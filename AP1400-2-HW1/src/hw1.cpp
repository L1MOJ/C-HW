#include "hw1.h"
#include <vector>
#include <random>
#include <iomanip>
#include <iostream>

using std::logic_error;
using std::size_t;
using namespace std;

namespace algebra{

Matrix CreateMatrix(size_t n, size_t m, double v) {
    if (n <= 0 || m <= 0) {
        throw logic_error("wrong col or row\n");
    }
    Matrix x;
    for (int i = 0; i < n; i++) {
        std::vector<double> vect(m, v);
        x.push_back(vect);
    }
    return x;
}

Matrix zeros(size_t n, size_t m) {
    return CreateMatrix(n, m, 0);
}

Matrix ones(size_t n, size_t m) {
    return CreateMatrix(n, m, 1);
}

Matrix random(size_t n, size_t m, double min, double max) {
    if (min > max ) {
        throw logic_error("Invalid input parameters!\n");
    }

    Matrix x = zeros(n, m);

    uniform_real_distribution<double> unif(min, max);
    default_random_engine re;
 
    // for (int i = 0; i < n; i++) {
    //     for( int j = 0; i < m; j++) {
    //         x[i][j] = unif(re);
    //     }
    // }
    // Iterator
    for (auto row = x.begin(); row != x.end(); row ++) {
        for (auto col = row->begin(); col != row->end(); col++) {
            *col = unif(re);
        }
    }
    return x;
}

void show(const Matrix& matrix) {
    for (auto row = matrix.begin(); row != matrix.end(); row ++) {
        for (auto col = row->begin(); col != row->end(); col++) {
          cout << setprecision(4) << *col ;
        }
        cout << endl;
    }
}

Matrix multiply(const Matrix& matrix, double c) {
    if (matrix.size() == 0)
    {
        return matrix;
    }
    int n = matrix.size();
    int m = matrix[0].size();
    Matrix temp = zeros(n, m);  
    for (int i = 0; i < n; i++) {
        for( int j = 0; j < m; j++) {
            temp[i][j] = matrix[i][j] * c;
        }
    }
    return temp;
}

Matrix multiply(const Matrix& matrix1, const Matrix& matrix2) {
    if (matrix1.empty() && matrix2.empty()) {
        return Matrix{};
    }

    if (matrix1.empty() || matrix2.empty()) {
        throw logic_error("calculation error\n");
    }

    if (matrix1[0].size() != matrix2.size()) {
        throw logic_error("dimenssion errors\n");
    }

    auto m{matrix1.size()};
    auto n{matrix2[0].size()};

    auto x{zeros(m, n)};

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < matrix2.size(); k++) {
                x[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return x;
}

Matrix sum(const Matrix& matrix, double c) {
    if (matrix.empty())
    {
        return Matrix{};
    }
    int n = matrix.size();
    int m = matrix[0].size();
    Matrix temp = zeros(n, m);  
    for (int i = 0; i < n; i++) {
        for( int j = 0; j < m; j++) {
            temp[i][j] = matrix[i][j] + c;
        }
    }
    return temp;
}

Matrix sum(const Matrix& matrix1, const Matrix& matrix2) {
    if (matrix1.empty() && matrix2.empty()) {
        return Matrix{};
    }

    if (matrix1.empty() || matrix2.empty())
    {
        throw logic_error("Empty adder");
    }

    if(matrix1.size() != matrix2.size() || matrix1[0].size() != matrix2[0].size()) {
        throw logic_error("Not compatible");
    }
    
    int n = matrix1.size();
    int m = matrix1[0].size();

    Matrix temp = zeros(n,m);

    for (int i = 0; i < n; i++) {
        for( int j = 0; j < m; j++) {
            temp[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    return temp; 
}

Matrix transpose(const Matrix& matrix) {
    if (matrix.empty()) {
        return Matrix{};
    }

    int n = matrix.size();
    int m = matrix[0].size();

    Matrix temp = zeros(m, n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            temp[j][i] = matrix[i][j];
        }
    }
    return temp;
}

Matrix minor(const Matrix& matrix, size_t n, size_t m) {
    
}
}