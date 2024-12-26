#include "../../includes/queue/linkedlistfunctionsTemplated.h"
template <typename T>
class Queue
{
public:
    class Iterator
    {
    public:
        friend class Queue;               // give access to list to access _ptr
        Iterator() { _ptr = NULL; }       // default ctor
        Iterator(node<T> *p) : _ptr(p) {} // Point Iterator to where p is pointing to
        T operator*()
        {
            assert(_ptr != NULL);
            return _ptr->_item;
        }
        bool is_null() // true if _ptr is NULL
        {
            return (_ptr == NULL);
        }

        friend bool operator!=(const Iterator &left, const Iterator &right) // true if left != right
        {
            return (left._ptr != right._ptr);
        }

        friend bool operator==(const Iterator &left, const Iterator &right) // true if left == right
        {
            return (left._ptr == right._ptr);
        }

        Iterator &operator++() // member operator:++it or ++it = new_value
        {
            assert(_ptr != NULL);
            _ptr = _ptr->_next;
            return *this;
        }

        friend Iterator operator++(Iterator &it, int unused) // friend operator: it++
        {
            Iterator temp(it);
            assert(it._ptr != NULL);
            it._ptr = it._ptr->_next;
            return temp;
        }

    private:
        node<T> *_ptr; // pointer being encapsulated
    };

    Queue();

    Queue(const Queue<T> &copyMe);
    ~Queue();
    Queue &operator=(const Queue<T> &RHS);

    bool empty();
    T front();
    T back();

    void push(T item);
    T pop();

    Iterator begin() const; // Iterator to the head node
    Iterator end() const;   // Iterator to NULL
    void print_pointers();
    int size() const { return _size; }
    template <typename TT>
    friend ostream &operator<<(ostream &outs, const Queue<TT> &printMe);

private:
    node<T> *_front;
    node<T> *_rear;
    int _size;
};

// Definitions

template <typename T>
Queue<T>::Queue()
{
    _front = NULL;
    _rear = NULL;
    _size = 0;
}

template <typename T>
Queue<T>::Queue(const Queue<T> &copyMe) //*****
{
    _front = NULL;
    _rear = NULL;
    _size = 0;

    node<T> *traverser_copyMe = copyMe._front;
    node<T> *traverser_current = _front;
    while (traverser_copyMe != NULL)
    {
        if (_front == NULL)
        {
            _front = new node<T>(copyMe._front->_item, NULL, NULL);
            traverser_current = _front;
            _rear = _front;
        }
        else
        {
            node<T> *newNode = new node<T>(traverser_copyMe->_item, NULL, traverser_current);
            traverser_current->_next = newNode;
            traverser_current = newNode;
            _rear = newNode;
        }
        traverser_copyMe = traverser_copyMe->_next;
        _size++;    //05/26
    }
}

template <typename T>
Queue<T>::~Queue()
{
    while (_front != NULL)
    {
        node<T> *temp = _front;
        _front = _front->_next;
        delete temp;
        _size--;
    }
    _rear = NULL;
}

template <typename T>
Queue<T> &Queue<T>::operator=(const Queue<T> &RHS)
{
    _front = NULL;
    _rear = NULL;
    _size = 0;

    node<T> *traverser_RHS = RHS._front;
    node<T> *traverser_current = _front;
    while (traverser_RHS != NULL)
    {
        if (_front == NULL)
        {
            _front = new node<T>(RHS._front->_item, NULL, NULL);
            traverser_current = _front;
            _rear = _front;
        }
        else
        {
            node<T> *newNode = new node<T>(traverser_RHS->_item, NULL, traverser_current);
            traverser_current->_next = newNode;
            traverser_current = newNode;
            _rear = newNode;
        }
        traverser_RHS = traverser_RHS->_next;
        _size++;    //Double check
    }
    return *this; //05/26
}

template <typename T>
bool Queue<T>::empty()
{
    return (_front == NULL && _rear == NULL);
}

template <typename T>
T Queue<T>::front()
{
    T item = _front->_item;
    return item;
}

template <typename T>
T Queue<T>::back()
{
    T item = _rear->_item;
    return item;
}
template <typename T>
void Queue<T>::push(T item) // First in
{
    if (_rear == NULL)
    {
        node<T> *newNode = new node<T>(item, NULL, NULL);
        _front = newNode;
        _rear = newNode;
    }
    else
    {
        node<T> *newNode = new node<T>(item, NULL, _rear);
        _rear->_next = newNode;
        _rear = newNode;
    }
    _size++;
}
template <typename T>
T Queue<T>::pop() // First Out
{
    assert(_front != NULL);
    T item = _front->_item;
    if (_front->_next != NULL)
    {
        node<T> *temp = _front->_next;
        temp->_prev = NULL;
        delete _front;
        _front = temp;
    }
    else
    {
        delete _front;
        _front = NULL;
        _rear = NULL;
    }
    _size--;
    return item;
}
template <typename T>
typename Queue<T>::Iterator Queue<T>::begin() const // Iterator to the head node
{
    typename Queue<T>::Iterator it(_front);
    return it;
}
template <typename T>
typename Queue<T>::Iterator Queue<T>::end() const // Iterator to NULL
{
    typename Queue<T>::Iterator it(NULL);
    return it;
}

template <typename T>
void Queue<T>::print_pointers()
{
    if (_front == NULL)
    {
        cout << "Queue is now empty." << endl;
    }
    else
    {
        if (_front != _rear)
        {
            cout << "Front Address: " << _front << endl
                 << "Front value: " << _front->_item << endl;
            cout << "Rear Address: " << _rear << endl
                 << "Rear value: " << _rear->_item << endl;
        }
        else
        {
            cout << "There is only one element in the queue." << endl
                 << "Address: " << _front << endl
                 << "value: " << _front->_item << endl;
        }
    }
}

template <typename T>
ostream &operator<<(ostream &outs, const Queue<T> &printMe)
{
    // assert(printMe._front != NULL);
    node<T> *current = printMe._front;
    cout << " Head ->";
    for (; current != NULL; current = current->_next)
    {
        outs << "[" << current->_item << "]"
             << "-><-";
    }
    cout << "|||";
    return outs;
}

/*
 node<ITEM_TYPE> *current = printMe._top;
    for (; current != NULL; current = current->_next)
    {
        outs << current->_item << " ->";
    }
    return outs;
    */

// queue: Queue:Head-><-[0]-> <-[10]-> |||
