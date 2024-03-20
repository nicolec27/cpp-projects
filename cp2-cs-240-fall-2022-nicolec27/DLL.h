#ifndef DLL_H
#define DDL_H

#include <string>
#include <stdlib.h>

using namespace std;

class DLL{
    private:
        class Node {
            public:
                Node() {
                    this->data = -1;
                    this->next = nullptr;
                    this->prev = nullptr;
                };

                Node(int data) {
                    this->data = data;
                    this->next = nullptr;
                    this->prev = nullptr;
                };

                int data;
                Node* next;
                Node* prev;
        };

        Node* head;
        Node* tail;
        Node* currentNode;

    public:
        DLL();
        bool prepend(int val);
        bool append(int val);
        bool merge(DLL &other);
        DLL& operator+=(const DLL &other);
        DLL& operator-=(const DLL &other);
        void deleteNode(Node *nodeToDelete);
        int getMax();
        int extractMax();
        DLL extractOdds();
        DLL extractEvens();
        bool reset();
        int getNext();

};

#endif