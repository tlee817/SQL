#ifndef B_PLUS_TREE_H
#define B_PLUS_TREE_H
#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include <cassert>
#include "../../includes/bplustree/btree_array_funcs.h"
using namespace std;

template <class T>
class BPlusTree
{
public:
    class Iterator
    {
    public:
        friend class BPlusTree;
        Iterator(BPlusTree<T> *_it = NULL, int _key_ptr = 0) : it(_it), key_ptr(_key_ptr)
        {
        }
        T operator*()
        {
            return it->data[key_ptr];
        }
        Iterator operator++(int un_used);
        Iterator operator++();
        friend bool operator==(const Iterator &lhs, const Iterator &rhs)
        {
            return ((lhs.it == rhs.it) && (lhs.key_ptr == rhs.key_ptr));
        }
        friend bool operator!=(const Iterator &lhs, const Iterator &rhs)
        {
            return ((lhs.it != rhs.it) || (lhs.key_ptr != rhs.key_ptr));
        }
        void print_Iterator()
        {
            if (it)
            {
                cout << "iterator: ";
                print_array(it->data, it->data_count, key_ptr);
            }
            else
            {
                cout << "iterator: NULL, key_ptr: " << key_ptr << endl;
            }
        }
        bool is_null() { return !it; }
        void info()
        {
            cout << endl
                 << "Iterator info:" << endl;
            cout << "key_ptr: " << key_ptr << endl;
            cout << "it: " << *it << endl;
        }
        // PRIVATE:
        BPlusTree<T> *it;
        int key_ptr;

    private:
        //     BPlusTree<T> *it;
        //     int key_ptr;
    };

    BPlusTree(bool dups = true);
    BPlusTree(T *a, int size, bool dups = false);

    // big three:
    BPlusTree(const BPlusTree<T> &other);
    ~BPlusTree();
    BPlusTree<T> &operator=(const BPlusTree<T> &RHS);

    void copy_tree(const BPlusTree<T> &other); // copy other into this object
    void copy_tree(const BPlusTree<T> &other, BPlusTree<T> *&last_node);

    void insert(const T &entry); // insert entry into the tree
    void remove(const T &entry); // remove entry from the tree
    void clear_tree();           // clear this object (delete all nodes etc.)

    bool contains(const T &entry) const; // true if entry can be found
    T &get(const T &entry);              // return a reference to entry
    const T &get(const T &entry) const;  // return a reference to entry
    T &get_existing(const T &entry);     // return a reference to entry
    Iterator find(const T &key);         // return an iterator to this key.  NULL if not there.
    Iterator lower_bound(const T &key);  // return first that goes NOT BEFORE key entry or next if does not exist: >= entry
    Iterator upper_bound(const T &key);  // return first that goes AFTER key exist or not, the next entry  >entry

    int size() const; // count the number of elements

    bool empty() const; // true if the tree is empty

    void print_tree(int level = 0, ostream &outs = cout) const;
    friend ostream &operator<<(ostream &outs, const BPlusTree<T> &print_me)
    {
        print_me.print_tree(0, outs);
        return outs;
    }

    bool is_valid();
    string pre_order();
    string in_order();
    string post_order();
    Iterator begin();
    Iterator end();
    ostream &list_keys(Iterator from = NULL, Iterator to = NULL)
    {
        if (from == NULL)
            from = begin();
        if (to == NULL)
            to = end();
        for (Iterator it = from; it != to; it++)
            cout << *it << " ";
        return cout;
    }
    // DEBUGGING FUNCTIONS:
    void makeTree();
    void printData();

    // PRIVATE:
private:
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;

    bool dups_ok;                   // true if duplicate keys are allowed
    int data_count;                 // number of data elements
    T data[MAXIMUM + 1];            // holds the keys
    int child_count;                // number of children
    BPlusTree *subset[MAXIMUM + 2]; // subtrees
    BPlusTree *next;
    bool is_leaf() const
    {
        return child_count == 0; // true if this is a leaf node
    }
    T *find_ptr(const T &entry); // return a pointer to this key. NULL if not there.

