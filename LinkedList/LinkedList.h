#include <vector> 
#include <algorithm>
//#include "leaker.h"

using namespace std;
template<typename T>
class LinkedList {
public:
    LinkedList();
    LinkedList(const LinkedList<T>& list);
    ~LinkedList();
    LinkedList<T> operator=(const LinkedList<T> j);

    struct Node {
        T data;
        Node* next = nullptr;
        Node* prev = nullptr;
        Node* searchNext(unsigned int index) {
            if (index == 0) {
                return this;
            }
            else {
                index--;
                return next->searchNext(index);
            }
        }
    };
    Node* deletedNode = nullptr;
    Node* n = nullptr;
    Node* t = nullptr;
    Node* head = nullptr;
    Node* tail = nullptr;
    Node* tp = nullptr;
    vector<Node*> deletedData;
    bool FirstAdd = true;
    bool operator==(const LinkedList<T> j) {
        Node* x = head;
        Node* y = j.head;
        while (x != nullptr) {
            if (x->data != y->data) {
                return false;
            }
            x = x->next;
            y = y->next;
        }return true;
    }
    unsigned int _Nodecount = 0;
    void InsertBefore(Node* node, const T& data) {
        if (node == head) { AddHead(data); }
        else {
            n = new Node;
            n->data = data;
            n->next = node;
            n->prev = node->prev;
            n->prev->next = n;
            node->prev = n;
            _Nodecount++;
        }
    }
    void InsertAfter(Node* node, const T& data) {
        if (node == tail) { AddTail(data); }
        else {
            n = new Node;
            n->data = data;
            n->next = node->next;
            n->prev = node;
            n->next->prev = n;
            node->next = n;
            _Nodecount++;
        }
    }
    void InsertAt(const T& data, unsigned int index) {
        if (index == 0) { AddHead(data); }
        else if (index == (_Nodecount)) {
            AddTail(data);
        }
        else {
            InsertAfter(GetNode(index - 1), data);
        }
    }

    void Clear() {
        Node* temp = nullptr;
        for (unsigned int i = 0; i < _Nodecount; i++) {
            // cout << "deleting" << endl;
            temp = head;
            if (head != nullptr) {
                if (head->next != nullptr) {
                    // cout << "not null" << endl;
                    head = head->next;
                    delete temp;
                }
                else {
                    delete head;
                }
            }
            //cout << "delete successful" << endl;
        }
        for (Node* p : deletedData) {
            delete p;
        }
        head = nullptr;
        tail = nullptr;
        FirstAdd = true;
        _Nodecount = 0;
        //cout << "delete successful" << endl;
    }
    void AddHead(const T& data) {
        if (_Nodecount - deletedData.size() == 0) { Clear(); }
        n = new Node;
        n->data = data;
        if (FirstAdd) {
            head = n;
            t = n;
            tail = n;
            tp = tail;
            FirstAdd = false;
        }
        else {
            head = n;
            t->prev = n;
            head->next = t;
            t = n;
        }

        _Nodecount++;

    }
    bool RemoveHead() {
        if (head == nullptr) {
            return false;
        }
        if (head->next != nullptr) {
            head->next->prev = nullptr;
        }
        deletedData.push_back(head);
        head = head->next;

        return true;
    }
    bool RemoveTail() {
        if (tail == nullptr) {
            return false;
        }
        if (tail->prev != nullptr) {
            tail->prev->next = nullptr;
        }
        deletedData.push_back(tail);
        tail = tail->prev;
        return true;

    }
    bool RemoveAt(unsigned int index) {
        if (index > _Nodecount) {
            return false;
        }
        if (index == 0) { return RemoveHead(); }
        else if (index == _Nodecount) { return RemoveTail(); }
        else {
            deletedNode = GetNode(index);
            if (deletedNode != nullptr) {
                if (deletedNode->next != nullptr) {
                    deletedNode->next->prev = deletedNode->prev;
                }
                if (deletedNode->prev != nullptr) {
                    deletedNode->prev->next = deletedNode->next;
                }
                deletedData.push_back(deletedNode);
                return true;
            }
        }
        return false;
    }

    unsigned int Remove(const T& data) {
        unsigned int index = 0;
        unsigned int timesremoved = 0;
        Node* x = head;
        while (x != nullptr) {
            if ((x->data) == data) {
                RemoveAt(index);
                timesremoved++;
                index--;
            }
            x = x->next;
            index++;
        }
        return timesremoved;
    }

