#include "QDynMatrix.h"

QDynMatrix::QDynMatrix(int nRow, int nCol)
{
    // Creates a matrix with size of nRow and nCol

    rows = nRow;
    cols = nCol;

    if(rows == 1 && cols == 1)
    isScalar = true;
    else
    isScalar = false;

    for(int i=0; i<nRow; i++)
    {
        data << new double[nCol];
    }
}

QDynMatrix::QDynMatrix(bool identity, int size)
{
    if(identity)
    {
        rows = size;
        cols = size;

        if(rows == 1 && cols == 1)
        isScalar = true;
        else
        isScalar = false;

        for(int i=0; i<size; i++)
        {
            data << new double[size];
        }

        for(int i=0; i<size; i++)
        {
            for(int j=0; j<size; j++)
            {
                data[i][j] = (i==j)? 1 : 0;
            }
        }

    }
    else
    {
        rows = 1;
        cols = 1;
        isScalar = true;

        data << new double[1];
        data[0][0] = 1;
    }
}

QDynMatrix::QDynMatrix(double value)
{
    // Creates a scalar (which is a 1x1 Matrix)
    rows = 1;
    cols = 1;
    isScalar = true;

    data << new double[1];
    data[0][0] = value;
}

QDynMatrix::~QDynMatrix()
{
    for(int i=rows-1; i>=0; i--)
    {
        delete [] data.takeAt(i);
    }
}

QDynMatrix* QDynMatrix::getColumn(int col)
{
    QDynMatrix *R = new QDynMatrix(rows,1);

    for(int i=0; i<rows; i++)
    {
        R->data[i][0] = this->data[i][col];
    }

    return R;
}

QDynMatrix* QDynMatrix::getRow(int row)
{
    QDynMatrix *R = new QDynMatrix(1,cols);

    for(int i=0; i<cols; i++)
    {
        R->data[0][i] = this->data[row][i];
    }

    return R;
}

QDynMatrix* QDynMatrix::getSubMatrix(int fromRow, int fromCol, int toRow, int toCol)
{
    int cantRows = toRow-fromRow+1;
    int cantCols = toCol-fromCol+1;

    if(cantRows <= 0 || cantCols <= 0)
    return 0;

    QDynMatrix *R = new QDynMatrix(cantRows,cantCols);

    for(int i=0; i<cantRows; i++)
    {
        for(int j=0; j<cantRows; j++)
        {
            R->data[i][j] = this->data[i+fromRow][j+fromCol];
        }
    }
    return R;
}

void QDynMatrix::getSubMatrix(QDynMatrix *mat, int fromRow, int fromCol, int toRow, int toCol)
{
    int cantRows = toRow-fromRow+1;
    int cantCols = toCol-fromCol+1;

    if(cantRows <= 0 || cantCols <= 0)
    return;

    for(int i=0; i<cantRows; i++)
    {
        for(int j=0; j<cantRows; j++)
        {
            mat->data[i][j] = this->data[i+fromRow][j+fromCol];
        }
    }
}

void QDynMatrix::setColumn(int col, QDynMatrix *colMat)
{
    if(colMat->cols != 1 || colMat->rows != rows)
    return;

    for(int i=0; i<rows; i++)
    {
        this->data[i][col] = colMat->data[i][0];
    }
}

void QDynMatrix::setRow(int row, QDynMatrix *rowMat)
{
    if(rowMat->rows != 1 || rowMat->cols != cols)
    return;

    for(int i=0; i<cols; i++)
    {
        this->data[row][i] = rowMat->data[0][i];
    }
}

QDynMatrix* QDynMatrix::getTranspose()
{
    QDynMatrix *R = new QDynMatrix(cols,rows);

    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            R->data[j][i] = this->data[i][j];
        }
    }

    return R;
}

void QDynMatrix::getTranspose(QDynMatrix *mat)
{
    if(mat->rows!=cols || mat->cols!=rows)
    return;

    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            mat->data[j][i] = this->data[i][j];
        }
    }
}
