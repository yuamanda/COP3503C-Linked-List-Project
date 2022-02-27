#pragma once
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class LinkedList
{
public:
    struct Node
    {
        // the data you are storing
        T data;
        // a pointer to the next node
        Node* next;
        // a pointer to the previous node (if doubly-linked)
        Node* prev;
    };

public:
    // a node pointer to the head
    Node* head;
    // a node pointer to the tail
    Node* tail;
    // how many nodes are there?
    unsigned int count;

    void AddHead(const T& _data);
    void AddTail(const T& _data);
    void AddNodesHead(const T* _data, unsigned int _count);
    void AddNodesTail(const T* _data, unsigned int _count);
    unsigned int NodeCount() const;
    void PrintForward() const;
    void PrintReverse() const;
    LinkedList();
    ~LinkedList();
    Node* Head();
    const Node* Head() const;
    Node* Tail();
    const Node* Tail() const;
    const Node* GetNode(unsigned int index) const;
    Node* GetNode(unsigned int index);
    const T& operator[](unsigned int index) const;
    T& operator[](unsigned int index);
    const Node* Find(const T& _data) const;
    Node* Find(const T& _data);
    void FindAll(vector<Node*>& outData, const T& value) const;
    LinkedList(const LinkedList<T>& list);
    LinkedList<T>& operator=(const LinkedList<T>& rhs);
    void InsertBefore(Node* node, const T& _data);
    void InsertAfter(Node* node, const T& _data);
    void InsertAt(const T& _data, unsigned int index);
    bool operator==(const LinkedList<T>& rhs);
    bool RemoveHead();
    bool RemoveTail();
    bool RemoveAt(unsigned int index);
    unsigned int Remove(const T& _data);
    void Clear();
    void PrintForwardRecursive(const Node* node) const;
    void PrintReverseRecursive(const Node* node) const;

};

// create a new node at the front of the list to store the passed in parameter
template <typename T>
void LinkedList<T>::AddHead(const T& _data)
{
    struct Node* newHead = new Node();
    newHead -> data = _data;
    newHead -> next = head;
    head = newHead;
    newHead -> prev = nullptr;

    if(count == 0)
    {
        tail = newHead;
    }
    else
    {
        newHead -> next -> prev = head;
    }

    count++;
}

// create a new node at the end of the list to store the passed in parameter
template <typename T>
void LinkedList<T>::AddTail(const T& _data)
{
    struct Node* newTail = new Node();
    newTail -> data = _data;
    newTail -> prev = tail;
    tail = newTail;
    newTail -> next = nullptr;

    if(count == 0)
    {
        head = newTail;
    }
    else
    {
        newTail -> prev -> next = tail;
    }

    count++;
}

// given an array of values
// insert a node for each of those at the beginning of the list
// maintaining the orginal order
template <typename T>
void LinkedList<T>::AddNodesHead(const T* _data, unsigned int _count)
{
    _data += _count - 1;

    for(unsigned int i = _count; i > 0; i--)
    {
        AddHead(*_data);
        _data--;
    }
}

// same as AddNodesHead(), except adding to the end of the list
template <typename T>
void LinkedList<T>::AddNodesTail(const T* _data, unsigned int _count)
{
    for(unsigned int i = 0; i < _count; i++)
    {
        AddTail(*_data);
        _data++;
    }
}

// how many things are stored in this list?
template <typename T>
unsigned int LinkedList<T>::NodeCount() const
{
    int count = 0;
    Node* temp = head;

    while(temp != nullptr)
    {
        count++;
        temp = temp -> next;
    }

    return count;
}

// iterator through all the nodes and print out their values, one at a time
template <typename T>
void LinkedList<T>::PrintForward() const
{
    Node* temp = head;

    while(temp != nullptr)
    {
        cout << temp -> data << endl;
        temp = temp -> next;
    }
}

// exactly the same as PrintForward(), except completely the opposite
template <typename T>
void LinkedList<T>::PrintReverse() const
{
    Node* temp = tail;

    while(temp != nullptr)
    {
        cout << temp -> data << endl;
        temp = temp -> prev;
    }
}

// default constructor
// how many nodes in an empty list? (answer = 0)
// what is the head pointing to?
// what is the tail pointing to? (answer = nullptr)
// initialize your variables
template <typename T>
LinkedList<T>::LinkedList()
{
    count = 0;
    head = nullptr;
    tail = nullptr;
}

