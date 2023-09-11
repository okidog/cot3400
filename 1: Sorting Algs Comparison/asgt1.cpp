#include <iostream>
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

int main() {
    generateList();
    printList();
    return 0;
};