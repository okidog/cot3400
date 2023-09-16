#include <iostream>
#include <ctime>
using namespace std;

void merge(int leftInd, int midInd, int rightInd);
const int LENGTH = 10000; // Const int to change list length
int list[LENGTH] = {0};

void generateList() {
    for (int i = 0; i < LENGTH; i++) {
        list[i] = rand() % 100000;
    }
}

void printList() {
    for (int i = 0; i < LENGTH; i++) {
        cout << list[i] << " ";
    }
}

void insertionSort() {
    int temp = 0;
    int tmpIndex = 0;
    float timeStarted = clock();
    for (int i = 1; i < LENGTH; i++) {
        if (list[i] < list[i-1]) {
            tmpIndex = i;
            while (list[tmpIndex] < list[tmpIndex-1]) {
                temp = list[tmpIndex-1];
                list[tmpIndex-1] = list[tmpIndex];
                list[tmpIndex] = temp;
                tmpIndex--;
            }
        }
    }
    float timeElapsed = clock() - timeStarted;
    cout << endl << "The following insertion sort took " << timeElapsed << " cycles, or " << timeElapsed / CLOCKS_PER_SEC << " seconds." << endl;
}

void mergeSort(int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        merge(left, mid, right);
    }
}

void merge(int leftInd, int midInd, int rightInd) { // Left, middle, right indeces
    int n1 = midInd - leftInd + 1;
    int n2 = rightInd - midInd;
    int L[n1], M[n2];

    for (int i = 0; i < n1; i++)
        L[i] = list[leftInd + i];
    for (int j = 0; j < n2; j++)
        M[j] = list[midInd + 1 + j];

    int i, j, k; // Indexes of sub-arrays, main array
    i = 0;
    j = 0;
    k = leftInd;

    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) {
            list[k] = L[i];
            i++;
        } else {
            list[k] = M[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        list[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        list[k] = M[j];
        j++;
        k++;
    }
}

int main() {
    srand(time(0));
    generateList();
    int time = clock();
    mergeSort(0, LENGTH-1);
    cout << "The following merge sort took " << clock() - time << " cycles, or "
    << (float)(clock() - time) / CLOCKS_PER_SEC << " seconds." << endl;
    printList();
    generateList();
    insertionSort();
    printList();
    return 0;
};