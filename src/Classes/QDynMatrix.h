#ifndef QDYNMATRIX_H
#define QDYNMATRIX_H

#include <QList>

class QDynMatrix
{

public:
    QDynMatrix(int nRow, int nCol);
    QDynMatrix(double value);
    QDynMatrix(bool identity, int size);

    QDynMatrix* getColumn(int col);
    QDynMatrix* getRow(int row);

    QDynMatrix* getSubMatrix(int fromRow, int fromCol, int toRow, int toCol);
    void getSubMatrix(QDynMatrix *mat, int fromRow, int fromCol, int toRow, int toCol);

    void setColumn(int col, QDynMatrix* colMat);
    void setRow(int row, QDynMatrix* rowMat);

    QDynMatrix* getTranspose();
    void getTranspose(QDynMatrix *mat);

    ~QDynMatrix();

    int rows;
    int cols;
    bool isScalar;
    QList<double*> data;
};

#endif // QDYNMATRIX_H
