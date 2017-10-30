#include "QDynRobot.h"

QDynRobot::QDynRobot(QString filename, QObject *parent)
{
    QFile       *robotFile = new QFile(filename);
    QFileInfo   *robotFileInfo = new QFileInfo(filename);

    robotFile->open(QIODevice::ReadOnly);

    QDomDocument *doc = new QDomDocument("Robot");
    doc->setContent(robotFile);
    robotFile->close();

    QDomElement robotDoc = doc->documentElement();
    QDomNode robotNameNode = robotDoc.firstChild();
    QDomNode robotLinksNode = robotNameNode.nextSibling();
    QDomNode actLinkNode = robotLinksNode.firstChild();
    QDomElement actPropNode;

    this->name = robotNameNode.toElement().text();

    while(!actLinkNode.isNull())
    {
        actPropNode = actLinkNode.firstChild().toElement();
        while(!actPropNode.isNull())
        {
            if(actPropNode.tagName().toLower() == "name")
            Links << new QDynLink(robotFileInfo->absolutePath() + "/" + actPropNode.text() + ".obj", actPropNode.text());

            if(actPropNode.tagName().toLower() == "id")
            Links[Links.length()-1]->id = actPropNode.text().toInt();

            if(actPropNode.tagName().toLower() == "parentid")
            Links[Links.length()-1]->parentId = actPropNode.text().toInt();

            if(actPropNode.tagName().toLower() == "joint")
            Links[Links.length()-1]->jointType = actPropNode.text().toLower().startsWith("r") ? QDynLink::Revolute : QDynLink::Prismatic ;

            if(actPropNode.tagName().toLower() == "qmin")
            Links[Links.length()-1]->qMin = actPropNode.text().toDouble();

            if(actPropNode.tagName().toLower() == "qmax")
            Links[Links.length()-1]->qMax = actPropNode.text().toDouble();

            if(actPropNode.tagName().toLower() == "a")
            Links[Links.length()-1]->a = actPropNode.text().toDouble();

            if(actPropNode.tagName().toLower() == "alpha")
            Links[Links.length()-1]->alpha = actPropNode.text().toDouble();

            if(actPropNode.tagName().toLower() == "d")
            Links[Links.length()-1]->d = Links[Links.length()-1]->defaultD = actPropNode.text().toDouble();

            if(actPropNode.tagName().toLower() == "theta")
            {
                Links[Links.length()-1]->theta = Links[Links.length()-1]->defaultTheta = actPropNode.text().toDouble();
                if(actPropNode.attribute("plus","") != "")
                Links[Links.length()-1]->plusTheta = actPropNode.attribute("plus","").toDouble();
            }

            if(actPropNode.tagName().toLower() == "m")
            Links[Links.length()-1]->mass = actPropNode.text().toDouble();

            if(actPropNode.tagName().toLower() == "asys")
            {
                delete Links[Links.length()-1]->Asys;
                Links[Links.length()-1]->Asys = QDynGeneric::matrixFromString(actPropNode.text());
            }

            if(actPropNode.tagName().toLower() == "bsys")
            {
                delete Links[Links.length()-1]->Bsys;
                Links[Links.length()-1]->Bsys = QDynGeneric::matrixFromString(actPropNode.text());
            }

            if(actPropNode.tagName().toLower() == "csys")
            {
                delete Links[Links.length()-1]->Csys;
                Links[Links.length()-1]->Csys = QDynGeneric::matrixFromString(actPropNode.text());
            }

            if(actPropNode.tagName().toLower() == "dsys")
            {
                delete Links[Links.length()-1]->Dsys;
                Links[Links.length()-1]->Dsys = QDynGeneric::matrixFromString(actPropNode.text());
            }

            actPropNode = actPropNode.nextSibling().toElement();
        }
        actLinkNode = actLinkNode.nextSibling();
    }

    delete robotFile;
    delete robotFileInfo;

    nLinks = 0;

    nLinks = Links.length();
    realLinks = nLinks - 1;
    nPaths = 0;
    nPoints = 0;
    selectedLink = -1;
    isSelected = false;

    xRef = 0;
    yRef = 0;
    zRef = 0;
    tRef = 0;
    tAcu = 0;

    for(int i=0; i<(nLinks-1); i++)
    {
        qRef << 0;
        qSim << 0;
        qDot << 0;
        qDotDot << 0;
        qTorque << 0;
        Links[i+1]->computeInertiaAndCenterOfMass();
    }

    for(int i=0; i<nLinks; i++)
    {
        Links[i]->updateP();
    }

    stopped = false;
    ikSolved = false;

    x = 0; y = 0; z = 0; rotX = 0; rotY = 0; rotZ = 0;
    updateMatricesFrom(0,false,true);
}

QDynRobot::~QDynRobot()
{
    for(int i=(nLinks-1); i>=0; i--)
    {
        delete Links.takeAt(i);
    }

    for(int i=(nPaths-1); i>=0; i--)
    {
        deletePath(i);
    }
}

