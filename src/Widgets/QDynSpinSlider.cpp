#include "QDynSpinSlider.h"

int roundInt(double d)
{
    return (int)floor(d + 0.5);
}

QDynSpinSlider::QDynSpinSlider(QWidget *parent)
    : QWidget(parent)
{
    spinBox = new QDoubleSpinBox(this);
    slider = new QScrollBar(this);
    slider->setOrientation(Qt::Horizontal);

    spinBox->setGeometry(0,0,50,20);
    slider->setGeometry(spinBox->geometry());

    spinBox->setAccelerated(true);
    spinBox->setFocusPolicy(Qt::StrongFocus);

    setFocusPolicy(Qt::StrongFocus);
    setFocusProxy(spinBox);

    singleStep = 0.1;
    setRange(0,100);
    setSingleStep(0.1);

    invertedSlide = false;
    slider->setInvertedAppearance(invertedSlide);

    connect(spinBox,SIGNAL(valueChanged(double)),this,SLOT(setValueFromSpin(double)));
    connect(slider,SIGNAL(valueChanged(int)),this,SLOT(setValueFromSlide(int)));
}

QDynSpinSlider::~QDynSpinSlider()
{

}

void QDynSpinSlider::setRange(double minValue, double maxValue)
{
    min = minValue;
    max = maxValue;
    spinBox->setRange(min, max);
    slider->setRange(roundInt(min/singleStep),roundInt(max/singleStep));
}

void QDynSpinSlider::setDecimals(int decValue)
{
    spinBox->setDecimals(decValue);
}

void QDynSpinSlider::setSuffix(QString suffix)
{
    spinBox->setSuffix(suffix);
}

void QDynSpinSlider::setSingleStep(double stepValue)
{
    singleStep = stepValue;
    spinBox->setSingleStep(singleStep);
    slider->setRange(roundInt(min/singleStep),roundInt(max/singleStep));
}

void QDynSpinSlider::setPageStep(double stepValue)
{
    pageStep = stepValue;
    slider->setPageStep(roundInt(pageStep/singleStep));
}

void QDynSpinSlider::setInvertedSlide(bool inv)
{
    invertedSlide = inv;
    slider->setInvertedAppearance(invertedSlide);
}

void QDynSpinSlider::adjustAllSizes(QRect rect)
{
    this->setGeometry(rect);
    this->setFixedHeight(rect.height()+20);
    spinBox->setFixedSize(rect.width(),rect.height());
    slider->setGeometry(0,rect.height(),rect.width(),20);
}

void QDynSpinSlider::setValue(double newValue)
{
//    if (value != newValue)
//    {
        value = newValue;

        disconnect(spinBox,SIGNAL(valueChanged(double)),this,SLOT(setValueFromSpin(double)));
        disconnect(slider,SIGNAL(valueChanged(int)),this,SLOT(setValueFromSlide(int)));

        spinBox->setValue(newValue);
        slider->setValue(roundInt(value/singleStep));

        connect(spinBox,SIGNAL(valueChanged(double)),this,SLOT(setValueFromSpin(double)));
        connect(slider,SIGNAL(valueChanged(int)),this,SLOT(setValueFromSlide(int)));

        emit valueChanged(newValue);
//    }
}


void QDynSpinSlider::setValueFromSpin(double spinValue)
{
    setValue(spinValue);
//    value = spinValue;
//    disconnect(slider,SIGNAL(valueChanged(int)),this,SLOT(setValueFromSlide(int)));
//    slider->setValue(roundInt(value/singleStep));
//    connect(slider,SIGNAL(valueChanged(int)),this,SLOT(setValueFromSlide(int)));
}

void QDynSpinSlider::setValueFromSlide(int slideValue)
{
    double newValue = ((double)slideValue) * singleStep;
    setValue(newValue);
//    value = newValue;
//    disconnect(spinBox,SIGNAL(valueChanged(double)),this,SLOT(setValueFromSpin(double)));
//    spinBox->setValue(value);
//    connect(spinBox,SIGNAL(valueChanged(double)),this,SLOT(setValueFromSpin(double)));
}
