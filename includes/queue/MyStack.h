#include "../../includes/queue/linkedlistfunctionsTemplated.h"

template <typename ITEM_TYPE>
class Stack
{
public:
    class Iterator
    {
    public:
        friend class Stack;                       // give access to list to access _ptr
        Iterator() { _ptr = NULL; }               // default ctor
        Iterator(node<ITEM_TYPE> *p) : _ptr(p) {} // Point Iterator to where p is pointing to
        ITEM_TYPE operator*()                     // dereference operator
        {
            assert(_ptr != NULL);
            return _ptr->_item;
        }
        bool is_null() { return (_ptr == NULL); }                           // true if _ptr is NULL
        friend bool operator!=(const Iterator &left, const Iterator &right) // true if left != right
        {
            return left._ptr != right._ptr;
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

        friend Iterator operator++(Iterator &it, int unused)
        { // friend operator: it++
            Iterator temp(it);
            assert(it._ptr != NULL);
            it._ptr = it._ptr->_next;
            return temp;
        }

    private:
        node<ITEM_TYPE> *_ptr; // pointer being encapsulated
    };
    // End of Iterator calss

    Stack();
    Stack(const Stack<ITEM_TYPE> &copyMe);
    ~Stack();
    Stack<ITEM_TYPE> &operator=(const Stack<ITEM_TYPE> &RHS);
    ITEM_TYPE top();
    bool empty();
    void push(ITEM_TYPE item);
    ITEM_TYPE pop();
    template <typename T>
    friend ostream &operator<<(ostream &outs, const Stack<T> &printMe);
    Iterator begin() const; // Iterator to the head node
    Iterator end() const;   // Iterator to NULL
    int size() const { return _size; }

private:
    node<ITEM_TYPE> *_top;
    int _size;
};

template <typename ITEM_TYPE>
Stack<ITEM_TYPE>::Stack()
{
    _top = NULL;
    _size = 0;
}
template <typename ITEM_TYPE>
Stack<ITEM_TYPE>::Stack(const Stack<ITEM_TYPE> &copyMe)
{
    this->_top = NULL;
    this->_size = 0;
    node<ITEM_TYPE> *traverser_copyMe = copyMe._top;
    node<ITEM_TYPE> *traverser_current = _top;
    if (copyMe._top == NULL)
    {
        return;
    }
    while (traverser_copyMe != NULL)
    {

        if (_top == NULL)
        {
            _top = new node<ITEM_TYPE>(traverser_copyMe->_item, NULL, NULL);
            traverser_current = _top;
        }
        else
        {
            node<ITEM_TYPE> *temp = new node<ITEM_TYPE>(traverser_copyMe->_item, NULL, traverser_current);
            traverser_current->_next = temp;
            // temp->_prev = traverser_current; *****Try using this line if the constrcutor does not link prev*****
            traverser_current = temp;
        }
        traverser_copyMe = traverser_copyMe->_next;
        _size++;
    }
}

template <typename ITEM_TYPE>
Stack<ITEM_TYPE>::~Stack()
{
    while (_top != NULL)
    {
        node<ITEM_TYPE> *temp = _top;
        _top = _top->_next;
        delete temp;
        _size--;
    }
}

template <typename ITEM_TYPE>
Stack<ITEM_TYPE> &Stack<ITEM_TYPE>::operator=(const Stack<ITEM_TYPE> &RHS)
{
    while (_top != NULL)
    {
        node<ITEM_TYPE> *temp = _top;
        _top = _top->_next;
        delete temp;
    }
    if (RHS._top == NULL)
    {
        return *this;
    }
    _top = NULL;
    _size = 0;

    node<ITEM_TYPE> *traverser_current = NULL;
    for (node<ITEM_TYPE> *traverser_RHS = RHS._top; traverser_RHS != NULL; traverser_RHS = traverser_RHS->_next)
    {
        if (traverser_current == NULL) // head
        {
            traverser_current = new node<ITEM_TYPE>(traverser_RHS->_item, NULL, NULL);
            _top = traverser_current;
        }
        else // non-head links
        {
            node<ITEM_TYPE> *newNode = new node<ITEM_TYPE>(traverser_RHS->_item, NULL, traverser_current);
            traverser_current->_next = newNode;
            traverser_current = newNode;
        }
        _size++;
    }
    return *this;
}

template <typename ITEM_TYPE>
ITEM_TYPE Stack<ITEM_TYPE>::top()
{
    assert(_top != NULL);
    return (_top->_item);
}

template <typename ITEM_TYPE>
bool Stack<ITEM_TYPE>::empty()
{
    return (_top == NULL);
}
template <typename ITEM_TYPE>
void Stack<ITEM_TYPE>::push(ITEM_TYPE item)
{
    if (_top == NULL)
    {
        _top = new node<ITEM_TYPE>(item, NULL, NULL);
    }
    else //_top!=NULL
    {
        node<ITEM_TYPE> *temp = new node<ITEM_TYPE>(item, _top, NULL);
        _top->_prev = temp;
        _top = temp;
    }
    _size++;
}
template <typename ITEM_TYPE>
ITEM_TYPE Stack<ITEM_TYPE>::pop()
{
    assert(_top != NULL);
    ITEM_TYPE temp = _top->_item;
    _size--;
    if (_top->_next != NULL)
    {
        node<ITEM_TYPE> *current = _top->_next;
        delete _top;
        current->_prev = NULL;
        _top = current;
    }
    else //_top->_next == NULL
    {
        delete _top;
        _top = NULL;
    }
    return temp;
}
template <typename ITEM_TYPE>
ostream &operator<<(ostream &outs, const Stack<ITEM_TYPE> &printMe)
{
    node<ITEM_TYPE> *current = printMe._top;
    cout << " Head ->";
    for (; current != NULL; current = current->_next)
    {
        outs << "[" << current->_item << "]"
             << "-><-";
    }
    cout << "|||";
    return outs;
}

template <typename ITEM_TYPE>
typename Stack<ITEM_TYPE>::Iterator Stack<ITEM_TYPE>::begin() const
{
    typename Stack<ITEM_TYPE>::Iterator it(_top);
    return it;
}
// Iterator to the head node
template <typename ITEM_TYPE>
typename Stack<ITEM_TYPE>::Iterator Stack<ITEM_TYPE>::end() const // Iterator to NULL
{
    typename Stack<ITEM_TYPE>::Iterator it(NULL);
    return it;
}

// typename Queue<T>::Iterator Queue<T>::begin() const // Iterator to the head node