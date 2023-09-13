#include <iostream>
#include <ctime>
using namespace std;

const int LENGTH = 100; // Const int to change list length

int list[LENGTH] = {0};

void generateList() {
    for (int i = 0; i < LENGTH; i++) {
        list[i] = rand() % 10000;
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
    cout << endl << "This operation took " << timeElapsed << " cycles, or " << timeElapsed / CLOCKS_PER_SEC << " sec." << endl;
}

int main() {
    srand(time(0));
    generateList();
    printList();
    cout << endl;
    insertionSort();
    printList();
    return 0;
};