    // insert element functions
    void loose_insert(const T &entry); // allows MAXIMUM+1 data elements in the root
    void fix_excess(int i);            // fix excess in child i

    // remove element functions:
    void loose_remove(const T &entry); // allows MINIMUM-1 data elements in the root

    BPlusTree<T> *fix_shortage(int i); // fix shortage in child i
    // and return the smallest key in this subtree
    BPlusTree<T> *get_smallest_node();
    void get_smallest(T &entry);                 // entry := leftmost leaf
    void get_biggest(T &entry);                  // entry := rightmost leaf
    void remove_biggest(T &entry);               // remove the biggest child of tree->entry
    void transfer_left(int i);                   // transfer one element LEFT from child i
    void transfer_right(int i);                  // transfer one element RIGHT from child i
    BPlusTree<T> *merge_with_next_subset(int i); // merge subset i with  i+1
    // private:
    //  static const int MINIMUM = 1;
    //  static const int MAXIMUM = 2 * MINIMUM;

    // bool dups_ok;                   // true if duplicate keys are allowed
    // int data_count;                 // number of data elements
    // T data[MAXIMUM + 1];            // holds the keys
    // int child_count;                // number of children
    // BPlusTree *subset[MAXIMUM + 2]; // subtrees
    // BPlusTree *next;
    // bool is_leaf() const
    // {
    //     return child_count == 0; // true if this is a leaf node
    // }
    // T *find_ptr(const T &entry); // return a pointer to this key. NULL if not there.

    // // insert element functions
    // void loose_insert(const T &entry); // allows MAXIMUM+1 data elements in the root
    // void fix_excess(int i);            // fix excess in child i

    // // remove element functions:
    // void loose_remove(const T &entry); // allows MINIMUM-1 data elements in the root

