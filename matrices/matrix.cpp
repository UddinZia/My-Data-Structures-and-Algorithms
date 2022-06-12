#include <iostream>
#include <fstream>
#include <string>
#include <vector>


#include "matrix.h"

using  std::string, std::vector, std::cout, std::endl, std::fstream, std::stoi, std::ofstream;

Matrix::Matrix() : rows{0}, columns{0} {}

Matrix::Matrix(const Matrix& other) : matrix{other.matrix}, rows{other.getRows()}, columns{other.getColumns()} {}// copy constructor

Matrix::~Matrix() {}// destructor


Matrix& Matrix::operator=(const Matrix& other) // copy assignment operator
{
    rows = other.getRows();
    columns = other.getColumns();
    matrix = other.matrix;

    return *this;
}

void Matrix::file_to_matrix(char* filename) 
{
    fstream matrixFile;
    matrixFile.open(filename);

    if (!matrixFile.is_open())
    {
        matrixFile.close();
        throw std::invalid_argument("file cannot open or does not exist");
    }

    string lineRow, lineCol; // converted to row and column
    getline(matrixFile, lineRow);
    getline(matrixFile, lineCol);

    rows = stoi(lineRow); // stoi will throw invalid arugment if string can't be converted to int
    columns = stoi(lineCol);

    // set size of matrix to row and col
    matrix.resize(rows);
    for (size_t i = 0; i < rows; i++)
    {
        matrix.at(i).resize(columns);
    }

    // extract and insert coefficient in row, col order 
    string coeff;
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            matrixFile >> coeff;
            matrix.at(i).at(j) = stoi(coeff); 
        }

    }
}

void Matrix::matrix_to_file(char* filename) 
{
    ofstream matrixOutput;

    matrixOutput.open(filename);

    matrixOutput << rows << endl;
    matrixOutput << columns << endl;

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            if (j == (columns - 1))
            {
                matrixOutput << matrix.at(i).at(j) << "";
            }
            else
            {
                matrixOutput << matrix.at(i).at(j) << " ";
            }
        }
        matrixOutput << endl;
    }
}

// Task 1
vector<int> Matrix::multiply_vector(vector<int> B) 
{
    if (columns != B.size())
    {
       
       throw std::invalid_argument("columns of matrix does not equal rows of vector"); 
    }
    vector<int> C;

    
    for (size_t i = 0; i < rows; i++)
    {
        int coeff = 0;
        for (size_t j = 0; j < columns; j++)
        {
            coeff += (matrix.at(i).at(j) * B.at(j)); 
        }
        C.push_back(coeff);
    }
    return C;
}

int Matrix::count_mults(vector<int> B) 
{
    if (columns != B.size())
    {
       throw std::invalid_argument("columns of matrix does not equal rows of vector"); 
    }

    return (columns*rows);
}

int Matrix::count_adds(vector<int> B) 
{
    if (columns != B.size())
    {
       throw std::invalid_argument("columns of matrix does not equal rows of vector"); 
    }

    return rows* (columns - 1);
}

// Task 2
Matrix Matrix::multiply(Matrix B)
{
    
    
    if (!this->is_multipliable(B))
    {
        throw std::invalid_argument("matrices are not multipliable");
    }

    // new matrix will have row of matrix A and column of matrix B
    Matrix product;
    product.rows = rows;
    product.columns = B.getColumns();

    product.matrix.resize(product.rows);
    
    for (size_t i = 0; i < rows; i++)
    {
        product.matrix.at(i).resize(product.columns);
    }
    

    for (size_t i = 0; i < rows; i++) // row of matrix A
    {
        for (size_t j = 0; j < product.columns; j++) // col of matrix B
        {        
            for (size_t k = 0; k < columns; k++) // column of matrix A
            {
                product.matrix.at(i).at(j) += (matrix.at(i).at(k) * B.matrix.at(k).at(j));
            }
        }
    }

    return product;
}

Matrix Matrix::transpose() 
{
    Matrix transpose;
    transpose.rows = columns;
    transpose.columns = rows;
    
    transpose.matrix.resize(transpose.rows); // swap rows and cols of matrix 
    for (size_t i = 0; i < transpose.rows; i++)
    {
        transpose.matrix.at(i).resize(transpose.columns);
    }

    for (size_t i = 0; i < transpose.rows; i++)
    {
        for (size_t j = 0; j < transpose.columns; j++)
        {
            transpose.matrix.at(i).at(j) = matrix.at(j).at(i);
        }
    }
    return transpose;
}

int Matrix::count_mults(Matrix B) 
{
    if (!this->is_multipliable(B))
    {
        throw std::invalid_argument("matrices are not multipliable");
    } 
    return (rows * columns * B.columns);
}

int Matrix::count_adds(Matrix B) 
{
    if (!this->is_multipliable(B))
    {
        throw std::invalid_argument("matrices are not multipliable");
    } 

    return rows * B.columns * (columns - 1);
}

bool Matrix::is_multipliable(Matrix B) 
{
    return (columns == B.getRows());
}

// Task 3
Matrix Matrix::kronecker(Matrix B) 
{
    Matrix kronecker;
    kronecker.rows = B.rows * rows;
    kronecker.columns = B.columns * columns;

    kronecker.matrix.resize(kronecker.rows); 
    for (size_t i = 0; i < kronecker.rows; i++)
    {
        kronecker.matrix.at(i).resize(kronecker.columns);
    }


    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < B.rows; j++)
        {   
            for (size_t k = 0; k < columns; k++)
            {
                for (size_t m = 0; m < B.columns; m++)
                {
                    kronecker.matrix.at(B.rows * i + j).at(B.columns * k + m) = matrix.at(i).at(k) * B.matrix.at(j).at(m);
                }
            }
        }
    }
    
    return kronecker;
}


int Matrix::count_mults_kron(Matrix B) 
{
    return rows * B.rows * columns * B.columns; 
}


// my functions
size_t Matrix::getRows() const
{
    return rows;
}

size_t Matrix::getColumns() const
{
    return columns;
}

void Matrix::displayMatrix() const
{
    
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            cout << matrix.at(i).at(j) << " ";
        }
         cout << endl;
    }
    cout << endl;
}