// clean up mess, delete all the nodes created by the list
template <typename T>
LinkedList<T>::~LinkedList()
{
    Node* currentHead = head;
    Node* temp = head;

    while(temp != nullptr)
    {
        currentHead = temp -> next;
        delete temp;
        temp = currentHead;
    }
}

// returns the head pointer
// const and non-const versions
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head()
{
    return head;
}

// returns the head pointer
// const and non-const versions
template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const
{
    return head;
}

// returns the tail pointer
// const and non-const versions
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail()
{
    return tail;
}

// returns the tail pointer
// const and non-const versions
template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const
{
    return tail;
}

// given an index, return a pointer to the node at that index
// throws an exception of type out_of_range if the index is out of range
// const and non-const versions
template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const
{
    Node* temp = head;

    if(count <= index)
    {
        throw out_of_range("out of range");
    }

    else
    {
        for(unsigned int i = 0; i < index; i++)
        {
            temp = temp -> next;
        }

        return temp;
    }
}

// given an index, return a pointer to the node at that index
// throws an exception of type out_of_range if the index is out of range
// const and non-const versions
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index)
{
    Node* temp = head;

    if(count <= index)
    {
        throw out_of_range("out of range");
    }

    else
    {
        for(unsigned int i = 0; i < index; i++)
        {
            temp = temp -> next;
        }

        return temp;
    }
}

// overloaded subscript operator
// takes an index, and returns data from the index-th node
// throws an out_of_range exception for an invalid index
// const and non-const versions
template <typename T>
const T& LinkedList<T>::operator[](unsigned int index) const
{
    Node* temp = head;

    if(count <= index)
    {
        throw out_of_range("out of range");
    }

    else
    {
        for(unsigned int i = 0; i < index; i++)
        {
            temp = temp -> next;
        }

        return temp -> data;
    }
}

// overloaded subscript operator
// takes an index, and returns data from the index-th node
// throws an out_of_range exception for an invalid index
// const and non-const versions
template <typename T>
T& LinkedList<T>::operator[](unsigned int index)
{
    Node* temp = head;

    if(count <= index)
    {
        throw out_of_range("out of range");
    }

    else
    {
        for(unsigned int i = 0; i < index; i++)
        {
            temp = temp -> next;
        }

        return temp -> data;
    }
}

// find the first node with the data value matching the passed in parameter
// returning a pointer to that node
// returns nullptr if no matching code is found
template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& _data) const
{
    Node* temp = head;

    for(unsigned int i = 0; i < count; i++)
    {
        if(temp -> data == _data)
        {
            return temp;
        }

        temp = temp -> next;
    }

    return nullptr;
}

// find the first node with the data value matching the passed in parameter
// returning a pointer to that node
// returns nullptr if no matching code is found
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& _data)
{
    Node* temp = head;

    for(unsigned int i = 0; i < count; i++)
    {
        if(temp -> data == _data)
        {
            return temp;
        }

        temp = temp -> next;
    }

    return nullptr;
}

// finds all the nodes which match the passed in parameter value and store a pointer to that node in the passed in vector
// use of parameter like this (passing a something in by reference, and storing data for later use) is called an output parameter
template <typename T>
void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const
{
    Node* temp = head;

    for(unsigned int i = 0; i < count; i++)
    {
        if(temp -> data == value)
        {
            outData.push_back(temp);
        }
        temp = temp -> next;
    }
}

// set "this" to a copy of the passed in linkedlist
// for example, if the other list has 10 nodes, with values 1-10, "this" should have a copy of that same data
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list)
{
    count = 0;
    head = nullptr;
    tail = nullptr;

    Node* listHead = list.head;

    while(listHead != nullptr)
    {
        AddTail(listHead -> data);
        listHead = listHead -> next;
    }
}

// assignment operator
// after listA = listB, listA == listB is true
// can you utilize any of your existing functions to make write this one? (hint: yes you can)
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs)
{

    Node* currentHead = head;
    Node* temp = head;

    while(temp != nullptr)
    {
        currentHead = temp -> next;
        delete temp;
        temp = currentHead;
    }

    count = 0;
    head = nullptr;
    tail = nullptr;

    Node* rhsHead = rhs.head;

    while(rhsHead != nullptr)
    {
        AddTail(rhsHead -> data);
        rhsHead = rhsHead -> next;
    }

    return *this;
}

// insert the new node before the indicated node
template <typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& _data)
{
    Node* add = new Node();
    add -> data = _data;

    node -> prev -> next = add;
    node -> prev = add;
    add -> prev = node -> prev;
    add -> next = node;

    count++;
}