    // BPlusTree<T> *fix_shortage(int i); // fix shortage in child i
    // // and return the smallest key in this subtree
    // BPlusTree<T> *get_smallest_node();
    // void get_smallest(T &entry);                 // entry := leftmost leaf
    // void get_biggest(T &entry);                  // entry := rightmost leaf
    // void remove_biggest(T &entry);               // remove the biggest child of tree->entry
    // void transfer_left(int i);                   // transfer one element LEFT from child i
    // void transfer_right(int i);                  // transfer one element RIGHT from child i
    // BPlusTree<T> *merge_with_next_subset(int i); // merge subset i with  i+1
};
// PUBLIC:

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::Iterator::operator++(int un_used) // it++
{
    Iterator temp = it;
    if (it != NULL)
    {
        if (it->data_count - 1 > key_ptr)
        {
            key_ptr++;
        }
        else if (it->next != NULL)
        {
            it = it->next;
            key_ptr = 0;
        }
        else
        {
            it = NULL;
            key_ptr = 0;
        }
    }
    return temp;
}
template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::Iterator::operator++() //++it
{
    if (it != NULL)
    {
        if (it->data_count - 1 > key_ptr)
        {
            key_ptr++;
        }
        else if (it->next != NULL)
        {
            it = it->next;
            key_ptr = 0;
        }
        else
        {
            it = NULL;
            key_ptr = 0;
        }
    }
    return *this;
}
template <class T>
BPlusTree<T>::BPlusTree(bool dups) : dups_ok(dups), data_count(0), child_count(0), next(NULL)
{
    for (int i = 0; i < MAXIMUM + 2; i++)
    {
        subset[i] = NULL;
    }
    // for (int i = 0; i < MAXIMUM + 1; i++)
    // {
    //     data[i] = 0;
    // }
}
template <class T>
BPlusTree<T>::BPlusTree(T *a, int size, bool dups)
{
    data_count = 0;
    child_count = 0;
    dups_ok = dups;
    next = NULL;
    for (int i = 0; i < size; i++)
    {
        insert(a[i]);
    }
}
// big three:
template <class T>
BPlusTree<T>::BPlusTree(const BPlusTree<T> &other)
{
    dups_ok = other.dups_ok;
    // clear_tree(); <--- found this bug after 4 hours of suffering. Look back at this after 5 years
    data_count = 0;
    child_count = 0;
    copy_tree(other);
}
template <class T>
BPlusTree<T>::~BPlusTree()
{
    clear_tree();
}
template <class T>
BPlusTree<T> &BPlusTree<T>::operator=(const BPlusTree<T> &RHS)
{
    if (this != &RHS)
    {
        clear_tree();
        copy_tree(RHS);
    }
    return *this;
}
template <class T>
void BPlusTree<T>::copy_tree(const BPlusTree<T> &other) // copy other into this object
{
    BPlusTree<T> *last_node = NULL;
    copy_tree(other, last_node);
}
template <class T>
void BPlusTree<T>::copy_tree(const BPlusTree<T> &other, BPlusTree<T> *&last_node)
{
    dups_ok = other.dups_ok;
    next = NULL;
    child_count = other.child_count;
    copy_array(data, other.data, data_count, other.data_count); // No need to adjust data count as it's handled in copy array
    for (int i = 0; i < child_count; i++)
    {
        subset[i] = new BPlusTree<T>;
        subset[i]->copy_tree(*other.subset[i], last_node);
    }
    if (other.is_leaf())
    {
        if (last_node != NULL)
        {
            last_node->next = this;
        }
        last_node = this;
        // next = NULL;
    }
}
template <class T>
void BPlusTree<T>::insert(const T &entry) // insert entry into the tree
{
    loose_insert(entry);
    if (data_count > MAXIMUM)
    {
        // Create a new node and shallow copy
        BPlusTree<T> *newNode = new BPlusTree<T>(true);
        copy_array(newNode->data, data, newNode->data_count, data_count);       // Copy Data (Shallow)
                                                                                //  print_array(newNode->data,newNode->data_count);
        copy_array(newNode->subset, subset, newNode->child_count, child_count); // Copy Child (Shallow)
                                                                                // print_array(newNode->data,newNode->data_count);
        // cout << "newNode data_count: " << newNode->data_count << endl
        //      << "newNode child_count: " << newNode->child_count << endl;
        // Empty the root
        for (int i = 0; i < child_count; i++)
        {
            subset[i] = NULL;
        }
        for (int i = 0; i < data_count; i++)
        {
            // data[i] = 0;
            data[i] = T();
        }
        // cout << "root data_count: " << newNode->data_count << endl
        //      << "root child_count: " << newNode->child_count << endl;
        // print_array(data, 3);
        // print_array(subset, 4);
        data_count = 0;
        child_count = 1;
        subset[0] = newNode;
        // printData();
        // subset[0]->printData();
        fix_excess(0);
    }
}
template <class T>
void BPlusTree<T>::remove(const T &entry) // remove entry from the tree
{
}
template <class T>
void BPlusTree<T>::clear_tree() // clear this object (delete all nodes etc.)
{
    for (int i = 0; i < child_count; i++)
    {
        if (subset[i] != NULL)
        {
            subset[i]->clear_tree();
            delete subset[i];
            // subset[i] = NULL;
        }
    }
    // for (int i = 0; i < data_count; i++)
    // {
    //     data[i] = 0;
    // }
    child_count = 0;
    data_count = 0;
    next = NULL;
}
template <class T>
bool BPlusTree<T>::contains(const T &entry) const // true if entry can be found
{
    int i = first_ge(data, data_count, entry);
    bool found = (data[i] == entry);
    if (is_leaf())
    {
        if (found)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (found)
        {
            return subset[i + 1]->contains(entry);
        }
        else
        {
            return subset[i]->contains(entry);
        }
    }
}
template <class T>
T &BPlusTree<T>::get(const T &entry) // return a reference to entry
{
    if (!contains(entry))
    {
        insert(entry);
    }
    return get_existing(entry);
}
template <class T>
const T &BPlusTree<T>::get(const T &entry) const // return a reference to entry
{
    int i = first_ge(data, data_count, entry);
    bool found = (i < data_count && data[i] == entry);
    if (is_leaf())
    {
        if (found)
        {
            return data[i];
        }
        else
        {
            cout << "get_existing was called with non-existent entry" << endl;
            assert(found);
        }
    }
    else
    {
        if (found) // inner node
        {
            return subset[i + 1]->get(entry);
        }
        else // not found yet...
        {
            return subset[i]->get(entry);
        }
    }
}
template <class T>
T &BPlusTree<T>::get_existing(const T &entry) // return a reference to entry
{
    // on canvas
    int i = first_ge(data, data_count, entry);
    bool found = (i < data_count && data[i] == entry);
    if (is_leaf())
    {
        if (found)
        {
            return data[i];
        }
        else
        {
            cout << "get_existing was called with nonexistent entry" << endl;
            assert(found);
        }
    }
    if (found) // inner node
    {
        return subset[i + 1]->get(entry);
    }
    else // not found yet...
    {
        return subset[i]->get(entry);
    }
}
template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::find(const T &key) // return an iterator to this key.  NULL if not there.
{
    int i = first_ge(data, data_count, key);
    bool found = (i < data_count && data[i] == key);
    if (is_leaf())
    {
        if (found)
        {
            // cout << "data i : " << data[i] << endl;
            return Iterator(this, i);
        }
        else
        {
            return Iterator(NULL);
        }
    }
    else // is NOT leaf
    {
        if (found)
        {
            return subset[i + 1]->find(key);
        }
        else
        {
            return subset[i]->find(key);
        }
    }
}
template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::lower_bound(const T &key) // return first that goes NOT BEFORE key entry or next if does not exist: >= entry
{
    int i = first_ge(data, data_count, key);
    bool found = (i < data_count && data[i] == key);

    if (is_leaf())
    {
        //  for (Iterator temp(this, 0); temp.it != NULL; temp++)
        for (Iterator temp(this, i); temp.it != NULL; temp++)
        {
            // if (temp.it->data[i] <key)
            if (key <= *temp)
            {
                return temp;
            }
        }
        return Iterator(NULL);
    }
    else // is NOT leaf
    {
        if (found)
        {
            return subset[i + 1]->lower_bound(key);
        }
        else
        {
            return subset[i]->lower_bound(key);
        }
    }
    return Iterator(NULL);
}
template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::upper_bound(const T &key) // return first that goes AFTER key exist or not, the next entry  >entry
{
    // First equal to or greater than
    int i = first_ge(data, data_count, key);
    bool found = (i < data_count && data[i] == key);
    if (is_leaf())
    {
        // for (Iterator temp(this, 0); temp.it != NULL; temp++)
        for (Iterator temp(this, i); temp.it != NULL; temp++)
        {
            // if (temp.it->data[i] <key)
            if (key < *temp)
            {
                return temp;
            }
        }
        return Iterator(NULL);
    }
    else // is NOT leaf
    {
        if (found)
        {
            return subset[i + 1]->upper_bound(key);
        }
        else
        {
            return subset[i]->upper_bound(key);
        }
    }
    return Iterator(NULL);
}
template <class T>
int BPlusTree<T>::size() const // count the number of elements
{
    if (is_leaf())
    {
        return data_count;
    }
    else
    {
        int count = 0;
        for (int i = 0; i < child_count; i++)
        {
            count = count + subset[i]->size();
        }
        return data_count + count;
    }
}
template <class T>
bool BPlusTree<T>::empty() const // true if the tree is empty
{
    return (data_count == 0);
}
template <class T>
void BPlusTree<T>::print_tree(int level, ostream &outs) const
{
    if (is_leaf())
    {
        if (next != NULL)
        {
            outs << setw(5 * level) << ""
                 << " ^" << endl;
        }
        else
        {
            outs << setw(5 * level) << ""
                 << " NULL" << setw(5 * level) << endl
                 << ""
                 << " ^" << endl;
        }
        for (int i = data_count - 1; i >= 0; i--)
        {

            outs << setw(5 * level) << ""
                 << "[" << data[i] << "]" << endl;
        }
    }
    else
    {
        subset[child_count - 1]->print_tree(level + 1, outs);
        //----ARROW -> NULL
        if (next != NULL)
        {
            outs << setw(5 * level) << ""
                 << " ^" << endl;
        }
        else
        {
            outs << setw(5 * level) << ""
                 << " NULL" << setw(5 * level) << endl
                 << ""
                 << " ^" << endl;
        }
        //-------------
        for (int i = data_count - 1; i >= 0; i--)
        {
            outs << setw(5 * level) << ""
                 << "[" << data[i] << "]" << endl;
            subset[i]->print_tree(level + 1, outs);
        }
    }
}
template <class T>
bool BPlusTree<T>::is_valid()
{
    return true;
}
template <class T>
string BPlusTree<T>::pre_order()
{
    string result;
    if (is_leaf())
    {
        for (int i = 0; i < data_count; i++)
        {
            result += to_string(data[i]) + "|";
        }
    }
    else
    {
        for (int i = 0; i < child_count; i++)
        {
            if (i == data_count)
            {
                result += subset[i]->pre_order();
            }
            else
            {
                result += to_string(data[i]) + "|" + subset[i]->pre_order();
            }
        }
    }
    return result;
}
template <class T>
string BPlusTree<T>::in_order()
{
    string result = "";
    if (is_leaf())
    {
        for (int i = 0; i < data_count; i++)
        {

            result += to_string(data[i]) + "|";
        }
    }
    else
    {
        for (int i = 0; i <= data_count; i++)
        {
            result += subset[i]->in_order();
            if (i < data_count)
            {
                result += to_string(data[i]) + "|";
            }
        }
    }
    return result;
}
template <class T>
string BPlusTree<T>::post_order()
{
    string result = "";
    if (is_leaf())
    {
        for (int i = 0; i < data_count; i++)
        {

            result += to_string(data[i]) + "|";
        }
    }
    else
    {
        for (int i = 0; i < child_count; i++)
        {
            if (i == 0)
            {
                result += subset[i]->post_order();
            }
            else
            {
                result += subset[i]->post_order() + to_string(data[i - 1]) + "|";
                ;
            }
        }
        // for(int i=0;i<data_count;i++)
        // {
        //      result += to_string(data[i]) + "|";
        // }
    }
    return result;
}
template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::begin()
{
    return Iterator(get_smallest_node());
}
template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::end()
{
    return Iterator(NULL);
}
// PRIVATE:

template <class T>
T *BPlusTree<T>::find_ptr(const T &entry) // return a pointer to this key. NULL if not there.
{
    int i = first_ge(data, data_count, entry);
    bool found = (i < data_count && data[i] == entry);
    if (!is_leaf())
    {
        if (found)
        {
            return subset[i + 1]->find_ptr(entry);
        }
        else
        {
            return subset[i]->find_ptr(entry);
        }
    }
    else // is_leaf()==true
    {
        if (found)
        {
            return &data[i];
        }
        else
        {
            return NULL;
        }
    }
}
// insert element functions
template <class T>
void BPlusTree<T>::loose_insert(const T &entry) // allows MAXIMUM+1 data elements in the root
{
    int i = first_ge(data, data_count, entry);
    bool found = (i < data_count && data[i] == entry);
    if (is_leaf())
    {
        if (found)
        {
            if (dups_ok)
            {
                //  cout << "Dups okay" << endl;
                // data[i] = data[i] + entry;
                data[i] = data[i] + entry;
            }
            else
            {
                cout << "Dups not okay" << endl;
                data[i] = entry;
            }
        }
        else // Not found
        {
            ordered_insert(data, data_count, entry);
        }
    }
    else // is NOT leaf
    {
        if (found)
        {
            subset[i + 1]->loose_insert(entry);
            fix_excess(i + 1);
        }
        else // Not found
        {
            subset[i]->loose_insert(entry);
            fix_excess(i);
        }
    }
}
template <class T>
void BPlusTree<T>::fix_excess(int i) // fix excess in child i
{
    if (subset[i]->data_count <= MAXIMUM)
    {
        return;
    }
    // ordered_insert(data, data_count, subset[i]->data[data_count / 2]);
    // data_count++;
    T temp;
    BPlusTree<T> *newNode = new BPlusTree<T>();
    split(subset[i]->data, subset[i]->data_count, newNode->data, newNode->data_count);
    detach_item(subset[i]->data, subset[i]->data_count, temp);
    ordered_insert(data, data_count, temp);
    // cout << "Temp: " << temp << endl;
    // cout << "i :" << i << endl;
    //  subset[i]->printData();
    if (!subset[i]->is_leaf())
    {
        split(subset[i]->subset, subset[i]->child_count, newNode->subset, newNode->child_count);
        // subset[i]->child_count = subset[i]->child_count + 1;
    }

    insert_item(subset, i + 1, child_count, newNode);
    if (subset[i]->is_leaf())
    {
        insert_item(subset[i + 1]->data, 0, subset[i + 1]->data_count, temp);
        subset[i + 1]->next = subset[i]->next; // DOUBLE CHECK THIS
        subset[i]->next = subset[i + 1];
    }
}
// remove element functions:
template <class T>
void BPlusTree<T>::loose_remove(const T &entry) // allows MINIMUM-1 data elements in the root
{
    int i = first_ge(data, data_count, entry);
    bool found = (i < data_count && data[i] == entry);
    if (is_leaf())
    {
        if (found)
        {
            T temp;
            delete_item(data, i, data_count, temp);
        }
        else // Not found
        {
            return;
        }
    }
    else // is NOT leaf
    {
        if (found)
        {
            subset[i + 1]->loose_remove(entry);
        }
        else // Not found
        {
            subset[i]->loose_remove(entry);
        }
    }
    if (!is_leaf())
    {
        if (subset[i]->data_count < MINIMUM)
        {
            //   cout << "calling fix_shortage()" << endl;
            fix_shortage(i);
        }
    }
}
template <class T>
BPlusTree<T> *BPlusTree<T>::fix_shortage(int i) // fix shortage in child i , BPlusTree<T> * ->void
{
    //  if child i+1 has more than MINIMUM, rotate left
    // cout << "In fix_shortage()" << endl;
    if ((i < child_count - 1) && (subset[i + 1] != NULL) && (subset[i + 1]->data_count > MINIMUM))
    {
        cout << "transfer_left" << endl;
        transfer_left(i);
    }
    // else if child i-1 has more than MINIMUM, rotate right
    else if ((i > 0) && (subset[i - 1] != NULL) && (subset[i - 1]->data_count > MINIMUM))
    {
        cout << "transfer_right" << endl;
        transfer_right(i);
    }
    // else if there is a right child, merge child i with next child
    else if ((i < data_count) && (subset[i + 1] != NULL) && (subset[i + 1]->data_count <= MINIMUM))
    {
        cout << "Merge with next subset(i)" << endl;
        merge_with_next_subset(i);
    }
    else if (i > 0 && subset[i - 1] != NULL && subset[i - 1]->data_count <= MINIMUM)
    {
        cout << "Merge with next subset(i-1)" << endl;
        merge_with_next_subset(i - 1);
    }
}
// and return the smallest key in this subtree
template <class T>
BPlusTree<T> *BPlusTree<T>::get_smallest_node()
{
    if (!is_leaf())
    {
        return subset[0]->get_smallest_node();
    }
    else
    {
        return this;
    }
}
template <class T>
void BPlusTree<T>::get_smallest(T &entry) // entry := leftmost leaf
{
    if (!is_leaf())
    {
        subset[0]->get_smallest(entry);
    }
    else
    {
        assert(data_count > 0);
        entry = data[0];
    }
}
template <class T>
void BPlusTree<T>::get_biggest(T &entry) // entry := rightmost leaf
{
    if (!is_leaf())
    {
        subset[child_count - 1]->get_biggest(entry);
    }
    else
    {
        assert(data_count > 0);
        entry = data[data_count - 1];
    }
}
template <class T>
void BPlusTree<T>::remove_biggest(T &entry) // remove the biggest child of tree->entry
{
}
template <class T>
void BPlusTree<T>::transfer_left(int i) // transfer one element LEFT from child i , borrow from right
{
    // From B Tree Remove
    if (!subset[i]->is_leaf())
    {
        T temp;
        delete_item(subset[i + 1]->data, 0, subset[i + 1]->data_count, temp);
        cout << "temp : " << temp << endl;
        insert_item(subset[i]->data, subset[i]->data_count, subset[i]->data_count, data[i]);
        data[i] = temp;
        // child
        BPlusTree<T> *temp2;
        delete_item(subset[i + 1]->subset, 0, subset[i + 1]->child_count, temp2);
        insert_item(subset[i]->subset, subset[i]->child_count, subset[i]->child_count, temp2);
    }
    // B Plus Tree Remove
    if (subset[i]->is_leaf())
    {
        T temp;
        delete_item(subset[i + 1]->data, 0, subset[i + 1]->data_count, temp);
        insert_item(subset[i]->data, 0, subset[i]->data_count, temp);
        // insert_item(data,)
        data[i] = subset[i + 1]->data[0];
    }
}
template <class T>
void BPlusTree<T>::transfer_right(int i) // transfer one element RIGHT from child i , borrow from left
{
    if (!subset[i]->is_leaf())
    {
        T temp;
        //  cout << "temp : " << temp << endl;
        delete_item(subset[i - 1]->data, subset[i - 1]->data_count - 1, subset[i - 1]->data_count, temp);
        insert_item(subset[i]->data, 0, subset[i]->data_count, data[i - 1]);
        data[i - 1] = temp;
        // child
        BPlusTree<T> *temp2;
        delete_item(subset[i - 1]->subset, subset[i - 1]->child_count - 1, subset[i - 1]->child_count, temp2);
        insert_item(subset[i]->subset, 0, subset[i]->child_count, temp2);
    }
    if (subset[i]->is_leaf())
    {
        T temp;
        delete_item(subset[i - 1]->data, subset[i - 1]->data_count - 1, subset[i - 1]->data_count, temp);
        insert_item(subset[i]->data, 0, subset[i]->data_count, temp);
        data[i - 1] = temp;
    }
}
template <class T>
BPlusTree<T> *BPlusTree<T>::merge_with_next_subset(int i) // merge subset i with  i+1
{
    if (!subset[i]->is_leaf())
    {
        T temp;
        delete_item(data, i, data_count, temp);
        ordered_insert(subset[i]->data, subset[i]->data_count, temp);
        merge(subset[i]->data, subset[i]->data_count, subset[i + 1]->data, subset[i + 1]->data_count);
        // if (!subset[i]->is_leaf())
        // {
        merge(subset[i]->subset, subset[i]->child_count, subset[i + 1]->subset, subset[i + 1]->child_count);
        // }
        BPlusTree<T> *temp2 = NULL;
        delete_item(subset, i + 1, child_count, temp2);
        delete temp2;
    }
}