void QDynRobot::updateMatricesFrom(int link, bool secondaryMatrices, bool refreshRobotBounds)
{
    // First compute the matrices backwards each link, i.e., T0a, T0b
    for (int i=link; i<nLinks; i++)
    {
        if(Links[i]->parentId != -1)
        {
            // Each link i has a fixed frame of reference i.
            // Each link is defined between the frames i-1 and i;
            // The transformation between the global reference frame and i-th frame equals
            // the product between the transformation of the i-1 th frame and the transformation
            // between i-1 and i frames, which is Denavit-Hartenberg.
            // T:0->i = T:0->i-1 * T:i-1->i
            Links[i]->setBaseFrame(Links[Links[i]->parentId]->T0b,secondaryMatrices);
            Links[i]->updateglMatrices();
        }
        else
        {
            double R[3][3];
            double Tra[] = {x,y,z};
            QDynMath::convRxRyRz2RotM(rotX,rotY,rotZ,R);
            QDynMath::convRotTra2Trans(R,Tra,T);
            QDynMath::convTrans2glMat(T,glMat);
            Links[i]->setBaseFrame(T,secondaryMatrices);
            Links[i]->updateglMatrices();
        }
    }

    // Second, compute the matrices towards the link, i.e. Tbn
    for(int i=(nLinks-1); i>=link; i--)
    {
        if(i==(nLinks-1))
        {
            QDynMath::setTransIdentity(Links[i]->Tbn);
        }
        else
        {
            QDynMath::multTransMat(Links[i+1]->Tab,Links[i+1]->Tbn,Links[i]->Tbn);
        }
    }

    if(refreshRobotBounds)
    refreshBounds();
}

void QDynRobot::setQ(double q, int link, bool secondaryMatrices, bool refreshRobotBounds)
{
    if(Links[link]->jointType == QDynLink::Revolute/* && q != Links[link]->theta*/)
    {
        Links[link]->theta = q;
        updateMatricesFrom(link,secondaryMatrices);
    }
    if(Links[link]->jointType == QDynLink::Prismatic/* && q != Links[link]->d*/)
    {
        Links[link]->d = q;
        updateMatricesFrom(link,secondaryMatrices);
    }

    if(refreshRobotBounds)
    refreshBounds();
}

void QDynRobot::setProp(int prop, QVariant value)
{
    switch(prop)
    {
        case 0: // Robot Name
        name = value.toString();
        break;

        case 1: // Robot Name
        x = value.toDouble();
        break;

        case 2: // Robot Name
        y = value.toDouble();
        break;

        case 3: // Robot Name
        z = value.toDouble();
        break;

        case 4: // Robot Name
        rotX = value.toDouble();
        break;

        case 5: // Robot Name
        rotY = value.toDouble();
        break;

        case 6: // Robot Name
        rotZ = value.toDouble();
        break;

    }

    if(prop != 0)
    {
        updateMatricesFrom(0,true,true);
        ikSolved = false;
    }

}

void QDynRobot::resetRobot()
{
    x = 0;
    y = 0;
    z = 0;

    rotX = 0;
    rotY = 0;
    rotZ = 0;

    for (int i=0; i<nLinks; i++)
    {
        Links[i]->d = Links[i]->defaultD;
        Links[i]->theta = Links[i]->defaultTheta;
    }

    updateMatricesFrom(0,false,true);
    ikSolved = false;
}

void QDynRobot::addPath(QDynPath *path, int link, double appSpeed, double speed)
{
    Paths << new QDynRobotPath(nLinks-1, path, link, appSpeed, speed);

    nPaths = Paths.length();

    for(int i=1; i<nLinks; i++)
    {
        Paths[nPaths-1]->qIni[i-1] = (Links[i]->jointType == QDynLink::Revolute)? Links[i]->theta : Links[i]->d;
    }
    Paths[nPaths-1]->rIni[0] = this->x;
    Paths[nPaths-1]->rIni[1] = this->y;
    Paths[nPaths-1]->rIni[2] = this->z;

    Paths[nPaths-1]->rIni[3] = this->rotX;
    Paths[nPaths-1]->rIni[4] = this->rotY;
    Paths[nPaths-1]->rIni[5] = this->rotZ;

    ikSolved = false;
}

void QDynRobot::deletePath(int index)
{
    delete Paths.takeAt(index);
    nPaths = Paths.length();
    if (xRef)
    {
        delete [] xRef;
        delete [] yRef;
        delete [] zRef;
        delete [] tRef;
        delete [] tAcu;
        xRef = 0;
        yRef = 0;
        zRef = 0;
        tRef = 0;
        tAcu = 0;

        for(int i=realLinks-1; i>=0; i--)
        {
            if(qRef[i] || qDot[i] || qDotDot[i] || qTorque[i])
            {
                delete [] qRef[i];
                delete [] qDot[i];
                delete [] qDotDot[i];
                delete [] qTorque[i];
            }
            qRef[i] = 0;
            qDot[i] = 0;
            qDotDot[i] = 0;
            qTorque[i] = 0;
        }
    }
    ikSolved = false;
}

