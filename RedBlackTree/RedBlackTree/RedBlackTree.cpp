#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include "RBTree.hpp"

using namespace std;

int main() {
    RedBlackTree<int> rbTree;

    int arr[50];

    srand(GetTickCount());

    int count = 0;

    while(count < 50){
        int tmp = rand() % 100 + 1;
        int isSame = 0;
        for (int i = 0; i < 50; i++){
            if(tmp == arr[i]){
                isSame = 1;
                break;
            }
        }
        if(isSame == 0){
            arr[count] = tmp;
            rbTree.insert(arr[count]);
            count++;
        }
    }

    cout << "Red-Black Tree:" << endl;
    rbTree.printTree(rbTree.getRoot());

    return 0;
}
