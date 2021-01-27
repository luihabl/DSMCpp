#pragma once 

namespace DSMCpp {

    template <typename T> 
    struct LinkedList {
        struct Node {
            T data;
            Node * next;
        };

        LinkedList() {
            head = nullptr;
            tail = nullptr;
            size = 0;
        }
        
        Node * head;
        Node * tail;
        int size; 

        void add(T v) {
            Node *tmp = new Node;
            tmp->data = v;
            tmp->next = nullptr;

            if (head==nullptr) {
                head = tmp;
                tail = tmp;
            } else {
                tail->next = tmp;
                tail = tail->next;
            }
            size += 1;
        }

        T get(int index) const {
            Node * n = head;
            for (int i=0; i<index; i++) n = n->next;
            return n->data;
        }

        ~LinkedList() {
            Node * tmp = nullptr;
            Node * first = head;
            while( first != nullptr ) {
                tmp = first->next;
                delete first;
                first = tmp;
            }
            head = nullptr;
        }
    };

    // For iterating over the LinkedList:
    // for (DoubleNode * n = ll.head; n != nullptr; n=n->next) {
    //     Log::print(n->data);
    // }
    typedef LinkedList<double>::Node DoubleNode; 
    typedef LinkedList<int>::Node IntNode;

}