    void AddTail(const T& data) {
        if (_Nodecount - deletedData.size() == 0) { Clear(); }

        n = new Node;
        n->data = data;
        if (FirstAdd) {
            tail = n;
            head = n;
            tp = n;
            t = head;
            FirstAdd = false;
        }
        else {
            tail = n;
            tp->next = n;
            tail->prev = tp;
            tp = n;
        }

        _Nodecount++;

    }
    void AddNodesHead(const T* data, unsigned int count) {
        for (unsigned int i = 0; i < count; i++) {
            //  cout << "in loop" << i;;
            AddHead(data[count - i - 1]);
        }
        // cout << "done loop";
    }
    void AddNodesTail(const T* data, unsigned int count) {
        for (unsigned int i = 0; i < count; i++) {
            AddTail(data[i]);
        }
    }
    unsigned int NodeCount() {
        if (deletedData.size() > _Nodecount) {
            return 0;
        }
        else {
            return (_Nodecount - deletedData.size());
        };
    }
    unsigned int NodeCount() const {
        return _Nodecount;
    }
    void PrintForward() {
        Node* x = head;
        while (x != nullptr) {
            cout << x->data << endl;
            x = x->next;
        }
    }
    void PrintReverse() {
        Node* x = tail;
        while (x != nullptr) {
            cout << x->data << endl;
            x = x->prev;
        }
    }
    void PrintForwardRecursive(const Node* node) {
        if (node != nullptr) {
            cout << node->data << endl;
            PrintForwardRecursive(node->next);
        }

    }
    void PrintReverseRecursive(const Node* node) {
        if (node != nullptr) {
            cout << node->data << endl;
            PrintReverseRecursive(node->prev);
        }
    }


    void FindAll(vector<Node*>& outData, const T& value) const {
        Node* x = head;
        while (x != nullptr) {
            if ((x->data) == value) {
                outData.push_back(x);
            }
            x = x->next;
        }
    }
    Node* Head() {
        return head;
    }
    const Node* Head() const {
        return head;
    }

    Node* Tail() {
        return tail;
    }
    const  Node* Tail() const {
        return tail;
    }
    const Node* GetNode(unsigned int index) const {
        if (index >= NodeCount()) {
            throw std::out_of_range("ArrayList<X>::at() : index is out of range");
        }
        else {
            if (index == 0) {
                return head;
            }
            if (index == ((NodeCount() - 1))) {
                return tail;
            }
            return head->searchNext(index);

        }
    }
    Node* GetNode(unsigned int index) {
        if (index >= NodeCount()) {
            throw std::out_of_range("ArrayList<X>::at() : index is out of range");
        }
        else {
            if (index == 0) {
                return head;
            }
            if (index == ((NodeCount() - 1))) {
                return tail;
            }
            return head->searchNext(index);

        }
    }
    Node* Find(const T& data) {
        Node* x = head;
        while (x != nullptr) {
            //?
            if (x->data == data) {
                return x;
            }
            x = x->next;
        }return head;
    };
    const Node* Find(const T& data) const {
        Node* x = head;
        while (x != nullptr) {
            //?
            if (x->data == data) {
                return x;
            }
            x = x->next;
        }return head;
    };
    const T& operator[](unsigned int index) const {
        if (index >= NodeCount()) {
            throw std::out_of_range("ArrayList<X>::at() : index is out of range");
        }
        return GetNode(index)->data;
    }
    T& operator[](unsigned int index) {
        if (index >= NodeCount()) {
            throw std::out_of_range("ArrayList<X>::at() : index is out of range");
        }
        return GetNode(index)->data;
    }
};
template <typename T>LinkedList<T>::LinkedList() {}
template <typename T>LinkedList<T>::LinkedList(const LinkedList<T>& list) {
    this->_Nodecount = list._Nodecount;
    // cout << this->_Nodecount << endl;
    for (unsigned int i = 0; i < this->_Nodecount; i++) {
        // cout << "nodecount= "<< this->_Nodecount << " " << endl;
         //cout << "looped " << i << list.GetNode(i)->data;
        AddTail(list.GetNode(i)->data);
        this->_Nodecount--;
    }
}
template <typename T>LinkedList<T>::~LinkedList() {
    Node* temp = nullptr;
    for (unsigned int i = 0; i < NodeCount(); i++) {
        // cout << "deleting" << endl;
        temp = head;
        if (head != nullptr) {
            if (head->next != nullptr) {
                // cout << "not null" << endl;
                head = head->next;
                delete temp;
            }
            else {
                delete head;
            }
        }
        //cout << "delete successful" << endl;
    }
    for (Node* p : deletedData) {
        delete p;
    }
}
template <typename T>
LinkedList<T> LinkedList<T>::operator= (const LinkedList<T> j)
{
    Clear();
    this->_Nodecount = j._Nodecount;
    for (unsigned int i = 0; i < this->_Nodecount; i++) {
        // cout << "nodecount= "<< this->_Nodecount << " " << endl;
         //cout << "looped " << i << list.GetNode(i)->data;
        AddTail(j.GetNode(i)->data);
        this->_Nodecount--;
    }
    return *this;
}