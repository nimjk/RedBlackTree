#include <iostream>
#include "RBTree.hpp"

int main() {
    RedBlackTree rbTree;

    rbTree.insert(10);
    rbTree.insert(5);
    rbTree.insert(15);
    rbTree.insert(3);
    rbTree.insert(7);
    rbTree.insert(12);
    rbTree.insert(18);

    // 이후에 트리의 상태를 확인하거나 다른 기능들을 테스트할 수 있습니다.

    return 0;
}
