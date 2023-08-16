#include <iostream>
#include <vector>
using namespace std;

// Node 클래스 템플릿 정의
template <typename T>
class Node {
public:
    T data;
    Node* next;

    Node(T value) : data(value), next(nullptr) {}
};

// LinkedList 클래스 템플릿 정의
template <typename T>
class LinkedList {
  private:
    Node<T>* head;
  public:
    LinkedList() : head(nullptr) {}

    // 리스트에 새로운 노드 추가
    void insert(T value) {
        Node<T>* newNode = new Node<T>(value);
        
        if (head == nullptr) {
            head = newNode;
        } else {
            Node<T>* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    // 리스트에서 특정 값 찾기
    bool search(T value) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // 리스트에서 특정 값 삭제
    void remove(T value) {
        if (head == nullptr) {
            return;
        }

        if (head->data == value) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node<T>* current = head;
        while (current->next != nullptr) {
            if (current->next->data == value) {
                Node<T>* temp = current->next;
                current->next = current->next->next;
                delete temp;
                return;
            }
            current = current->next;
        }
    }

     //첫 번째 노드 가져오기
    Node<T>* getHead() 
    {
        return head;
    }

    // LinkedList 소멸자
    ~LinkedList() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
    }
};

