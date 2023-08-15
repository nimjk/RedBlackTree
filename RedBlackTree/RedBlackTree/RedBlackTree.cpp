#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "RBTree.hpp"

using namespace std;

int main() {
    RedBlackTree<int> rbTree;

    int arr[50];

    srand(unsigned int(time(0)));

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

    cout << "In-order traversal of the tree: ";
    rbTree.inOrderTraversal(rbTree.getRoot());
    cout << endl;

    

    return 0;
}
