#include <iostream>
#include <ctime>
using namespace std;

const int INT_SIZE = 10;
const int MATRIX_SIZE_INIT = 99;

class Matrix {
public:
    int size = 0;
    int matrix[MATRIX_SIZE_INIT][MATRIX_SIZE_INIT] = {0}; // Init to constant needed in order to cut down
    int matrix2[MATRIX_SIZE_INIT][MATRIX_SIZE_INIT] = {0}; // unnecessary memory usage
    int multMatrix[MATRIX_SIZE_INIT][MATRIX_SIZE_INIT] = {0}; // Multiplied matrix for standard algorithm
    int strassenMatrix[MATRIX_SIZE_INIT][MATRIX_SIZE_INIT] = {0}; // Multiplied matrix for Strassen's algorithm
    Matrix() {
        cout << "Enter the size of the matrix: " << endl;
        cin >> size;
        for (int i = 0; i < size; i++) { /// Generate 2 matrices with rand values
            for (int j = 0; j < size; j++) {
                matrix[i][j] = rand() % INT_SIZE;
                matrix2[i][j] = rand() % INT_SIZE;
            }
        }
        printMatrix(1);
        printMatrix(2);
    }

    void printMatrix(int matrixSel) {
        for (int i = 0; i < size; i++) { /// Display generated matrices
            for (int j = 0; j < size; j++) {
                switch (matrixSel) {
                    case 1:
                        cout << matrix[i][j] << ' ';
                        break;
                    case 2:
                        cout << matrix2[i][j] << ' ';
                        break;
                    case 3:
                        cout << multMatrix[i][j] << ' ';
                        break;
                    case 4:
                        cout << strassenMatrix[i][j] << ' ';
                        break;
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    void matrixMult() { /// i = row pos, j = column pos
        int cycles = clock();
        int result = 0;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                for (int k = 0; k < size; k++) {
                    result += matrix[i][k] * matrix2[k][j];
                }
                multMatrix[i][j] = result;
                result = 0;
            }
        }
        cout << endl << "This operation took " << clock() - cycles << " cycles." << endl;
        printMatrix(3);
    }
    void strassenMult() {
        int cycles = clock();
        int m1, m2, m3, m4, m5, m6, m7 = {0};
        for (int i = 0; i < size; i += 2) {
            for (int j = 0; j < size; j += 2) {
                m1 = (matrix[i][j] + matrix[i+1][j+1]) * (matrix2[i][j] + matrix2[i+1][j+1]); /// 7 calculations for each term
                m2 = (matrix[i+1][j] + matrix[i+1][j+1]) * matrix2[i][j];
                m3 = matrix[i][j] * (matrix2[i][j+1] - matrix2[i+1][j+1]);
                m4 = matrix[i+1][j+1] * (matrix2[i+1][j] - matrix2[i][j]);
                m5 = (matrix[i][j] + matrix[i][j+1]) * matrix2[i+1][j+1];
                m6 = (matrix[i+1][j] - matrix[i][j]) * (matrix2[i][j]+matrix2[i][j+1]);
                m7 = (matrix[i][j+1] - matrix[i+1][j+1]) * (matrix2[i+1][j]+matrix2[i+1][j+1]);

                strassenMatrix[i][j] = m1 + m4- m5 + m7;
                strassenMatrix[i][j+1] = m3 + m5;
                strassenMatrix[i+1][j] = m2 + m4;
                strassenMatrix[i+1][j+1] = m1 - m2 + m3 + m6;
            }
        }
        cout << "This operation took " << clock() - cycles << " cycles." << endl;
        printMatrix(4);
    }
};

int main() {
    Matrix matrix;
    matrix.matrixMult();
    matrix.strassenMult();
    return 0;
}
