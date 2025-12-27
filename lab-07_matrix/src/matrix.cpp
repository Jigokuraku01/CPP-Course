#include "matrix.h"

Matrix::Matrix(size_t r, size_t c): _rows(r), _cols(c) {
	int* tmp_data = new int[get_rows() * get_cols()];
	_data = new int* [get_rows()];
	for (size_t i = 0; i < get_rows(); ++i)
	{
		_data[i] = i * get_cols() + tmp_data;
		for (size_t j = 0; j < get_cols(); ++j)
			_data[i][j] = 0;
	}

}

Matrix::~Matrix() {
	delete[] _data[0];
	delete[] _data;
}

Matrix::Matrix(const Matrix& other): _rows(other._rows), _cols(other._cols) {
	/*Тут я хоткл сделать вот такой мудрый ход:
	this = &Matrix(_rows, _cols);
	Но возникли ошибки с rvalue и lvalue, поэтому получилось нехитро*/

	int* tmp_data = new int[get_rows() * get_cols()];
	_data = new int* [get_rows()];
	for (size_t i = 0; i < get_rows(); ++i)
		_data[i] = i * get_cols() + tmp_data;

	for (size_t i = 0; i < get_rows(); ++i)
		for (size_t j = 0; j < get_cols(); ++j)
			set(i, j, other.get(i, j));
}

size_t Matrix::get_rows() const {
	return _rows;
}

size_t Matrix::get_cols() const {
	return _cols;
}

void Matrix::set(size_t i, size_t j, int val) {
	if (i >= get_rows() || j >= get_cols())
		throw std::runtime_error("incorrect index");
	_data[i][j] = val;
}

int Matrix::get(size_t i, size_t j) const {
	if (i >= get_rows() || j >= get_cols())
		throw std::runtime_error("incorrect index");
	return _data[i][j];
}

void Matrix::print(FILE *f) const {
	for (size_t i = 0; i < get_rows(); ++i)
		for (size_t j = 0; j < get_cols(); ++j)
			if (j + 1 != get_cols())
				fprintf(f, "%d ", _data[i][j]);
			else
				fprintf(f, "%d\n", _data[i][j]);
}

Matrix& Matrix::operator=(const Matrix& m) {
	delete[] _data[0];
	delete[] _data;
	_rows = m.get_rows();
	_cols = m.get_cols();
	int* tmp_data = new int[get_rows() * get_cols()];
	_data = new int* [get_rows()];
	for (size_t i = 0; i < get_rows(); ++i)
		_data[i] = i * get_cols() + tmp_data;

	for (size_t i = 0; i < get_rows(); ++i)
		for (size_t j = 0; j < get_cols(); ++j)
			set(i, j, m.get(i, j));
	return *this;
}

Matrix Matrix::operator+(const Matrix& m) const {
	if (get_rows() != m.get_rows() || get_cols() != m.get_cols())
		throw std::runtime_error("incorrect size of vectors");
	Matrix ans(get_rows(), get_cols());
	for (size_t i = 0; i < get_rows(); ++i)
		for (size_t j = 0; j < get_cols(); ++j)
			ans.set(i, j, get(i, j) + m.get(i, j));
	return ans;
}

Matrix Matrix::operator-(const Matrix& m) const {
	if (get_rows() != m.get_rows() || get_cols() != m.get_cols())
		throw std::runtime_error("incorrect size of vectors");
	Matrix ans(get_rows(), get_cols());
	for (size_t i = 0; i < get_rows(); ++i)
		for (size_t j = 0; j < get_cols(); ++j)
			ans.set(i, j, get(i, j) - m.get(i, j));
	return ans;
}

Matrix Matrix::operator*(const Matrix& m) const {
	if (get_cols() != m.get_rows())
		throw std::runtime_error("incorrect size of vectors");
	Matrix ans(get_rows(), m.get_cols());
	for (size_t i = 0; i < get_rows(); ++i)
		for (size_t j = 0; j < m.get_cols(); ++j)
			for (size_t k = 0; k < get_cols(); ++k)
				ans.set(i, j, ans.get(i, j) + get(i, k) * m.get(k, j));
	return ans;
}

bool Matrix::operator==(const Matrix& m) const {
	if (get_rows() != m.get_rows() || get_cols() != m.get_cols())
		return false;
	for (size_t i = 0; i < get_rows(); ++i)
		for (size_t j = 0; j < get_cols(); ++j)
			if (get(i, j) != m.get(i, j))
				return false;
	return true;
}

bool Matrix::operator!=(const Matrix& m) const {
	return !(*this == m);
}

Matrix& Matrix::operator+=(const Matrix& m) {
	if (get_rows() != m.get_rows() || get_cols() != m.get_cols())
		throw std::runtime_error("incorrect size of vectors");
	for (size_t i = 0; i < get_rows(); ++i)
		for (size_t j = 0; j < get_cols(); ++j)
			set(i, j, get(i, j) + m.get(i, j));
	return *this;
}
Matrix& Matrix::operator-=(const Matrix& m) {
	if (get_rows() != m.get_rows() || get_cols() != m.get_cols())
		throw std::runtime_error("incorrect size of vectors");
	for (size_t i = 0; i < get_rows(); ++i)
		for (size_t j = 0; j < get_cols(); ++j)
			set(i, j, get(i, j) - m.get(i, j));
	return *this;
}
Matrix& Matrix::operator*=(const Matrix& m) {
	if (get_cols() != m.get_rows())
		throw std::runtime_error("incorrect size of vectors");
	Matrix tmp(*this * m);
	delete[] _data[0];
	delete[] _data;
	_rows = tmp.get_rows();
	_cols = tmp.get_cols();
	int* tmp_data = new int[get_rows() * get_cols()];
	_data = new int* [get_rows()];
	for (size_t i = 0; i < get_rows(); ++i)
	{
		_data[i] = i * get_cols() + tmp_data;
		for (size_t j = 0; j < get_cols(); ++j)
			set(i, j, tmp.get(i, j));
	}
	return *this;
}