void QDynRobot::calculateFullPath()
{
    // First get the very first point by assigning the initial conditions
    ikSolved = false;
    int appPoints = 99;
    setInitialPathConfig();
    nPoints = 0;

    for(int i=0; i<nPaths; i++)
    {
        // Add the points because the approach path, can be 50.
        nPoints +=appPoints;

        // Then add the points regarding the actual path:
        nPoints += Paths[i]->path->nPoints;
    }

    // Then create the full array
    if (xRef)
    {
        delete [] xRef;
        delete [] yRef;
        delete [] zRef;
        delete [] tRef;
        delete [] tAcu;
        xRef = 0;
        yRef = 0;
        zRef = 0;
        tRef = 0;
        tAcu = 0;
    }

    xRef = new double[nPoints];
    yRef = new double[nPoints];
    zRef = new double[nPoints];
    tRef = new double[nPoints];
    tAcu = new double[nPoints];

    // For each path and its approach path, assign the proper values

    int index = 0;
    tAcu[0] = 0;

    for(int i=0; i<nPaths; i++)
    {
        double xIniApp,yIniApp,zIniApp,xFinApp,yFinApp,zFinApp;
        if(i==0)
        {
            // If is the very first path, the 1st point of the approach path is based on initial conditions
            xIniApp = Links[nLinks-1]->T0b[0][3];
            yIniApp = Links[nLinks-1]->T0b[1][3];
            zIniApp = Links[nLinks-1]->T0b[2][3];
        }
        else
        {
            // If is not the first path, the initial point of the approach path equals the endpoint of the previous path
            xIniApp = Paths[i-1]->path->points[(Paths[i-1]->path->nPoints)-1].pos[0];
            yIniApp = Paths[i-1]->path->points[(Paths[i-1]->path->nPoints)-1].pos[1];
            zIniApp = Paths[i-1]->path->points[(Paths[i-1]->path->nPoints)-1].pos[2];
        }

        // The last point of the approach path is the initial point of the actual path
        xFinApp = Paths[i]->path->points[0].pos[0] - (Paths[i]->path->points[0].pos[0]-xIniApp)/(appPoints+1);
        yFinApp = Paths[i]->path->points[0].pos[1] - (Paths[i]->path->points[0].pos[1]-yIniApp)/(appPoints+1);
        zFinApp = Paths[i]->path->points[0].pos[2] - (Paths[i]->path->points[0].pos[2]-zIniApp)/(appPoints+1);

        // Create a path for the approach path:
        QDynPath approachPath(xIniApp,yIniApp,zIniApp,xFinApp,yFinApp,zFinApp,appPoints);

        // Assign the approach path values to the reference values and define the time interval
        double tApp = (sqrt(pow(xFinApp - xIniApp,2) + pow(yFinApp - yIniApp,2) + pow(zFinApp - zIniApp,2)))/(double)appPoints/Paths[i]->approachSpeed;
//        qDebug() << Paths[i]->approachSpeed << tApp << "secs. for the approach path";

        for(int j=index; j<(appPoints+index); j++)
        {
            xRef[j] = approachPath.points[j-index].pos[0];
            yRef[j] = approachPath.points[j-index].pos[1];
            zRef[j] = approachPath.points[j-index].pos[2];
            tRef[j] = tApp;

            if(j>0)
            tAcu[j] = tAcu[j-1] + tRef[j-1];
        }

        index += appPoints;
        for(int j=index; j<(Paths[i]->path->nPoints+index); j++)
        {
            xRef[j] = Paths[i]->path->points[j-index].pos[0];
            yRef[j] = Paths[i]->path->points[j-index].pos[1];
            zRef[j] = Paths[i]->path->points[j-index].pos[2];
        }

        for(int j=index; j<(Paths[i]->path->nPoints+index); j++)
        {
            if(j<(Paths[i]->path->nPoints+index-1))
            tRef[j] = sqrt(pow(xRef[j+1] - xRef[j],2)+pow(yRef[j+1] - yRef[j],2)+pow(zRef[j+1] - zRef[j],2)) / Paths[i]->speed;
            else
            tRef[j] = tRef[j-1];

            tAcu[j] = tAcu[j-1] + tRef[j-1];
        }

        index += Paths[i]->path->nPoints;
    }
}

void QDynRobot::calculateInverseKinematics()
{
    stopped = false;
    if(qRef[0])
    {
        for(int i=realLinks-1; i>=0; i--)
        {
            delete [] qRef[i];
            qRef[i] = 0;
        }
    }

    double qA, qB;

    for(int i=0; i<realLinks; i++)
    {
        qRef[i] = new double[nPoints];
    }

    for(int i=0; i<nPoints; i++)
    {
        // 0 - Loading Robot.
        // 1 - IK Calculation.
        // 2 - Simulating
        emit processState(1,(int)floor((i*100.0/(nPoints))+ 0.5));

        for(int j=1; j<realLinks; j++)
        {
            if(stopped)
            {
                setInitialPathConfig();
                return;
            }

            // Here we iterate by picking pairs of joints in order to find the minimum like my algorithm proposes
            // So, for each pair of links
            findMinimumError(Links[j], Links[j+1], xRef[i], yRef[i], zRef[i], qA, qB);

            if(Links[j]->jointType == QDynLink::Revolute)
            qA -= Links[j]->plusTheta;

            if(Links[j+1]->jointType == QDynLink::Revolute)
            qB -= Links[j+1]->plusTheta;

            setQ(qA,j);
            setQ(qB,j+1);

            qRef[j-1][i] = qA;
            qRef[j  ][i] = qB;
        }
    }
}