// given a pointer to a node, create a new node to store the passed in value, after the indicated node
template <typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& _data)
{
    Node* add = new Node();
    add -> data = _data;

    add -> prev = node;
    add -> next = node -> next;
    node -> next -> prev = add;
    node -> next = add;

    count++;
}

// insert a new node to store the first parameter, at the index-th location
// so if you specified 3 as the index, the new node should have 3 nodes before it
// throws an out_of_range exception if given an invalid index
template <typename T>
void LinkedList<T>::InsertAt(const T& _data, unsigned int index)
{
    if(index > count)
    {
        throw out_of_range("out of range");
    }

    else if(index == 0)
    {
        AddHead(_data);
    }

    else if(index == count)
    {
        AddTail(_data);
    }

    else
    {
        Node* temp;
        Node* add = new Node();
        add -> data = _data;

        temp = GetNode(index - 1);

        add -> prev = temp;
        add -> next = temp -> next;
        temp -> next = add;
        add -> next -> prev = add;

        count++;
    }
}

// overloaded equality operator
// given listA and listB, is listA equal to listB?
// what would amke one linked list equal to another?
// if each of its node were equal to the corresponding node of the other
// similar to comparing two arrays, just with non-contigous data
template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs)
{
    Node* rhsHead = rhs.head;

    for(unsigned int i = 0; i < count; i++)
    {
        if(rhsHead -> data != head -> data)
        {
            return 0;
        }

        rhsHead = rhsHead -> next;
        head = head -> next;
    }

    return 1;
}

// deletes the first node in the list
// returns whether or not the node was removed
template <typename T>
bool LinkedList<T>::RemoveHead()
{
    if(count == 0)
    {
        return 0;
    }

    else if(count == 1)
    {
        Node* temp = head;

        delete temp;

        head = nullptr;
        tail = nullptr;

        count--;
        return 1;
    }

    else
    {
        Node* temp = head -> next;
        delete head;
        head = temp;
        head -> prev = nullptr;
        count--;
        return 1;
    }
}

// deletes the last node, returning whether or not the operation was successful
template <typename T>
bool LinkedList<T>::RemoveTail()
{
    if(count == 0)
    {
        return 0;
    }

    else if(count == 1)
    {
        delete tail;

        head = nullptr;
        tail = nullptr;

        count--;
        return 1;
    }

    else
    {
        Node* temp = tail -> prev;
        delete tail;
        tail = temp;
        tail -> next = nullptr;
        count--;
        return 1;
    }
}

// deletes the index-th node from the list, returning whether or not the operation was successful
template <typename T>
bool LinkedList<T>::RemoveAt(unsigned int index)
{
    if(index > count)
    {
        return 0;
    }

    else
    {
        Node* temp = GetNode(index);

        temp -> prev -> next = temp -> next;
        temp -> next -> prev = temp -> prev;
        delete temp;
        count--;
        return 1;
    }
}

// deletes all nodes containing values matching that of the passed-in parameter
// returns how many instances were removed
template <typename T>
unsigned int LinkedList<T>::Remove(const T& _data)
{
    Node* temp = head;
    Node* currentNode = head;
    int instances = 0;

    for(unsigned int i = 0; i < count; i++)
    {
        if(temp -> data == _data)
        {
            temp -> prev -> next = temp -> next;
            temp -> next -> prev = temp -> prev;
            temp = temp -> next;
            delete currentNode;
            currentNode = temp;
            instances++;
        }

        else
        {
            temp = temp -> next;
            currentNode = currentNode -> next;
        }
    }

    count -= instances;
    return instances;
}

// deletes all nodes
// don't forget the node count, how many nodes do you have after you delete all fo them?
template <typename T>
void LinkedList<T>::Clear()
{
    Node* currentHead = head;
    Node* temp = head;

    while(temp != nullptr)
    {
        currentHead = temp -> next;
        delete temp;
        temp = currentHead;
    }

    count = 0;
    head = nullptr;
    tail = nullptr;
}

// the function takes in a pointer to a node, a starting node
// from that node, recursively visit each node that follows, in forward order, and print their values
// this function must be implemented using recursion, or tests using it will be worth no points
// check your textbook for a reference on recursion
template <typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const
{
    if(node == nullptr)
    {
        return;
    }

    else
    {
        cout << node -> data << endl;
        PrintForwardRecursive(node -> next);
    }
}

// same deal as printforwardrecursive, but in reverse
template <typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const
{
    if(node == nullptr)
    {
        return;
    }

    else
    {
        cout << node -> data << endl;
        PrintReverseRecursive(node -> prev);
    }
}