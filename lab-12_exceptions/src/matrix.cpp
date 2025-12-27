#include "matrix.h"

matrixNamespace::Matrix::Matrix(int r, int c) : _rows(r), _cols(c)
{
    _data.resize(_rows, std::vector<int>(_cols));
    for (int i = 0; i < get_rows(); ++i)
    {
        for (int j = 0; j < get_cols(); ++j)
            _data[i][j] = 0;
    }
}
matrixNamespace::Matrix::~Matrix()
{
}

matrixNamespace::Matrix::Matrix(const Matrix &other) : _rows(other._rows), _cols(other._cols)
{
    _data.resize(_rows, std::vector<int>(_cols));
    for (int i = 0; i < get_rows(); ++i)
        for (int j = 0; j < get_cols(); ++j)
            set(i, j, other.get(i, j));
}

int matrixNamespace::Matrix::get_rows() const
{
    return _rows;
}

int matrixNamespace::Matrix::get_cols() const
{
    return _cols;
}

void matrixNamespace::Matrix::set(int i, int j, int val)
{
    if (i < 0 || j < 0 || i >= get_rows() || j >= get_cols())
        throw MatrixException("ACCESS: bad index.");
    _data[i][j] = val;
}

int matrixNamespace::Matrix::get(int i, int j) const
{
    if (i < 0 || j < 0 || i >= get_rows() || j >= get_cols())
        throw MatrixException("ACCESS: bad index.");
    return _data[i][j];
}

matrixNamespace::Matrix &matrixNamespace::Matrix::operator=(Matrix m)
{
    if (this == &m)
        return *this;

    _data.clear();
    _data.resize(m.get_rows(), std::vector<int>(m.get_cols()));
    _cols = m.get_cols();
    _rows = m.get_rows();
    for (int i = 0; i < _rows; ++i)
        for (int j = 0; j < _cols; ++j)
            set(i, j, m._data[i][j]);
    return *this;
}

matrixNamespace::Matrix matrixNamespace::Matrix::operator+(const Matrix &m) const
{
    if (get_rows() != m.get_rows() || get_cols() != m.get_cols())
        throw MatrixException("ADD: dimensions do not match.");

    Matrix ans(get_rows(), get_cols());
    for (int i = 0; i < get_rows(); ++i)
        for (int j = 0; j < get_cols(); ++j)
            ans.set(i, j, get(i, j) + m.get(i, j));
    return ans;
}

matrixNamespace::Matrix Matrix::Matrix::operator-(const Matrix &m) const
{
    if (get_rows() != m.get_rows() || get_cols() != m.get_cols())
        throw MatrixException("ADD: dimensions do not match.");

    Matrix ans(get_rows(), get_cols());
    for (int i = 0; i < get_rows(); ++i)
        for (int j = 0; j < get_cols(); ++j)
            ans.set(i, j, get(i, j) - m.get(i, j));
    return ans;
}

matrixNamespace::Matrix matrixNamespace::Matrix::operator*(const Matrix &m) const
{
    if (get_cols() != m.get_rows())
    {
        throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
    }

    Matrix ans(get_rows(), m.get_cols());
    for (int i = 0; i < get_rows(); ++i)
        for (int j = 0; j < m.get_cols(); ++j)
            for (int k = 0; k < get_cols(); ++k)
                ans.set(i, j, ans.get(i, j) + get(i, k) * m.get(k, j));
    return ans;
}

bool matrixNamespace::Matrix::operator==(const Matrix &m) const
{
    if (get_rows() != m.get_rows() || get_cols() != m.get_cols())
        return false;
    for (int i = 0; i < get_rows(); ++i)
        for (int j = 0; j < get_cols(); ++j)
            if (get(i, j) != m.get(i, j))
                return false;
    return true;
}

bool matrixNamespace::Matrix::operator!=(const Matrix &m) const
{
    return !(*this == m);
}