// DEBUGGING FUNCTIONS:
template <class T>
void BPlusTree<T>::makeTree()
{
    // Tree for Fix Excess:
    //  Level 0
    data[0] = 50;
    data[1] = 100;
    data_count = 2;
    child_count = 3;
    next = NULL;
    subset[0] = new BPlusTree<T>();
    subset[1] = new BPlusTree<T>();
    subset[2] = new BPlusTree<T>();

    // Level 1
    subset[0]->data[0] = 25;
    subset[0]->data_count = 1;
    subset[0]->child_count = 0;
    subset[0]->next = subset[1];

    subset[1]->data[0] = 50;
    subset[1]->data[1] = 70;
    subset[1]->data_count = 2;
    subset[1]->child_count = 0;
    subset[1]->next = subset[2];

    //  subset[2]->data[0] = 100;
    subset[2]->data_count = 0;
    subset[2]->child_count = 0;
    subset[2]->next = NULL;
}
template <class T>
void BPlusTree<T>::printData()
{
    cout << "[";
    for (int i = 0; i < data_count; i++)
    {
        cout << " " << data[i] << " ";
    }
    cout << "]" << endl;
    cout << "Data count: " << data_count << endl;
    cout << "Child count: " << child_count << endl;
    if (next == NULL)
    {
        cout << "Next: NULL" << endl;
    }
    else
    {
        cout << "Next : " << endl;
        next->printData();
    }
}
#endif