void QDynRobot::calculateRobotDynamics()
{

    QDynDerivType derivType = Fourth;

    stopped = false;
    for(int i=realLinks-1; i>=0; i--)
    {
        if(qDot[i] || qDotDot[i] || qTorque[i])
        {
            delete [] qDot[i];
            delete [] qDotDot[i];
            delete [] qTorque[i];
        }
        qDot[i] = 0;
        qDotDot[i] = 0;
        qTorque[i] = 0;
    }


    for(int i=0; i<realLinks; i++)
    {
        qDot[i] = new double[nPoints];
        qDotDot[i] = new double[nPoints];
        qTorque[i] = new double[nPoints];
    }

    // First we have to compute qDot based on qRef
    for(int k=0; k<nPoints; k++)
    {
        for(int i=1; i<nLinks; i++)
        {
            if(derivType == Fourth)
            {
                if(k==0 || k==1)
                qDot[i-1][k] = (-3*qRef[i-1][k] + 4*qRef[i-1][k+1] - qRef[i-1][k+2])/2;
                else if(k==nPoints-1 || k==nPoints-2)
                qDot[i-1][k] = ( 3*qRef[i-1][k] - 4*qRef[i-1][k-1] + qRef[i-1][k-2])/2;
                else
                qDot[i-1][k] = (qRef[i-1][k-2] - 8*qRef[i-1][k-1] + 8*qRef[i-1][k+1] - qRef[i-1][k+2])/12;

                qDot[i-1][k] /= tRef[k];
            }

            if(derivType == Second)
            {
                if(k==0)
                qDot[i-1][k] = (qRef[i-1][k+1] - qRef[i-1][k])/tRef[k];
                else if(k==nPoints-1)
                qDot[i-1][k] = (qRef[i-1][k] - qRef[i-1][k-1])/tRef[k];
                else
                qDot[i-1][k] = (qRef[i-1][k+1] - qRef[i-1][k-1])/(tRef[k+1]+tRef[k-1]);
            }

        }
    }

    setQ(Links[0]->theta,0,true);

    // After computing qDot we can compute qDotDot and at the same time after computing qDotDot we can compute the whole dynamics (torques) of each link
    QList<QDynMatrix*> Ri0wi;
    QList<QDynMatrix*> Ri0widot;
    QList<QDynMatrix*> Ri0vidot;
    QList<QDynMatrix*> Ri0aibar;
    QList<QDynMatrix*> Ri0Fi;
    QList<QDynMatrix*> Ri0Ni;
    QList<QDynMatrix*> Ri0fi;
    QList<QDynMatrix*> Ri0ni;
    QList<QDynMatrix*> ti;

    QDynMatrix *z0      = new QDynMatrix(3,1); z0->data[0][0] = 0; z0->data[1][0] = 0; z0->data[2][0] = 1;
    QDynMatrix *vecZero = new QDynMatrix(3,1); vecZero->data[0][0] = 0; vecZero->data[1][0] = 0; vecZero->data[2][0] = 0;
    QDynMatrix *gravity = new QDynMatrix(3,1); gravity->data[0][0] = 0; gravity->data[1][0] = 0; gravity->data[2][0] = 9.8062;
    QDynMatrix *forceEE = new QDynMatrix(3,1); forceEE->data[0][0] = 0; forceEE->data[1][0] = 0; forceEE->data[2][0] = 0;
    QDynMatrix *momenEE = new QDynMatrix(3,1); momenEE->data[0][0] = 0; momenEE->data[1][0] = 0; momenEE->data[2][0] = 0;

    QDynMatrix *rotIdentity = new QDynMatrix(true,3);
    QDynMatrix *Ri0Gravity = QDynMath::multMatrix(Links[1]->Ra0,gravity);
    QDynMatrix *z0qiDot = 0;
    QDynMatrix *z0qiDotDot = 0;

    for(int i=1; i<nLinks; i++)
    {
        Ri0wi << 0;
        Ri0widot << 0;
        Ri0vidot << 0;
        Ri0aibar << 0;
        Ri0Fi << 0;
        Ri0Ni << 0;
        Ri0fi << 0;
        Ri0ni << 0;
        ti << 0;
    }

    for(int k=0; k<nPoints; k++)
    {
        for(int i=1; i<nLinks; i++)
        {
            if(stopped)
            {
                setInitialPathConfig();
                return;
            }

            if(derivType == Fourth)
            {
                if(k==0 || k==1)
                qDotDot[i-1][k] = (-3*qDot[i-1][k] + 4*qDot[i-1][k+1] - qDot[i-1][k+2])/2;
                else if(k==nPoints-1 || k==nPoints-2)
                qDotDot[i-1][k] = ( 3*qDot[i-1][k] - 4*qDot[i-1][k-1] + qDot[i-1][k-2])/2;
                else
                qDotDot[i-1][k] = (qDot[i-1][k-2] - 8*qDot[i-1][k-1] + 8*qDot[i-1][k+1] - qDot[i-1][k+2])/12;

                qDotDot[i-1][k] /= tRef[k];
            }

            if(derivType == Second)
            {
                if(k==0)
                qDotDot[i-1][k] = (qDot[i-1][k+1] - qDot[i-1][k])/tRef[k];
                else if(k==nPoints-1)
                qDotDot[i-1][k] = (qDot[i-1][k] - qDot[i-1][k-1])/tRef[k];
                else
                qDotDot[i-1][k] = (qDot[i-1][k+1] - qDot[i-1][k-1])/(tRef[k+1]+tRef[k-1]);
            }

            // For the actual point, we have to update all of the Joint Values
            // i.e., q's and finding all the rotation matrices in order to use them in the
            // computation of dynamics

            setQ(qRef[i-1][k],i,true);

        }

        // After computing all qDot and qDotDot we can calculate for the actual point and each link the torques

        // Forward Equations
        for(int i=1; i<nLinks; i++)
        {

            if(Links[i]->jointType == QDynLink::Revolute)
            {
                z0qiDot     = QDynMath::multMatScalar(z0,QDynMath::deg2Rad(qDot[i-1][k]));
                z0qiDotDot  = QDynMath::multMatScalar(z0,QDynMath::deg2Rad(qDotDot[i-1][k]));
            }
            if(Links[i]->jointType == QDynLink::Prismatic)
            {
                z0qiDot     = QDynMath::multMatScalar(z0,qDot[i-1][k]);
                z0qiDotDot  = QDynMath::multMatScalar(z0,qDotDot[i-1][k]);
            }

            if(i==1)
            {

                if(Links[i]->jointType == QDynLink::Revolute)
                {
                    Ri0wi[i-1]      = QDynMath::multMatrix(Links[i]->Rba, QDynMath::addMatrix(vecZero,z0qiDot));
                    Ri0widot[i-1]   = QDynMath::multMatrix(Links[i]->Rba, QDynMath::addMatrix( QDynMath::addMatrix(vecZero,z0qiDotDot),QDynMath::crossProd(vecZero,z0qiDot)));
                    Ri0vidot[i-1]   = QDynMath::addMatrix(QDynMath::addMatrix(QDynMath::crossProd(Ri0widot[i-1],Links[i]->p),QDynMath::crossProd(Ri0wi[i-1],QDynMath::crossProd(Ri0wi[i-1],Links[i]->p))), QDynMath::multMatrix(Links[i]->Rba,Ri0Gravity));

                }
                if(Links[i]->jointType == QDynLink::Prismatic)
                {
                    Ri0wi[i-1]      = QDynMath::multMatrix(Links[i]->Rba, vecZero);
                    Ri0widot[i-1]   = QDynMath::multMatrix(Links[i]->Rba, vecZero);
                    Ri0vidot[i-1]   = QDynMath::addMatrix(QDynMath::addMatrix(QDynMath::multMatrix(Links[i]->Rba, QDynMath::addMatrix(z0qiDotDot,Ri0Gravity)),QDynMath::crossProd(Ri0widot[i-1],Links[i]->p)),QDynMath::addMatrix(QDynMath::crossProd(QDynMath::multMatScalar(Ri0wi[i-1],2),QDynMath::multMatrix(Links[i]->Rba,z0qiDot)),QDynMath::crossProd(Ri0wi[i-1],QDynMath::crossProd(Ri0wi[i-1],Links[i]->p))));
                }
            }
            else
            {
                if(Links[i]->jointType == QDynLink::Revolute)
                {
                    Ri0wi[i-1]      = QDynMath::multMatrix(Links[i]->Rba, QDynMath::addMatrix(Ri0wi[i-2],z0qiDot ));
                    Ri0widot[i-1]   = QDynMath::multMatrix(Links[i]->Rba, QDynMath::addMatrix( QDynMath::addMatrix(Ri0widot[i-2],z0qiDotDot),QDynMath::crossProd(Ri0wi[i-2],z0qiDot)));
                    Ri0vidot[i-1]   = QDynMath::addMatrix(QDynMath::addMatrix(QDynMath::crossProd(Ri0widot[i-1],Links[i]->p),QDynMath::crossProd(Ri0wi[i-1],QDynMath::crossProd(Ri0wi[i-1],Links[i]->p))), QDynMath::multMatrix(Links[i]->Rba,Ri0vidot[i-2]));

                }
                if(Links[i]->jointType == QDynLink::Prismatic)
                {
                    Ri0wi[i-1]      = QDynMath::multMatrix(Links[i]->Rba, Ri0wi[i-2]);
                    Ri0widot[i-1]   = QDynMath::multMatrix(Links[i]->Rba, Ri0widot[i-2]);
                    Ri0vidot[i-1]   = QDynMath::addMatrix(QDynMath::addMatrix(QDynMath::multMatrix(Links[i]->Rba, QDynMath::addMatrix(z0qiDotDot,Ri0vidot[i-2])),QDynMath::crossProd(Ri0widot[i-1],Links[i]->p)),QDynMath::addMatrix(QDynMath::crossProd(QDynMath::multMatScalar(Ri0wi[i-1],2),QDynMath::multMatrix(Links[i]->Rba,z0qiDot)),QDynMath::crossProd(Ri0wi[i-1],QDynMath::crossProd(Ri0wi[i-1],Links[i]->p))));
                }
            }

            Ri0aibar[i-1]   = QDynMath::addMatrix( QDynMath::addMatrix(QDynMath::crossProd(Ri0widot[i-1],Links[i]->s),QDynMath::crossProd(Ri0wi[i-1],QDynMath::crossProd(Ri0wi[i-1],Links[i]->s))),Ri0vidot[i-1]);

            delete z0qiDot;
            delete z0qiDotDot;

        }

        // Backward Equations
        for(int i=nLinks-1; i>=1; i--)
        {
            Ri0Fi[i-1] = QDynMath::multMatScalar(Ri0aibar[i-1],Links[i]->mass);
            Ri0Ni[i-1] = QDynMath::addMatrix(QDynMath::multMatrix(Links[i]->I,Ri0widot[i-1]),QDynMath::crossProd(Ri0wi[i-1],QDynMath::multMatrix(Links[i]->I,Ri0wi[i-1])));

            if(i==nLinks-1)
            {
                Ri0fi[i-1] = QDynMath::addMatrix(QDynMath::multMatrix(rotIdentity,forceEE),Ri0Fi[i-1]);
                Ri0ni[i-1] = QDynMath::addMatrix(QDynMath::multMatrix(rotIdentity,QDynMath::addMatrix(momenEE,QDynMath::crossProd(QDynMath::multMatrix(rotIdentity,Links[i]->p),forceEE))),QDynMath::addMatrix( QDynMath::crossProd(QDynMath::addMatrix(Links[i]->p,Links[i]->s),Ri0Fi[i-1]),Ri0Ni[i-1]));
            }
            else
            {
                Ri0fi[i-1] = QDynMath::addMatrix(QDynMath::multMatrix(Links[i+1]->Rab,Ri0fi[i]),Ri0Fi[i-1]);
                Ri0ni[i-1] = QDynMath::addMatrix(QDynMath::multMatrix(Links[i+1]->Rab,QDynMath::addMatrix(Ri0ni[i],QDynMath::crossProd(QDynMath::multMatrix(Links[i+1]->Rba,Links[i]->p),Ri0fi[i]))),QDynMath::addMatrix( QDynMath::crossProd(QDynMath::addMatrix(Links[i]->p,Links[i]->s),Ri0Fi[i-1]),Ri0Ni[i-1]));
            }
            if(Links[i]->jointType == QDynLink::Revolute)
            {
                ti[i-1] = QDynMath::multMatrix(Ri0ni[i-1]->getTranspose(),QDynMath::multMatrix(Links[i]->Rba,z0));
            }
            if(Links[i]->jointType == QDynLink::Prismatic)
            {
                ti[i-1] = QDynMath::multMatrix(Ri0fi[i-1]->getTranspose(),QDynMath::multMatrix(Links[i]->Rba,z0));
            }
            qTorque[i-1][k] = ti[i-1]->data[0][0];
        }

        // For each point we have to delete the matrices in order to avoid memory increasing or unreferenced memory sectors
        for(int i=1; i<nLinks; i++)
        {
            if(Ri0wi[i-1])
            {
                delete Ri0wi[i-1];
                delete Ri0widot[i-1];
                delete Ri0vidot[i-1];
                delete Ri0aibar[i-1];
                delete Ri0Fi[i-1];
                delete Ri0Ni[i-1];
                delete Ri0fi[i-1];
                delete Ri0ni[i-1];
                delete ti[i-1];
            }

            Ri0wi[i-1] = 0;
            Ri0widot[i-1] = 0;
            Ri0vidot[i-1] = 0;
            Ri0aibar[i-1] = 0;
            Ri0Fi[i-1] = 0;
            Ri0Ni[i-1] = 0;
            Ri0fi[i-1] = 0;
            Ri0ni[i-1] = 0;
            ti[i-1] = 0;
        }
    }

    delete z0;
    delete vecZero;
    delete gravity;
    delete forceEE;
    delete momenEE;

    delete Ri0Gravity;
    delete rotIdentity;

    for(int i=nLinks-1; i>=1; i--)
    {
        delete Ri0wi.takeAt(i-1);
        delete Ri0widot.takeAt(i-1);
        delete Ri0vidot.takeAt(i-1);
        delete Ri0aibar.takeAt(i-1);
        delete Ri0Fi.takeAt(i-1);
        delete Ri0Ni.takeAt(i-1);
        delete Ri0fi.takeAt(i-1);
        delete Ri0ni.takeAt(i-1);
        delete ti.takeAt(i-1);
    }

    setInitialPathConfig();
    ikSolved = true;
}

