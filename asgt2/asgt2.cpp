#include <iostream>
#include <ctime>
using namespace std;
using type = int;
using Matrix = type * *;

const int INT_SIZE = 10;
const int SIZE = 1024;


Matrix randomize(Matrix randMatrix) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            randMatrix[i][j] = rand() % INT_SIZE;
        }
    }
    return randMatrix;
}
/* Requirements for Strassen's multiplication */
Matrix createMatrix(size_t N) {
    Matrix newMatrix = new type *[N];
    for (unsigned int i = 0; i < N; i++) {
        newMatrix[i] = new type[N];
    }
    return newMatrix;
}

Matrix matrixMult(Matrix matrix, Matrix matrix2) { /// i = row pos, j = column pos
    int cycles = clock();
    int result = 0;

    Matrix multMatrix = createMatrix(SIZE);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                result += matrix[i][k] * matrix2[k][j];
            }
            multMatrix[i][j] = result;
            result = 0;
        }
    }
    cout << endl << "This operation took " << (float)(clock() - cycles) / CLOCKS_PER_SEC << " seconds." << endl;
    return multMatrix;
}

Matrix add(Matrix A, Matrix B, size_t N) {

    Matrix C = createMatrix(N);

    for (unsigned int i = 0; i < N; i++)
        for (unsigned int j = 0; j < N; j++)
            C[i][j] = A[i][j] + B[i][j];

    return C;
}
Matrix subtract(Matrix A, Matrix B, size_t N) {
    Matrix C = createMatrix(N);

    for (unsigned int i = 0; i < N; i++)
        for (unsigned int j = 0; j < N; j++)
            C[i][j] = A[i][j] - B[i][j];

    return C;
}
Matrix sq_matrix_multiply(Matrix A, Matrix B, size_t N) {

    Matrix C = createMatrix(N);

    type sum = 0;									// O(1)

    for (unsigned int i = 0; i < N; i++) {						// O(n^3)
        for (unsigned int j = 0; j < N; j++) {
            for (size_t k = 0; k < N; k++) {
                sum += A[i][k] * B[k][j];				// O(1)
            }
            C[i][j] = sum;							// O(1)
            sum = 0;							// O(1)
        }
    }
    return C;
}
Matrix strassen(Matrix A, Matrix B, size_t N) {
    int cycles = clock();

    // Base case
    if (N == 1) {
        return sq_matrix_multiply(A, B, N);
    }

    // Create a new matrix to hold the result
    Matrix C = createMatrix(N);

    size_t K = N / 2;

    // New sub-matrices
    Matrix A11 = createMatrix(K);
    Matrix A12 = createMatrix(K);
    Matrix A21 = createMatrix(K);
    Matrix A22 = createMatrix(K);
    Matrix B11 = createMatrix(K);
    Matrix B12 = createMatrix(K);
    Matrix B21 = createMatrix(K);
    Matrix B22 = createMatrix(K);


    // Populate the values accordingly
    for (unsigned int i = 0; i < K; i++) {
        for (unsigned j = 0; j < K; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][K + j];		// Bug solved: I had a type: A22 instead of A12
            A21[i][j] = A[K + i][j];
            A22[i][j] = A[K + i][K + j];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][K + j];		// Bug solved: I had a type: B22 instead of B12
            B21[i][j] = B[K + i][j];
            B22[i][j] = B[K + i][K + j];
        }
    }

    // S
    Matrix S1 = subtract(B12, B22, K);
    Matrix S2 = add(A11, A12, K);
    Matrix S3 = add(A21, A22, K);
    Matrix S4 = subtract(B21, B11, K);
    Matrix S5 = add(A11, A22, K);
    Matrix S6 = add(B11, B22, K);
    Matrix S7 = subtract(A12, A22, K);
    Matrix S8 = add(B21, B22, K);
    Matrix S9 = subtract(A11, A21, K);
    Matrix S10 = add(B11, B12, K);

    // P
    Matrix P1 = strassen(A11, S1, K);
    Matrix P2 = strassen(S2, B22, K);
    Matrix P3 = strassen(S3, B11, K);
    Matrix P4 = strassen(A22, S4, K);
    Matrix P5 = strassen(S5, S6, K);
    Matrix P6 = strassen(S7, S8, K);
    Matrix P7 = strassen(S9, S10, K);

    // C_i
    Matrix C11 = subtract(add(add(P5, P4, K), P6, K), P2, K);				// P5 + P4 - P2 + P6
    Matrix C12 = add(P1, P2, K);								// P1 + P2
    Matrix C21 = add(P3, P4, K);								// P3 + P4
    Matrix C22 = subtract(subtract(add(P5, P1, K), P3, K), P7, K);				// P1 + P5 - P3 - P7

    // C
    for (unsigned int i = 0; i < K; i++) {
        for (unsigned int j = 0; j < K; j++) {

            C[i][j] = C11[i][j];

            C[i][j + K] = C12[i][j];

            C[K + i][j] = C21[i][j];

            C[K + i][K + j] = C22[i][j];
        }
    }

    // Return the result
    return C;
}

int main() {
    Matrix matrixA = randomize(createMatrix(SIZE));
    Matrix matrixB = randomize(createMatrix(SIZE));

    matrixMult(matrixA, matrixB);

    int cycles = clock();
    strassen(matrixA, matrixB, SIZE);
    cout << "This operation took " << (float)(clock() - cycles) / CLOCKS_PER_SEC << " seconds.";

    return 0;
}