//  //Tree for Regular Testing:
//     // Level 0
//     data[0] = 40;
//     data[1] = 60;
//     data_count = 2;
//     child_count = 3;
//     next = NULL;
//     subset[0] = new BPlusTree<T>();
//     subset[1] = new BPlusTree<T>();
//     subset[2] = new BPlusTree<T>();

//     // Level 1
//     subset[0]->data[0] = 20;
//     subset[0]->data_count = 1;
//     subset[0]->child_count = 2;
//     subset[0]->next = NULL;
//     subset[0]->subset[0] = new BPlusTree<T>();
//     subset[0]->subset[1] = new BPlusTree<T>();

//     subset[1]->data[0] = 50;
//     subset[1]->data_count = 1;
//     subset[1]->child_count = 2;
//     subset[1]->next = NULL;
//     subset[1]->subset[0] = new BPlusTree<T>();
//     subset[1]->subset[1] = new BPlusTree<T>();

//     subset[2]->data[0] = 70;
//     subset[2]->data[1] = 80;
//     subset[2]->data_count = 2;
//     subset[2]->child_count = 3;
//     subset[2]->next = NULL;
//     subset[2]->subset[0] = new BPlusTree<T>();
//     subset[2]->subset[1] = new BPlusTree<T>();
//     subset[2]->subset[2] = new BPlusTree<T>();

