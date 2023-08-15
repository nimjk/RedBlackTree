#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <atomic>
#include <mutex>
#include <thread>
#include <vector>
#include "RBTree.hpp"

using namespace std;

int main() {
    RedBlackTree<int> rbTree;

    int arr[2000];

    srand(GetTickCount());

    int count = 0;

    while(count < 2000){
        int tmp = rand() % 5000 + 1;
        int isSame = 0;
        for (int i = 0; i < 2000; i++){
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
