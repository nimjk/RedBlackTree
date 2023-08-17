#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <atomic>
#include <mutex>
#include <thread>
#include <vector>
#include "RBTree.hpp"
#include "SpinLock.hpp"

using namespace std;

int main() {
    RedBlackTree<int> rbTree;

    int arr[2000];

    srand(GetTickCount());

    int count = 0;
    clock_t start, end;
    double duration;

    start = clock();
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
    end = clock();

    duration = (double)(end - start) / CLOCKS_PER_SEC;

    cout << "Red-Black Tree:" << endl;
    rbTree.printTree(rbTree.getRoot());
    cout << "Time of generation tree : " << duration << "초\n";

    int searchcnt = 0;


    double mintime, maxtime;
    double totaltime = 0;
    double meantime = 0;


    while(searchcnt < 100){
        int searchidx = rand() % 2000;
        int searchnum = rand() % 5000+1;

        start = clock();
        rbTree.search(searchnum);
        end = clock();

        duration = (double)(end - start) / CLOCKS_PER_SEC;

        if(searchcnt == 0){
            mintime = duration;
            maxtime = duration;
        }

        else{
            if(mintime > duration){
                mintime = duration;
            }
            else if(maxtime < duration){
                maxtime = duration;
            }
        }

        totaltime += duration;

        searchcnt++;
    }

    meantime = totaltime / (searchcnt+1);

    cout << "minimum time of search : " << mintime << "초\n";
    cout << "maximum time of search : " << maxtime << "초\n";
    cout << "total time of search : " << totaltime << "초\n";
    cout << "average time of search : " << meantime << "초\n";
    
     

    return 0;
}