matrixNamespace::Matrix &Matrix::Matrix::operator+=(const Matrix &m)
{
    *this = *this + m;
    return *this;
}
matrixNamespace::Matrix &Matrix::Matrix::operator-=(const Matrix &m)
{
    *this = *this - m;
    return *this;
}
matrixNamespace::Matrix &Matrix::Matrix::operator*=(const Matrix &m)
{
    *this = *this * m;
    return *this;
}

void Matrix::load(std::ifstream &f, Matrix &pos)
{
    int rows, col;
    if (f.eof())
        throw MatrixException("LOAD: invalid file format.");
    if (f.fail())
        throw MatrixException("File tech problem exception");

    f >> rows;
    if (f.eof())
        throw MatrixException("LOAD: invalid file format.");
    if (f.fail())
        throw MatrixException("File tech problem exception");

    f >> col;
    if (f.eof())
        throw MatrixException("LOAD: invalid file format.");
    if (f.fail())
        throw MatrixException("File tech problem exception");
    Matrix tmp(rows, col);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < col; ++j)
        {
            int x;
            f >> x;
            if (f.eof())
                throw MatrixException("LOAD: invalid file format.");
            if (f.fail())
                throw MatrixException("File tech problem exception");
            tmp.set(i, j, x);
        }
    pos = tmp;
}

matrixNamespace::MatrixException::MatrixException(const std::string &s)
{
    ExceptionMessage = std::string(s);
}

matrixNamespace::MatrixHolder::MatrixHolder()
{
    matrixVec_.resize(10);
}

matrixNamespace::MatrixHolder::~MatrixHolder()
{
    matrixVec_.clear();
}

void matrixNamespace::MatrixHolder::print(std::istream &is, std::ostream &os)
{
    try
    {
        char x;
        int curRegister;
        is >> x >> curRegister;
        Matrix &curMatrix = matrixVec_[curRegister];
        for (int i = 0; i < curMatrix.get_rows(); ++i)
        {
            for (int j = 0; j < curMatrix.get_cols(); ++j)
            {
                os << curMatrix.get(i, j);
                if (j != curMatrix.get_cols() - 1)
                    os << " ";
            }
            os << std::endl;
        }
    }
    catch (MatrixException &e)
    {
        os << e.ExceptionMessage << std::endl;
    }
}

void matrixNamespace::MatrixHolder::elem(std::istream &is, std::ostream &os)
{
    try
    {
        char x;
        int curRegister;
        int col, row;
        is >> x >> curRegister >> row >> col;
        os << matrixVec_[curRegister].get(row, col) << std::endl;
    }
    catch (MatrixException &e)
    {
        os << e.ExceptionMessage << std::endl;
    }
}

void matrixNamespace::MatrixHolder::mul(std::istream &is, std::ostream &os)
{
    try
    {
        char x;
        int curRegister1, curRegister2;
        is >> x >> curRegister1 >> x >> curRegister2;
        matrixVec_[curRegister1] *= matrixVec_[curRegister2];
    }
    catch (MatrixException &e)
    {
        os << e.ExceptionMessage << std::endl;
    }
}

void matrixNamespace::MatrixHolder::add(std::istream &is, std::ostream &os)
{
    try
    {
        char x;
        int curRegister1, curRegister2;
        is >> x >> curRegister1 >> x >> curRegister2;
        matrixVec_[curRegister1] += matrixVec_[curRegister2];
    }
    catch (MatrixException &e)
    {
        os << e.ExceptionMessage << std::endl;
    }
}

void matrixNamespace::MatrixHolder::load(std::istream &is, std::ostream &os)
{
    try
    {
        char x;
        int curRegister;
        std::string fileName;
        is >> x >> curRegister >> fileName;
        std::ifstream f(fileName);
        if (!f.is_open())
            throw MatrixException("LOAD: unable to open file.");
        Matrix::load(f, matrixVec_[curRegister]);
    }
    catch (MatrixException &e)
    {
        os << e.ExceptionMessage << std::endl;
    }
}
