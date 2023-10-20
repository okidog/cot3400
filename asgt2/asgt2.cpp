#include <iostream>
#include <ctime>
using namespace std;

const int INT_SIZE = 10;
const int MATRIX_SIZE_INIT = 99;

class Matrix {
public:
    int size = 0;
    int matrix[MATRIX_SIZE_INIT][MATRIX_SIZE_INIT] = {0};
    int matrix2[MATRIX_SIZE_INIT][MATRIX_SIZE_INIT] = {0};
    int multMatrix[MATRIX_SIZE_INIT][MATRIX_SIZE_INIT] = {0}; // Multiplied matrix for standard algorithm
    int strassenMatrix[MATRIX_SIZE_INIT][MATRIX_SIZE_INIT] = {0}; // Multiplied matrix for Strassen's algorithm
    Matrix() {
        cout << "Enter the size of the matrix: " << endl;
        cin >> size;
        for (int i = 0; i < size; i++) { /// Generate matrix with rand values
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
                switch (matrixSel){
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
        cout << endl << "This process took " << clock() - cycles << " cycles." << endl;
        printMatrix(3);
    }
};

int main() {
    Matrix matrix;
    matrix.matrixMult();
    return 0;
}