//     // Level 2
//     subset[0]->subset[0]->data[0] = 0;
//     subset[0]->subset[0]->data[1] = 10;
//     subset[0]->subset[0]->data_count = 2;
//     subset[0]->subset[0]->child_count = 0;
//     subset[0]->subset[0]->next = subset[0]->subset[1];

//     subset[0]->subset[1]->data[0] = 20;
//     subset[0]->subset[1]->data[1] = 30;
//     subset[0]->subset[1]->data_count = 2;
//     subset[0]->subset[1]->child_count = 0;
//     subset[0]->subset[1]->next = subset[1]->subset[0];

//     subset[1]->subset[0]->data[0] = 40;
//     subset[1]->subset[0]->data_count = 1;
//     subset[1]->subset[0]->child_count = 0;
//     subset[1]->subset[0]->next = subset[1]->subset[1];

//     subset[1]->subset[1]->data[0] = 50;
//     subset[1]->subset[1]->data_count = 1;
//     subset[1]->subset[1]->child_count = 0;
//     subset[1]->subset[1]->next = subset[2]->subset[0];

//     subset[2]->subset[0]->data[0] = 60;
//     subset[2]->subset[0]->data_count = 1;
//     subset[2]->subset[0]->child_count = 0;
//     subset[2]->subset[0]->next = subset[2]->subset[1];

