#pragma once

#include <cstdio>
#include <cstddef>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <fstream>

inline namespace matrixNamespace
{
  class Matrix
  {
  public:
    Matrix(int r = 0, int c = 0);
    Matrix(const Matrix &other);
    ~Matrix();

    int get_rows() const;
    int get_cols() const;
    void set(int i, int j, int val);
    int get(int i, int j) const;
    static void load(std::ifstream &, Matrix &);

    Matrix operator+(const Matrix &m) const;
    Matrix operator-(const Matrix &m) const;
    Matrix operator*(const Matrix &m) const;

    Matrix &operator=(Matrix m);

    Matrix &operator+=(const Matrix &m);
    Matrix &operator-=(const Matrix &m);
    Matrix &operator*=(const Matrix &m);

    bool operator==(const Matrix &m) const;
    bool operator!=(const Matrix &m) const;

  private:
    int _rows;
    int _cols;
    std::vector<std::vector<int>> _data;
  };
  class MatrixException
  {
  public:
    std::string ExceptionMessage;
    MatrixException(const std::string &);
  };

  class MatrixHolder
  {
  public:
    MatrixHolder();
    ~MatrixHolder();
    void load(std::istream &, std::ostream &);
    void print(std::istream &, std::ostream &);
    void mul(std::istream &, std::ostream &);
    void elem(std::istream &, std::ostream &);
    void add(std::istream &, std::ostream &);

  private:
    std::vector<Matrix> matrixVec_;
  };
}