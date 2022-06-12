#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>
#include <vector>

using std::vector; 

class Matrix {
	private:
		vector<vector<int>> matrix; 
		size_t rows;
		size_t columns;
	public:
		Matrix();
		Matrix(const Matrix& other);
		~Matrix();
		Matrix& operator=(const Matrix& other);
		void file_to_matrix(char* filename);
		void matrix_to_file(char* filename);

		std::vector<int> multiply_vector(std::vector<int> B);
		int count_mults(std::vector<int> B);
		int count_adds(std::vector<int> B);

		Matrix multiply(Matrix B);
		Matrix transpose();
		int count_mults(Matrix B);
		int count_adds(Matrix B);
		bool is_multipliable(Matrix B);

		Matrix kronecker(Matrix B);
		int count_mults_kron(Matrix B);

		size_t getRows() const;
		size_t getColumns() const;
		void displayMatrix () const;
};

#endif  // MATRIX_H
