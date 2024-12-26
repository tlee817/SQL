#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "../../includes/queue/node.h"
// Doubly linked list
//  Linked List General Functions:
template <typename T>
void _print_list(node<T> *head)
{
    cout << "Head-><-";
    for (node<T> *n = head; n != NULL; n = n->_next)
    {
        cout << "[" << n->_item << "]-> <-";
    }
    cout << "|||" << endl;
}

// recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head)
{
    if (head == NULL)
    {
        cout << "Empty list" << endl;
        return;
    }
    _print_list_backwards(head->_next);
    std::cout << head->_item << " ";
}

// return ptr to key or NULL
template <typename T>
node<T> *_search_list(node<T> *head, T key)
{
    node<T> *result = NULL;

    for (node<T> *n = head; n != NULL; n = n->_next)
    {
        if (n->_item == key)
        {
            result = n;
            return result;
        }
    }
    return result;
}

template <typename T>
node<T> *_insert_head(node<T> *&head, T insert_this)
{
    node<T> *temp = new node<T>(insert_this, head, NULL);
    if (head != NULL)
    {
        head->_prev = temp;
    }
    head = temp;
    return head;
}

// insert after ptr: insert head if marker null
//???? If marker nulll && head!=NULL, insert before or after head?
template <typename T>
node<T> *_insert_after(node<T> *&head, node<T> *after_this, T insert_this)
{
    if (after_this == NULL)
    {
        if (head == NULL)
        {
            head = new node<T>(insert_this, NULL, NULL);
            return head;
        }
        else
        {
            node<T> *temp = new node<T>(insert_this, NULL, head);
            head = temp;
            return head;
        }
    }
    else
    {
        //  node<T> *temp = after_this->_next;
        //  temp->_item = insert_this;
        if (after_this->_next == NULL)
        {
            node<T> *temp = new node<T>(insert_this, NULL, after_this);
            after_this->_next = temp;
            return temp;
        }
        else // after_this->_next!=NULL
        {
            node<T> *temp = new node<T>(insert_this, after_this->_next, after_this);
            after_this->_next->_prev = temp;
            after_this->_next = temp;
            return temp;
        }
    }
    return head;
}

// insert before ptr: insert head if marker null
//???? If marker nulll && head!=NULL, insert before or after head?
template <typename T>
node<T> *_insert_before(node<T> *&head, node<T> *before_this, T insert_this)
{
    if (before_this == NULL)
    {
        if (head == NULL)
        {
            head = new node<T>(insert_this, NULL, NULL);
            return head;
        }
        else // head!=NULL
        {
            node<T> *temp = new node<T>(insert_this, head, NULL);
            head->_prev = temp;
            head = temp;
            return head;
        }
    }
    else // before_this!=NULL
    {
        if (before_this->_prev == NULL && before_this == head)
        {
            node<T> *temp = new node<T>(insert_this, head, NULL);
            head = temp;
            return temp;
        }
        else // before_this->prev!=NULL
        {
            node<T> *temp = new node<T>(insert_this, before_this, before_this->_prev);
            before_this->_prev->_next = temp;
            before_this->_prev = temp;
            return temp;
        }
    }
    return head;
}

// ptr to previous node
template <typename T>
node<T> *_previous_node(node<T> *prev_to_this)
{
    if (prev_to_this->_prev == NULL)
    {
        return NULL;
    }
    else // if (prev_to_this->_prev != NULL)
    {
        return prev_to_this->_prev;
    }
}

// delete, return item
template <typename T>
T _delete_node(node<T> *&head, node<T> *delete_this)
{
    T item = delete_this->_item;
    if (delete_this == head && head->_next == NULL) // only one node
    {
        delete delete_this;
        head = NULL;
        return item;
    }
    else if (delete_this->_prev == NULL) // head
    {
        node<T> *temp = delete_this->_next;
        temp->_prev = NULL;
        delete delete_this;
        head = temp;
        return item;
    }
    else if (delete_this->_next == NULL) // tail
    {
        delete_this->_prev->_next = NULL;
        delete delete_this;
        return item;
    }
    else // anywhere in the middle
    {
        delete_this->_prev->_next = delete_this->_next;
        delete_this->_next->_prev = delete_this->_prev;
        delete delete_this;
        return item;
    }
    return item;
}

// duplicate the list...
template <typename T>
node<T> *_copy_list(node<T> *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    // head of new list
    node<T> *copyOfList_head = new node<T>(head->_item, NULL, NULL);
    // Traveerser
    node<T> *copyOfList_prev = copyOfList_head;

    for (node<T> *n = head->_next; n != NULL; n = n->_next)
    {
        node<T> *copyOfList_current = new node<T>(n->_item, NULL, copyOfList_prev);
        copyOfList_prev->_next = copyOfList_current;
        copyOfList_prev = copyOfList_current;
    }
    return copyOfList_head;
}

// duplicate the list, return pointer to last node in dest...
//      use this function in your queue big three
template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src)
{
    if (src == NULL)
    {
        return NULL;
    }
    // head of new list
    dest = new node<T>(src->_item, NULL, NULL);
    // Traveerser
    node<T> *dest_prev = dest;

    for (node<T> *n = src->_next; n != NULL; n = n->_next)
    {
        node<T> *dest_current = new node<T>(n->_item, NULL, dest_prev);
        dest_prev->_next = dest_current;
        dest_prev = dest_current;
    }
    node<T> *lastNode = NULL;
    for (node<T> *n = dest; n != NULL; n = n->_next)
    {
        lastNode = n;
    }
    return lastNode;
}

// delete all the nodes
template <typename T>
void _clear_list(node<T> *&head)
{
    while (head != NULL)
    {
        node<T> *next = head->_next;
        delete head;
        head = next;
    }
}

//_item at this position
// assume pos is within the list?
template <typename T>
T &_at(node<T> *head, int pos)
{
    node<T> *n = head;
    for (int i = 0; i < pos; i++)
    {
        n = n->_next;
        if (n == NULL)
        {
            std::cout << "Pos > Linked List size. Out of range." << endl;
            return NULL;
        }
    }

    return n->_item;
}

//

#endif