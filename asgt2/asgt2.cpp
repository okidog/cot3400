#include <iostream>
using namespace std;

const int INT_SIZE = 10;

class Matrix {
public:
    int size = 0;
    int matrix[99][99] = {0};
    int multMatrix[99][99] = {0}; // Multiplied matrix for standard algorithm
    int strassenMatrix[99][99] = {0}; // Multiplied matrix for Strassen's algorithm
    Matrix() {
        cout << "Enter the size of the matrix: " << endl;
        cin >> size;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                matrix[i][j] = rand() % INT_SIZE;
            }
        }
    }
    void printMatrix() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << matrix[i][j] << ' ';
            }
            cout << endl;
        }
    }
    void matrixMult() {
        for (int i = 0; i < size/2; i++) {         // quadrant I
            for (int j = 0; j < size/2; i++) {

            }
        }
        for (int i = size/2; i < size; i++) {         // quadrant II
            for (int j = 0; j < size/2; i++) {

            }
        }
        for (int i = 0; i < size/2; i++) {         // quadrant III
            for (int j = size/2; j < size; i++) {

            }
        }
        for (int i = size/2; i < size; i++) {         // quadrant IV
            for (int j = size/2; j < size; i++) {

            }
        }
    }
};

int main() {
    Matrix matrix;
    matrix.printMatrix();
    return 0;
}
