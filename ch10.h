#ifndef CH10
#define CH10

#include <iostream>

using namespace std;

template <class T>
class FixedStack // O(1)
{
    T *A;
    int top, max_size;
public:
    FixedStack(int n) {
        this->max_size = n;
        this->A = new T[n];
        this->top = -1;
    }
    void push(T x) {
        if (this->full())
            return;
        this->A[++top] = x;
    }
    T pop() {
        if (this->empty())
            return (T) 0;
        return this->A[top--];
    }
    bool empty(){
        return top < 0;
    }
    bool full(){
        return top >= max_size;
    }
    ~FixedStack() {
        delete [] this->A;
    }
};


template <class T>
class FixedDoubleStack // O(1)
{
    int topA, topB, max_size;
    T *A;
public:
    FixedDoubleStack(int n) {
        this->max_size = n;
        this->A = new T[n];
        this->topA = -1;
        this->topB = n;
    }

    bool full() {
        return topB = topA + 1;
    }

    void pushA(T x) {
        A[++topA] = x;
    }
    void pushB(T x) {
        A[--topB] = x;
    }
    T popA() {
        return A[topA--];
    }
    T popB() {
        return A[topB++];
    }

    ~FixedDoubleStack() {
        delete [] this->A;
    }
};


template <class T>
class FixedQueue // O(1)
{
    int head, tail;
    int max_size;
    T *A;
    bool h_cycled, t_cycled;
public:
    FixedQueue(int n) {
        A = new T[n];
        max_size = n;
        head = tail = 0;
        h_cycled = t_cycled = false;
    }
    void enqueue(T x) {
        if (full()) {
            cout << "Queue if full" << endl;
            return;
        }
        A[tail++] = x;
        if (tail == max_size) {
            tail = 0;
            if (h_cycled)
                t_cycled = h_cycled = false;
            else
                t_cycled = true;
            
        }
    }
    T dequeue() {
        if (empty()) {
            cout << "Queue is empty" << endl;
            return (T) -1;
        }
        T x = A[head++];
        if (head == max_size) {
            head = 0;
            if (t_cycled)
                t_cycled = h_cycled = false;
            else
                h_cycled = true;
        }
        return x;
    }
    bool full() {
        return head == tail && t_cycled && !h_cycled;
    }
    bool empty() {
        return head == tail && !t_cycled && !h_cycled;
    }
    ~FixedQueue() {
        delete [] A;
    }
};


template <class T>
class FixedDeque // O(1)
{
    int head, tail;
    int max_size;
    T *A;
public:
    FixedDeque(int n) {
        A = new T[n];
        max_size = n;
        head = tail = 0;
    }

    void push_back(T x) {
        A[tail++] = x;
        if (tail == max_size) {
            tail = 0;
        }
    }
    void push_forward (T x) {
        head = (head == 0) ? max_size : head;
        A[--head] = x;
    }
    T pop_back() {
        tail = (tail == 0) ? max_size : tail;
        T x = A[--tail];
        if (tail < 0) {
            tail = max_size - 1;
        }
        return x;
    }
    T pop_forward() {
        T x = A[head++];
        if (head == max_size) {
            head = 0;
        }
        return x;
    }
    ~FixedDeque() {
        delete [] A;
    }
};


template<class T>
class DobuleLinkedList
{
    class DoubleNode {
    public:
        T _item;
        DoubleNode *_next, *_prev;

        DoubleNode(DoubleNode *next, DoubleNode *prev, int item) {
            _item = item;
            _next = next;
            _prev = prev;
        }
    };

    DoubleNode *head;

    // можно добавить ограничитель
public:
    DobuleLinkedList() {
        head = new DoubleNode(NULL, NULL, -1);
    }
    void insert(T x) {
        DoubleNode *tmp = new DoubleNode(head->_next, head, x);
        head->_next = tmp;
    }
    DoubleNode* find(T x) {
        DoubleNode *result = head;
        while (result && result->_item != x)
            result = result->_next;
        return result;
    }
    void del(T x) {
        DoubleNode *result = head;
        while (result && result->_item != x)
            result = result->_next;

        result->_prev->_next = result->_next;
        if (result->_next)
            result->_next->_prev = result->_prev;

        delete result;
    }
    ~DobuleLinkedList() {
        DoubleNode *current = head;
        while (head->_next)
            this->del(head->_next->_item);
        delete head;
    }

};


template<class T>
class LinkedList
{
    class Node {
    public:
        T _item;
        Node *_next;

        Node(Node<T> *next, int item) {
            _item = item;
            _next = next;
        }
    };
    Node<T> *head;
public:
    LinkedList() {
        head = new Node(NULL, -1);
    }
    void insert(int x) {
        head->_next = new Node(head->_next, x);
    }
    Node* del(int key) {
        if (empty())
            return NULL;

        Node *result = head;
        while (result->_next && result->_next->_item != key)
            result = result->_next;

        if (!result->_next)
            return NULL;
        else {
            Node *tmp = result->_next;

            result->_next = tmp->_next;

            delete tmp;
            return result;
        }
    }
    bool empty() {
        return !head->_next;
    }
    ~LinkedList() {
        while (!empty())
            del(head->_next->_item);
        delete head;
    }
    void print() {
        Node *z = head->_next;
        while(z) {
            cout << z->_item << endl;
            z = z->_next;
        }
    }
    void transponce() { // O(n)
        Node *head2 = new Node(NULL, -1), *z = head->_next;
        while (z) {
            Node *z2 = z->_next;
            z->_next = head2->_next;
            head2->_next = z;
            z = z2;
        }
        delete head;
        head = head2;
    }
};


template<class T>
class StackOnLinkedList
{
    LinkedList<T> A;
    T last_key;

public:
    void push(int x) {
        A.insert(x);
        last_key = x;
    }

    int pop() {
        int tmp = last_key;
        Node<T>* t = A.del(tmp);
        if (t && t->_next)
            last_key = t->_next->_item;
        else
            last_key = -100;
        return tmp;
    }
};


#endif