void QDynRobot::calculateDynamicResponses()
{
    QDynMatrix *xSt;
    QDynMatrix *u;

    QDynMatrix *A;
    QDynMatrix *B;
    QDynMatrix *C;
    QDynMatrix *D;

    QDynMatrix *k1;
    QDynMatrix *k2;
    QDynMatrix *k3;
    QDynMatrix *k4;

    QDynMatrix *xAct,*suma;
    QDynMatrix *ui0,*ui1,*uih;

    stopped = false;
    if(qSim[0])
    {
        for(int i=realLinks-1; i>=0; i--)
        {
            delete [] qSim[i];
            qSim[i] = 0;
        }
    }

    for(int i=0; i<realLinks; i++)
    {
        qSim[i] = new double[nPoints];
    }

    for(int k=1; k<nLinks; k++)
    {
        A = Links[k]->Asys; B = Links[k]->Bsys; C = Links[k]->Csys; D = Links[k]->Dsys;
        int nStates = A->cols;

        xSt = new QDynMatrix(nStates,nPoints);
        u   = new QDynMatrix(1,nPoints);

        for(int i=0; i<nStates; i++)
        {
            xSt->data[i][0] = 0;
        }

        for(int i=0; i<(nPoints-1); i++)
        {
            xAct = xSt->getColumn(i);

            u->data[0][i]   = qRef[k-1][i];
            u->data[0][i+1] = qRef[k-1][i+1];

            ui0 = u->getColumn(i);
            ui1 = u->getColumn(i+1);
            uih = QDynMath::multMatrix(QDynMath::addMatrix(ui1,ui0),new QDynMatrix(0.5));

            k1 = QDynMath::addMatrix(QDynMath::multMatrix(A,xAct), QDynMath::multMatrix(B,ui0));
            k2 = QDynMath::addMatrix(QDynMath::multMatrix(A, QDynMath::addMatrix(xAct,QDynMath::multMatrix(k1,new QDynMatrix(0.5)))), QDynMath::multMatrix(B,uih));
            k3 = QDynMath::addMatrix(QDynMath::multMatrix(A, QDynMath::addMatrix(xAct,QDynMath::multMatrix(k2,new QDynMatrix(0.5)))), QDynMath::multMatrix(B,uih));
            k4 = QDynMath::addMatrix(QDynMath::multMatrix(A, QDynMath::addMatrix(xAct,k3)), QDynMath::multMatrix(B,ui1));

            suma = QDynMath::addMatrix( QDynMath::addMatrix(k1,k4), QDynMath::multMatrix(new QDynMatrix(2.0), QDynMath::addMatrix(k2,k3)));
            xSt->setColumn(i+1, QDynMath::addMatrix(xAct, QDynMath::multMatrix(suma,new QDynMatrix(1.0/6.0))));

            qSim[k-1][i] = QDynMath::addMatrix(QDynMath::multMatrix(C,xAct), QDynMath::multMatrix(D,ui0))->data[0][0];

            if(i == (nPoints-2))
            qSim[k-1][i+1] = QDynMath::addMatrix(QDynMath::multMatrix(C,xSt->getColumn(i+1)), QDynMath::multMatrix(D,ui1))->data[0][0];

            delete k1;
            delete k2;
            delete k3;
            delete k4;
            delete xAct;
            delete suma;
            delete ui0;
            delete ui1;
            delete uih;
        }

        delete xSt;
        delete u;
    }
}

