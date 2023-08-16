#include <iostream> 
#include <vector>
#include <random>
#include "linked_list.h"
using namespace std;

int main() {
    // 난수 발생
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 5000);

    // reference vector 생성.
    vector<int> reference;

    // linked list 생성.
    LinkedList<int> intList;

    // 2000번 반복해서 Linked List 생성.
    for (int i = 0; i <= 2000; i++)
    {
        int randomValue = dis(gen);
        if(i == 0)
        {
            reference.push_back(randomValue);
            intList.insert(randomValue);
        }


        for (int j = 0; j <= reference.size(); j++)
        {
            // Linked_list에 data를 넣기 전, reference vector를 활용해 중복 검사.
            if (randomValue == reference[i])
            {
                break;
            }
            else
            {
                // 중복 X -> linked_list 첨가.
                reference.push_back(randomValue);
                intList.insert(randomValue);
            }
        }
    }

    // 생성된 Linked List 배열.
    for (int i = 0; i < reference.size(); i++) {
        cout << reference[i] << "->";
    }
    

    return 0;
};