//     subset[2]->subset[1]->data[0] = 70;
//     subset[2]->subset[1]->data_count = 1;
//     subset[2]->subset[1]->child_count = 0;
//     subset[2]->subset[1]->next = subset[2]->subset[2];

//     subset[2]->subset[2]->data[0] = 80;
//     subset[2]->subset[2]->data[1] = 90;
//     subset[2]->subset[2]->data_count = 2;
//     subset[2]->subset[2]->child_count = 0;
//     subset[2]->subset[2]->next = NULL;

// // Tree for Fix Excess:
// //  Level 0
// data[0] = 500;
// data[1] = 700;
// data_count = 2;
// child_count = 3;
// next = NULL;
// subset[0] = new BPlusTree<T>();
// subset[1] = new BPlusTree<T>();
// subset[2] = new BPlusTree<T>();

// // Level 1
// subset[0]->data[0] = 300;
// subset[0]->data_count = 1;
// subset[0]->child_count = 0;
// subset[0]->next = subset[1];

// subset[1]->data[0] = 500;
// subset[1]->data[1] = 600;
// subset[1]->data_count = 2;
// subset[1]->child_count = 0;
// subset[1]->next = subset[2];

// subset[2]->data[0] = 700;
// subset[2]->data[1] = 1000;
// subset[2]->data_count = 2;
// subset[2]->child_count = 0;
// subset[2]->next = NULL;