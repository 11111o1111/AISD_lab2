#include<iostream>
#include<stdexcept>
#include<iomanip>

#pragma once

template<typename T>
class Matrix {
private:
	size_t _n, _m;
	T** _matrix;

	static Matrix<T> creating_line(const Matrix<T>& source, int number) {
		Matrix<T> temp(1, source._m, 0);
		for (size_t i = 0; i < source._m; ++i) {
			temp(0, i) = source(number, i);
		}
		return temp;
	}

	static void combining_vector(const Matrix<T>& source, int number1, const Matrix<T>& destination, int number2) {
		for (size_t i = 0; i < source._m; ++i) {
			destination(number2, i) = source(number1, i);
		}
	}
public:

	static double _accuracy;

	static void set_accuracy(double value) {
		_accuracy = value;
	}

	Matrix(): _n(1), _m(1) {
		_matrix = new T* [_n];
		for (size_t i = 0; i < _n; ++i) {
			_matrix[i] = new T[_m];
		}
		for (size_t i = 0; i < _n; ++i) {
			for (size_t j = 0; j < _m; ++j) {
				_matrix[i][j] = 0;
			}
		}
	}

	Matrix(size_t n, size_t m, const T& value) {
		if (n <= 0 || m <= 0)
			throw(std::logic_error("incorrect dimensions of the matrix"));
		_n = n;
		_m = m;
		_matrix = new T * [_n];
		for (size_t i = 0; i < _n; ++i) {
			_matrix[i] = new T[_m];
		}
		for (size_t i = 0; i < _n; ++i) {
			for (size_t j = 0; j < _m; ++j) {
				_matrix[i][j] = value;
			}
		}
	}

	Matrix(const Matrix<T>& b) : Matrix<T>(b._n, b._m, 0) {
		for (size_t i = 0; i < _n; ++i) {
			for (size_t j = 0; j < _m; ++j) {
				_matrix[i][j] = b._matrix[i][j];
			}
		}
	}

	~Matrix() {
		for (size_t i = 0; i < _n; ++i) {
			delete[] _matrix[i];
		}
		delete[] _matrix;
	}

	T& operator()(size_t n, size_t m) const {
		if (n < 0 || n > _n || m < 0 || m > _m)
			throw std::out_of_range("invalid index");
		return _matrix[n][m];
	}

	Matrix<T> operator+(const Matrix<T>& obj) const {
		if (_n != obj._n || _m != obj._m)
			throw std::logic_error("size mismatch");
		Matrix temp_matrix(*this);
		for (size_t i = 0; i < _n; ++i) {
			for (size_t j = 0; j < _m; ++j) {
				temp_matrix(i, j) += obj._matrix[i][j];
			}
		}
		return temp_matrix;
	}

	Matrix<T> operator-(const Matrix<T>& obj) const {
		if (_n != obj._n || _m != obj._m)
			throw std::logic_error("size mismatch");
		Matrix temp_matrix(*this);
		for (size_t i = 0; i < _n; ++i) {
			for (size_t j = 0; j < _m; ++j) {
				temp_matrix(i, j) -= obj._matrix[i][j];
			}
		}
		return temp_matrix;
	}

	Matrix<T> operator*(const Matrix<T>& obj) const {
		if (_m != obj._n)
			throw std::logic_error("size mismatch");
		Matrix<T> temp_matrix(_n, obj._m, 0);
		for (size_t i = 0; i < _n; ++i) {
			for (size_t j = 0; j < obj._m; ++j) {
				for (size_t k = 0; k < _m; ++k) {
					temp_matrix(i, j) += _matrix[i][k] * obj._matrix[k][j];
				}
			}
		}
		return temp_matrix;
	}

	Matrix<T>& operator*(double value) {
		for (size_t i = 0; i < _n; ++i) {
			for (size_t j = 0; j < _m; ++j) {
				_matrix[i][j] *= value;
			}
		}
		return *this;
	}

	friend Matrix<T>& operator*(double value, Matrix<T>& obj) {
		for (size_t i = 0; i < obj._n; ++i) {
			for (size_t j = 0; j < obj._m; ++j) {
				obj._matrix[i][j] *= value;
			}
		}
		return obj;
	}

	Matrix<T>& operator/(const T& value) {
		if (value == 0)
			throw std::logic_error("division by zero");
		for (size_t i = 0; i < _n; ++i) {
			for (size_t j = 0; j < _m; ++j) {
				_matrix[i][j] /= value;
			}
		}
		return *this;
	}

	bool operator==(const Matrix<T>& obj) const {
		if (_n != obj._n || _m != obj._m)
			return false;
		for (size_t i = 0; i < _n; ++i) {
			for (size_t j = 0; j < _m; ++j) {
				if (fabs(_matrix[i][j] - obj._matrix[i][j]) > _accuracy)
					return false;
			}
		}
		return true;
	}

	bool operator!=(const Matrix<T>& obj) const {
		if (*this == obj)
			return false;
		return true;
	}

	friend std::ostream& operator<<(std::ostream& out, const Matrix<T>& obj) {
		for (size_t i = 0; i < obj._n; ++i) {
			for (size_t j = 0; j < obj._m; ++j) {
				out << std::fixed << std::setprecision(2);
				out << "\t" << obj._matrix[i][j];
			}
			out << "\n";
		}
		system("pause");
		return out;
	}

	friend Matrix<T> matrix_transformation(const Matrix<T>& obj) {
		if (obj._m != obj._n)
			throw std::logic_error("not a square matrix");

		Matrix<T> new_matrix(obj);
		for (int j = obj._m - 1; j > 0; --j) {
			for (int i = 0; i < j; ++i) {
				if (new_matrix(i, j) != 0) {
					int k = j;
					if (new_matrix(k, j) == 0) {
						while (new_matrix(k, j) == 0) {
							++k;
						}
						Matrix<T> temp_arr_3 = Matrix::creating_line(new_matrix, j);
						Matrix<T>::combining_vector(new_matrix, k, new_matrix, j);
						Matrix<T>::combining_vector(temp_arr_3, 0, new_matrix, k);
					}
					double temp = (double)new_matrix(i, j) / new_matrix(j, j);
					Matrix<T> temp_arr_1 = Matrix<T>::creating_line(new_matrix, i);
					Matrix<T> temp_arr_2 = Matrix<T>::creating_line(new_matrix, j);
					Matrix<T> result = temp_arr_1 - (temp_arr_2 * temp);
					Matrix<T>::combining_vector(result, 0, new_matrix, i);
				}
			}
		}
		return new_matrix;
	}
};