void QDynRobot::findMinimumError(QDynLink *LinkA, QDynLink *LinkB, double xf, double yf, double zf, double &qA, double &qB)
{

    double a1 = LinkA->a;
    double a2 = LinkB->a;
    double alpha1 = LinkA->alpha;
    double alpha2 = LinkB->alpha;
    double d1 = LinkA->d;
    double d2 = LinkB->d;
    double theta1 = LinkA->theta + LinkA->plusTheta;
    double theta2 = LinkB->theta + LinkB->plusTheta;

    int jointA = (LinkA->jointType == QDynLink::Revolute)? 0 : 1;
    int jointB = (LinkB->jointType == QDynLink::Revolute)? 0 : 1;

    double precision = 1e-5;

    bool singular = false;

    if(jointA == 0 && jointB == 0)
    {
        if(fabs(cos(QDynMath::deg2Rad(theta2))) >= cos(QDynMath::deg2Rad(10)) )
        singular = true;
    }

    int maxIter = 1000;
    int actIter = 0;
    double err = 100;
    double derErr = 100;

    double xnew = (jointA == 0)? theta1 : d1;
    double ynew = (jointB == 0)? theta2 : d2;

    double T0aLinkA[4][4];
    double TbnLinkB[4][4];
    double TabLinkA[4][4];
    double TabLinkB[4][4];
    double TA[4][4];
    double TB[4][4];
    double TT[4][4];

    QDynMath::copyMatTrans(LinkA->T0a,T0aLinkA);
    QDynMath::copyMatTrans(LinkB->Tbn,TbnLinkB);

    for(int i=0; i<maxIter; i++)
    {

        QDynMath::convDH2Trans(a1,alpha1,((jointA == 0)? d1 : xnew),((jointA == 0)? xnew : theta1),TabLinkA);
        QDynMath::convDH2Trans(a2,alpha2,((jointB == 0)? d2 : ynew),((jointB == 0)? ynew : theta2),TabLinkB);

        QDynMath::multTransMat(T0aLinkA,TabLinkA,TA);
        QDynMath::multTransMat(TabLinkB,TbnLinkB,TB);
        QDynMath::multTransMat(TA,TB,TT);

        err = sqrt( pow(xf-TT[0][3],2) +  pow(yf-TT[1][3],2) + pow(zf-TT[2][3],2) );

        if(err < precision || derErr < (precision*precision))
        {
            actIter = i;
            break;
        }

        if(singular && i==0)
        {
            ynew += 15;
        }

        if(LinkA->jointType == QDynLink::Revolute && LinkB->jointType == QDynLink::Revolute)
        {
            QDynMath::newtonRR(derErr,xnew,ynew,T0aLinkA,TbnLinkB,xf,yf,zf,a1,alpha1,d1,xnew,a2,alpha2,d2,ynew);
        }

        if(LinkA->jointType == QDynLink::Revolute && LinkB->jointType == QDynLink::Prismatic)
        {
            QDynMath::newtonRP(derErr,xnew,ynew,T0aLinkA,TbnLinkB,xf,yf,zf,a1,alpha1,d1,xnew,a2,alpha2,ynew,theta2);
        }

        if(LinkA->jointType == QDynLink::Prismatic && LinkB->jointType == QDynLink::Revolute)
        {
            QDynMath::newtonPR(derErr,xnew,ynew,T0aLinkA,TbnLinkB,xf,yf,zf,a1,alpha1,xnew,theta1,a2,alpha2,d2,ynew);
        }

        if(LinkA->jointType == QDynLink::Prismatic && LinkB->jointType == QDynLink::Prismatic)
        {
            QDynMath::newtonPP(derErr,xnew,ynew,T0aLinkA,TbnLinkB,xf,yf,zf,a1,alpha1,xnew,theta1,a2,alpha2,ynew,theta2);
        }

        if(xnew>LinkA->qMax)
        xnew = LinkA->qMax;

        if(xnew<LinkA->qMin)
        xnew = LinkA->qMin;

        if(ynew>LinkB->qMax)
        ynew = LinkB->qMax;

        if(ynew<LinkB->qMin)
        ynew = LinkB->qMin;

    }
    qA = xnew;
    qB = ynew;
}

