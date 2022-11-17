#include<locale>

#include "Matrix.cpp"
#include "Matrix_complex.cpp"

double Matrix<double>::_accuracy = 0.15;

int main() {
	setlocale(LC_ALL, "ru");

	
	Matrix<std::complex<float>> first(3, 3, 3);

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			first(i, j) = std::complex<float>(rand() % 10, rand() % 10);
		}
	}
	
	/*Matrix<int> first(5, 5, 3);
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; j++) {
			first(i, j) = rand() % 100;
		}
	}

	Matrix<int> fourth(5, 5, 5);
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; j++) {
			fourth(i, j) = rand() % 100;
		}
	}*/

	Matrix<std::complex<float>> fourth(3, 3, 3);

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			fourth(i, j) = std::complex<float>(rand() % 10, rand() % 10);
		}
	}

	/*Matrix<double> second(5, 5, 5);

	
	Matrix<float> third(5, 5, 5);

	

	Matrix<std::complex<float>> fifth(5, 5, 5);*/

	std::cout << first << fourth << std::endl;

	std::cout <<  first * fourth ;

	std::cout << matrix_transformation(first);

	return 0;
}