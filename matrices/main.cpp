#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h> // time.h or chrono
#include <chrono> // time.h or chrono

#include "matrix.h"

using std::cout, std::endl, std::string, std::vector, std::fstream, std::stoi, std::cin, std::ofstream, std::to_string;



vector<int> file_to_vector(char* filename) 
{
    fstream vectorFile;
    vector<int> aVector;
    string coeff;
    vectorFile.open(filename);

    if (!vectorFile.is_open())
    {
        throw std::invalid_argument("file cannot open");
    }    

    size_t row, col;
    vectorFile >> row >> col;

    if (col > 1)
    {
        throw std::invalid_argument("more than column");
    }


    for (size_t i = 0; i < row; i++)
    {
        vectorFile >> coeff;
        aVector.push_back(stoi(coeff));
    }
    return aVector;
}

void vector_to_file(char* filename, vector<int> vector) 
{
    ofstream vectorOutput;

    vectorOutput.open(filename);
    vectorOutput << vector.size();
    vectorOutput << endl;
    vectorOutput << 1 << endl;

    for (size_t i = 0; i < vector.size(); i++)
    {
        vectorOutput << vector.at(i) << endl;
    }
}





int main() 
{
    /*
    Matrix test1,test2,test3;
    test1.file_to_matrix("matrix_3x5.txt");
    test2.file_to_matrix("matrix_5x5.txt");
    test3 = test1.multiply(test2);
    test3.matrix_to_file("rectangle.txt");
    cout << test1.count_adds(test2) << " " <<test1.count_mults(test2) << endl;
    */


    // Student's implementation
    
    string option;
    cout << "1. matrix-vector multiplication" << endl;
    cout << "2. matrix-matrix multiplication" << endl;
    cout << "3. matrix kronecker multiplication\n" << endl;
    cout << "4. kronecker runtime product (option for making runtime vs matrix size)" << endl;

    cout << "Enter option: ";
    cin >> option;

    string filenameA, filenameB, filenameC, filenameT;

    if (option == "1")
    {
        cout << "matrix A file name: ";
        cin >> filenameA;
        cout << "vector B file name: ";
        cin >> filenameB;
        cout << "vector C file name: ";
        cin >> filenameC;
        cout << endl;

        try
        {
            Matrix matrixA;
            matrixA.file_to_matrix(filenameA.data());
            vector<int> B = file_to_vector(filenameB.data());

            auto start = std::chrono::high_resolution_clock::now();
            vector<int> C = matrixA.multiply_vector(B);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> duration = end - start;


            vector_to_file(filenameC.data(), C);


            cout << "# of multiplications: " << matrixA.count_mults(B) << endl;
            cout <<"# of additions: " << matrixA.count_adds(B) << endl;
            cout << "Execution time of the multiplication of A and B: " << duration.count() << " seconds(s)" << endl;
        }
        catch (const std::invalid_argument& error)
        {
            ofstream emptyFile;
            emptyFile.open(filenameC.data());
            cout << "invalid operation" << endl;
        }
    }
    
    else if (option == "2")
    {
        cout << "matrix A file name: ";
        cin >> filenameA;
        cout << "matrix B file name: ";
        cin >> filenameB;
        cout << "matrix C file name: ";
        cin >> filenameC;
        cout << "matrix T file name: ";
        cin >> filenameT;
        cout << endl;

        try
        {
            Matrix matrixA, matrixB, matrixC, matrixT;

            matrixA.file_to_matrix(filenameA.data());
            matrixB.file_to_matrix(filenameB.data());

            auto start = std::chrono::high_resolution_clock::now();
            matrixC = matrixA.multiply(matrixB);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> duration = end - start;

            matrixC.matrix_to_file(filenameC.data());

            auto start1 = std::chrono::high_resolution_clock::now();
            matrixT = matrixC.transpose();
            auto end1 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> duration1 = end1 - start1;


            matrixT.matrix_to_file(filenameT.data());

            cout << "# of multiplications: " << matrixA.count_mults(matrixB) << endl;
            cout << "# of additions: " << matrixA.count_adds(matrixB) << endl;
            cout << "Execution time of the multiplication of A and B: " << duration.count() << " seconds(s)" << endl;
            cout << "Execution time of the transposal of C: " << duration1.count() << " seconds(s)" << endl;
        }
        catch(const std:: invalid_argument& error)
        {
            ofstream emptyFileC, emptyFileT;
            emptyFileC.open(filenameC.data());
            emptyFileT.open(filenameT.data());
            cout << "invalid operation" << endl;
        }
    }
    
    else if (option == "3")
    {
        cout << "matrix A file name: ";
        cin >> filenameA;
        cout << "matrix B file name: ";
        cin >> filenameB;
        cout << "matrix C file name: ";
        cin >> filenameC;
        cout << "matrix T file name: ";
        cin >> filenameT;
        cout << endl;

        try
        {
          Matrix matrixA, matrixB, matrixC, matrixT;

          matrixA.file_to_matrix(filenameA.data());
          matrixB.file_to_matrix(filenameB.data());

          auto start = std::chrono::high_resolution_clock::now();
          matrixC = matrixA.kronecker(matrixB);
          auto end = std::chrono::high_resolution_clock::now();
          std::chrono::duration<float> duration = end - start;

          matrixC.matrix_to_file(filenameC.data());
          
          auto start1 = std::chrono::high_resolution_clock::now();
          matrixT = matrixC.transpose();
          auto end1 = std::chrono::high_resolution_clock::now();
          std::chrono::duration<float> duration1 = end1 - start1;

          matrixT.matrix_to_file(filenameT.data());

          cout << "# of multiplications: " << matrixA.count_mults_kron(matrixB) << endl;
          cout << "Execution time of the kronecker product of A and B: " << duration.count() << " seconds(s)" << endl;
          cout << "Execution time of the transposal of C: " << duration1.count() << " seconds(s)" << endl;
          
        }
        catch(const std::invalid_argument& error)
        {
            ofstream emptyFileC, emptyFileT;
            emptyFileC.open(filenameC.data());
            emptyFileT.open(filenameT.data());

            cout << "invalid operation" << endl;
        }
    }
    else if (option == "4")
    {
        

        ofstream KroneckerRuntime;

        KroneckerRuntime.open("kroneckerRuntime(1).txt");


        for (int i = 10; i <= 200; i +=10)
        {
            Matrix MatrixA;
            Matrix MatrixB;

            string filenameA, filenameB;
            filenameA = "matrix_" + to_string(i) + "x" + to_string(i) + "_a.txt";
            filenameB = "matrix_" + to_string(i) + "x" + to_string(i) + "_b.txt";

            MatrixA.file_to_matrix(filenameA.data());  
            MatrixB.file_to_matrix(filenameB.data());

            auto start = std::chrono::high_resolution_clock::now();
            MatrixA.kronecker(MatrixB);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> duration = end - start;

            KroneckerRuntime << i << " " << duration.count() << endl;
            cout << "computing matrix of size: " << to_string(i) + "x" + to_string(i) << ", runtime: " << duration.count() << " seconds" << endl;
        }
        cout << "operation completed" << endl;
        
    }
    else
    {
        cout << "not valid option" << endl;
    }
    
    return 0;
}