void QDynRobot::simulationStep()
{
    for(int i=1; i<=realLinks; i++)
    {
        setQ(qRef[i-1][actSimState],i);
    }
    emit processState(2,(int)((tAcu[actSimState]*100)/tAcu[nPoints-1]));
    actSimState++;
}

void QDynRobot::stopCalculation()
{
    stopped = true;
}

void QDynRobot::setInitialPathConfig(bool resetIK)
{
    if(resetIK)
    {
        if(Paths[0]->rIni[0] != this->x)
        setProp(1,Paths[0]->rIni[0]);
        if(Paths[0]->rIni[1] != this->y)
        setProp(2,Paths[0]->rIni[1]);
        if(Paths[0]->rIni[2] != this->z)
        setProp(3,Paths[0]->rIni[2]);
        if(Paths[0]->rIni[3] != this->rotX)
        setProp(4,Paths[0]->rIni[3]);
        if(Paths[0]->rIni[4] != this->rotY)
        setProp(5,Paths[0]->rIni[4]);
        if(Paths[0]->rIni[5] != this->rotZ)
        setProp(6,Paths[0]->rIni[5]);
    }

    for(int i=1; i<nLinks; i++)
    {
        setQ(Paths[0]->qIni[i-1],i,false);
    }

    refreshBounds();

}

