#include "Matrices.h"

namespace Matrices
{
	Matrix::Matrix(int _rows, int _cols)
	{
        rows = _rows;
        cols = _cols;

        a.resize(rows, vector<double>(cols, 0));
	}

    Matrix operator+(const Matrix& a, const Matrix& b)
    {
        if (a.getCols() != b.getCols() || a.getRows() != b.getRows())
        {
            throw runtime_error("Error: dimensions must agree");
        }
        //if here then the dimensions match
        Matrix c(a.getRows(), a.getCols());

        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++)
            {
                c(i, j) = a(i, j) + b(i, j);
            }
        }

        return c;
    }

    Matrix operator*(const Matrix& a, const Matrix& b)
    {

        if (a.getCols() != b.getRows())
        {
            throw runtime_error("Error: dimensions must agree");
        }

        Matrix c(a.getRows(), b.getCols());

        for (int i = 0; i < a.getRows(); i++)
        {
            for (int k = 0; k < b.getCols(); k++)
            {
                for (int j = 0; j < a.getCols(); j++)
                {
                    c(i, k) += (a(i, j) * b(j, k));
                }
            }
        }

        return c;
    }

    bool operator==(const Matrix& a, const Matrix& b)
    {
        if (a.getCols() != b.getCols() || a.getRows() != b.getRows())
        {
            return false;
        }

        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < b.getCols(); j++)
            {
                if (abs(a(i, j) - b(i, j)) > 0.001)
                {
                    return false;
                }
            }
        }

        return true;
    }

    bool operator!=(const Matrix& a, const Matrix& b)
    {
        if (a.getCols() != b.getCols() || a.getRows() != b.getRows())
        {
            return true;
        }

        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < b.getCols(); j++)
            {
                if (abs(a(i, j) - b(i, j)) > 0.001)
                {
                    return true;
                }
            }
        }

        return false;
    }

    ostream& operator<<(ostream& os, const Matrix& a)
    {
        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++)
            {
                os << setw(12) << a(i, j) << " ";
            }
            os << endl;
        }
        return os;
    }

    RotationMatrix::RotationMatrix(double theta) : Matrix(2,2)
    {
        double cosTheta = cos(theta);
        double sinTheta = sin(theta);
        (*this)(0, 0) = cosTheta;
        (*this)(0, 1) = -sinTheta;
        (*this)(1, 0) = sinTheta;
        (*this)(1, 1) = cosTheta;
    }
    
    ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2)
    {
        (*this)(0, 0) = scale;
        (*this)(0, 1) = 0;
        (*this)(1, 0) = 0;
        (*this)(1, 1) = scale;
    }

    TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols)
    {
        for (int i = 0; i < nCols; i++)
        {
            (*this)(0, i) = xShift;
            (*this)(1, i) = yShift;
        }
    }
}