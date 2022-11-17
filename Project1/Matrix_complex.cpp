#include<complex>

#include "Matrix.cpp"


#pragma once

template<typename T>
class Matrix<std::complex<T>> {
private:
	size_t _n, _m;
	std::complex<T>** _matrix;

	static Matrix<std::complex<T>> creating_line(const Matrix<std::complex<T>>& source, int number) {
		Matrix<std::complex<T>> temp(1, source._m, std::complex<T>(0, 0));
		for (size_t i = 0; i < source._m; ++i) {
			temp(0, i) = source(number, i);
		}
		return temp;
	}

	static void combining_vector(const Matrix<std::complex<T>>& source, int number1, const Matrix<std::complex<T>>& destination, int number2) {
		for (size_t i = 0; i < source._m; ++i) {
			destination(number2, i) = source(number1, i);
		}
	}

public:

	static double _accuracy;

	Matrix(size_t n, size_t m, const std::complex<T>& value) {
		if (n <= 0 || m <= 0)
			throw(std::logic_error("incorrect dimensions of the matrix"));
		_n = n;
		_m = m;
		_matrix = new std::complex<T>*[_n];
		for (size_t i = 0; i < _n; ++i) {
			_matrix[i] = new std::complex<T>[_m];
		}
		for (size_t i = 0; i < _n; ++i) {
			for (size_t j = 0; j < _m; ++j) {
				_matrix[i][j] = value;
			}
		}
	}

	std::complex<T>& operator()(size_t n, size_t m) const {
		if (n < 0 || n > _n || m < 0 || m > _m)
			throw std::out_of_range("invalid index");
		return _matrix[n][m];
	}

	Matrix<std::complex<T>> operator+(const Matrix<std::complex<T>>& obj) const {
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

	Matrix<std::complex<T>> operator-(const Matrix<std::complex<T>>& obj) const {
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

	Matrix<std::complex<T>> operator*(const Matrix<std::complex<T>>& obj) const {
		if (_m != obj._n)
			throw std::logic_error("size mismatch");
		Matrix<std::complex<T>> temp_matrix(_n, obj._m, 0);
		for (size_t i = 0; i < _n; ++i) {
			for (size_t j = 0; j < obj._m; ++j) {
				for (size_t k = 0; k < _m; ++k) {
					temp_matrix(i, j) += _matrix[i][k] * obj._matrix[k][j];
				}
			}
		}
		return temp_matrix;
	}

	Matrix<std::complex<T>>& operator*(std::complex<T> value) {
		for (size_t i = 0; i < _n; ++i) {
			for (size_t j = 0; j < _m; ++j) {
				_matrix[i][j] *= value;
			}
		}
		return *this;
	}


	friend Matrix < std::complex<T>>& operator*(std::complex<T> value, Matrix<std::complex<T>>& obj) {
		for (size_t i = 0; i < obj._n; ++i) {
			for (size_t j = 0; j < obj._m; ++j) {
				obj._matrix[i][j] *= value;
			}
		}
		return obj;
	}

	Matrix<std::complex<T>>& operator/(const std::complex<T>& value) {
		if (value == std::complex <T>(0, 0))
			throw std::logic_error("division by zero");
		for (size_t i = 0; i < _n; ++i) {
			for (size_t j = 0; j < _m; ++j) {
				_matrix[i][j] /= value;
			}
		}
		return *this;
	}

	bool operator==(const Matrix<std::complex<T>>& obj) const {
		if (_n != obj._n || _m != obj._m)
			return false;
		for (size_t i = 0; i < _n; ++i) {
			for (size_t j = 0; j < _m; ++j) {
				if (fabs(_matrix[i][j].real() - obj._matrix[i][j].real()) > _accuracy && _matrix[i][j].imag() == obj._matrix[i][j].imag())
					return false;
			}
		}
		return true;
	}

	bool operator!=(const Matrix<std::complex<T>>& obj) const {
		if (*this == obj)
			return false;
		return true;
	}

	friend std::ostream& operator<<(std::ostream& out, const Matrix<std::complex<T>>& obj) {
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

	friend Matrix<std::complex<T>> matrix_transformation(const Matrix<std::complex<T>>& obj) {
		if (obj._m != obj._n)
			throw std::logic_error("not a square matrix");

		Matrix<std::complex<T>> new_matrix(obj);
		for (int j = obj._m - 1; j > 0; --j) {
			for (int i = 0; i < j; ++i) {
				if (new_matrix(i, j) != std::complex<T>(0, 0)) {
					int k = j;
					if (new_matrix(k, j) == std::complex<T>(0, 0)) {
						while (new_matrix(k, j) == std::complex<T>(0, 0)) {
							++k;
						}
						Matrix<std::complex<T>> temp_arr_3 = Matrix::creating_line(new_matrix, j);
						Matrix<std::complex<T>>::combining_vector(new_matrix, k, new_matrix, j);
						Matrix<std::complex<T>>::combining_vector(temp_arr_3, 0, new_matrix, k);
					}
					std::complex<T> temp = new_matrix(i, j) / new_matrix(j, j);
					Matrix<std::complex<T>> temp_arr_1 = Matrix<std::complex<T>>::creating_line(new_matrix, i);
					Matrix<std::complex<T>> temp_arr_2 = Matrix<std::complex<T>>::creating_line(new_matrix, j);
					Matrix<std::complex<T>> result = temp_arr_1 - (temp_arr_2 * temp);
					Matrix<std::complex<T>>::combining_vector(result, 0, new_matrix, i);
				}
			}
		}
		return new_matrix;
	}
};