void QDynRobot::refreshBounds()
{
    xMax = yMax = zMax = -5000;
    xMin = yMin = zMin =  5000;

    double P1[4];
    double P2[4];
    double P3[4];
    double P4[4];
    double P5[4];
    double P6[4];
    double P7[4];
    double P8[4];

    QList<double*> PNew;

    for(int i=0; i<8; i++)
    {
        PNew << new double[4];
    }

    for(int i=0; i<nLinks; i++)
    {
        P1[0] = Links[i]->mesh->xMin; P1[1] = Links[i]->mesh->yMax; P1[2] = Links[i]->mesh->zMax; P1[3] = 1;
        P2[0] = Links[i]->mesh->xMin; P2[1] = Links[i]->mesh->yMin; P2[2] = Links[i]->mesh->zMax; P2[3] = 1;
        P3[0] = Links[i]->mesh->xMin; P3[1] = Links[i]->mesh->yMin; P3[2] = Links[i]->mesh->zMin; P3[3] = 1;
        P4[0] = Links[i]->mesh->xMin; P4[1] = Links[i]->mesh->yMax; P4[2] = Links[i]->mesh->zMin; P4[3] = 1;
        P5[0] = Links[i]->mesh->xMax; P5[1] = Links[i]->mesh->yMax; P5[2] = Links[i]->mesh->zMax; P5[3] = 1;
        P6[0] = Links[i]->mesh->xMax; P6[1] = Links[i]->mesh->yMin; P6[2] = Links[i]->mesh->zMax; P6[3] = 1;
        P7[0] = Links[i]->mesh->xMax; P7[1] = Links[i]->mesh->yMin; P7[2] = Links[i]->mesh->zMin; P7[3] = 1;
        P8[0] = Links[i]->mesh->xMax; P8[1] = Links[i]->mesh->yMax; P8[2] = Links[i]->mesh->zMin; P8[3] = 1;

        QDynMath::singleCoorTrans(Links[i]->T0b,P1,PNew[0]);
        QDynMath::singleCoorTrans(Links[i]->T0b,P2,PNew[1]);
        QDynMath::singleCoorTrans(Links[i]->T0b,P3,PNew[2]);
        QDynMath::singleCoorTrans(Links[i]->T0b,P4,PNew[3]);
        QDynMath::singleCoorTrans(Links[i]->T0b,P5,PNew[4]);
        QDynMath::singleCoorTrans(Links[i]->T0b,P6,PNew[5]);
        QDynMath::singleCoorTrans(Links[i]->T0b,P7,PNew[6]);
        QDynMath::singleCoorTrans(Links[i]->T0b,P8,PNew[7]);

        for(int j=0; j<8; j++)
        {
            if(PNew[j][0] <= xMin)
            xMin = PNew[j][0];
            if(PNew[j][1] <= yMin)
            yMin = PNew[j][1];
            if(PNew[j][2] <= zMin)
            zMin = PNew[j][2];

            if(PNew[j][0] >= xMax)
            xMax = PNew[j][0];
            if(PNew[j][1] >= yMax)
            yMax = PNew[j][1];
            if(PNew[j][2] >= zMax)
            zMax = PNew[j][2];
        }
    }
}
