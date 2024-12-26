#ifndef MULTI_MAP_H
#define MULTI_MAP_H
#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include "../../includes/bplustree/bplustree.h"
using namespace std;

template <typename K, typename V>
struct MPair
{
    K key;
    vector<V> value_list;

    //--------------------------------------------------------------------------------
    /*      MPair CTORs:
     *  must have these CTORs:
     *  - default CTOR / CTOR with a key and no value: this will create an empty vector
     *  - CTOR with a key AND a value: pushes the value into the value_list
     *  _ CTOR with a key and a vector of values (to replace value_list)
     */
    //--------------------------------------------------------------------------------
    MPair(const K &k = K()) // - default CTOR / CTOR with a key and no value: this will create an empty vector
    {
        key = k;
        value_list.clear();
        // while (!value_list.empty())
        // {
        //     value_list.pop_back();
        // }
    }
    MPair(const K &k, const V &v) // - CTOR with a key AND a value: pushes the value into the value_list
    {
        key = k;
        value_list.push_back(v);
    }
    MPair(const K &k, const vector<V> &vlist) //_ CTOR with a key and a vector of values (to replace value_list)
    {
        key = k;
        // while (!value_list.empty())
        // {
        //     value_list.pop_back();
        // }
        value_list.clear();
        for (int i = 0; i < vlist.size(); i++)
        {
            value_list.push_back(vlist[i]);
        }
    }
    //--------------------------------------------------------------------------------

    // You'll need to overlod << for your vector:
    friend ostream &operator<<(ostream &outs, const MPair<K, V> &print_me)
    {
        outs << setw(15) << print_me.key << ":" << setw(5) << print_me.value_list;
        // outs << print_me.key << ":" << print_me.value_list;
        return outs;
    }
    friend bool operator==(const MPair<K, V> &lhs, const MPair<K, V> &rhs)
    {
        return (lhs.key == rhs.key);
    }
    friend bool operator<(const MPair<K, V> &lhs, const MPair<K, V> &rhs)
    {
        return (lhs.key < rhs.key);
    }
    friend bool operator<=(const MPair<K, V> &lhs, const MPair<K, V> &rhs)
    {
        return (lhs.key <= rhs.key);
    }
    friend bool operator>(const MPair<K, V> &lhs, const MPair<K, V> &rhs)
    {
        return (lhs.key > rhs.key);
    }
    friend bool operator>=(const MPair<K, V> &lhs, const MPair<K, V> &rhs)
    {
        return (lhs.key >= rhs.key);
    }
    friend MPair<K, V> operator+(const MPair<K, V> &lhs, const MPair<K, V> &rhs)
    {
        // MultiMap: Append to the right
        MPair<K, V> temp;
        temp.key = lhs.key;
        temp.value_list = lhs.value_list;
        for (int i = 0; i < rhs.value_list.size(); i++)
        {
            temp.value_list.push_back(rhs.value_list[i]);
        }
        return temp;
    }
};

template <typename K, typename V>
class MMap
{
public:
    typedef BPlusTree<MPair<K, V>> map_base;
    class Iterator
    {
    public:
        friend class MMap;
        Iterator()
        {
            _it = NULL;
        }
        Iterator(typename map_base::Iterator it)
        {
            _it = it;
        }
        Iterator operator++(int unused)
        {
            Iterator temp = _it;
            _it++;
            return temp;
        }
        Iterator operator++()
        {
            ++_it;
            return *this;
        }
        MPair<K, V> operator*()
        {
            return *_it;
        }
        friend bool operator==(const Iterator &lhs, const Iterator &rhs)
        {
            return (lhs._it == rhs._it);
        }
        friend bool operator!=(const Iterator &lhs, const Iterator &rhs)
        {
            return (lhs._it != rhs._it);
        }

    private:
        typename map_base::Iterator _it;
    };

    MMap();

    //  Iterators
    Iterator begin();
    Iterator end();

    //  Capacity
    int size() const;
    bool empty() const;

    //  Element Access
    const vector<V> &operator[](const K &key) const;
    vector<V> &operator[](const K &key);
    // V &at(const K &key) const; // DOUBLE CHECK WITH PROF
    vector<V> &at(const K &key);
    // const V &at(const K &key) const;
    //   Modifiers
    void insert(const K &k, const V &v);
    void erase(const K &key);
    void clear();

    //  Operations:
    bool contains(const K &key) const;
    vector<V> &get(const K &key);
    const vector<V> &get(const K &key) const;
    Iterator find(const K &key);
    int count(const K &key);
    // I have not writtent hese yet, but we will need them:
    Iterator lower_bound(const K &key); // DOUBLE CHECK WIHT PROF
    Iterator upper_bound(const K &key); // DOUBLE CHECK WIHT PROF
    //    equal_range:

    bool is_valid();

    friend ostream &operator<<(ostream &outs, const MMap<K, V> &print_me)
    {
        outs << print_me.mmap << endl;
        return outs;
    }

    void print_lookup();

private:
    BPlusTree<MPair<K, V>> mmap;
};

// MMap
template <typename K, typename V>
MMap<K, V>::MMap() // DOUBLE CHECK THIS
{
    BPlusTree<MPair<K, V>> mmap(true);
}

template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::begin()
{
    return (Iterator(mmap.begin()));
}

template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::end()
{
    return (Iterator(mmap.end()));
}
//  Capacity
template <typename K, typename V>
int MMap<K, V>::size() const
{
    return (mmap.size());
}
template <typename K, typename V>
bool MMap<K, V>::empty() const
{
    return (mmap.size() == 0);
}

//  Element Access
template <typename K, typename V>
const vector<V> &MMap<K, V>::operator[](const K &key) const
{
    return mmap.get(key).value_list;
}
template <typename K, typename V>
vector<V> &MMap<K, V>::operator[](const K &key)
{
    return mmap.get(key).value_list;
}
template <typename K, typename V>
vector<V> &MMap<K, V>::at(const K &key)
{
    return mmap.get(key).value_list;
}

//  Modifiers
template <typename K, typename V>
void MMap<K, V>::insert(const K &k, const V &v)
{
    MPair<K, V> temp(k, v);
    mmap.insert(temp);
}
template <typename K, typename V>
void MMap<K, V>::erase(const K &key)
{
    mmap.remove(key);
}
template <typename K, typename V>
void MMap<K, V>::clear()
{
    mmap.clear_tree();
}

//  Operations:
template <typename K, typename V>
bool MMap<K, V>::contains(const K &key) const
{
    return mmap.contains(key);
}
template <typename K, typename V>
vector<V> &MMap<K, V>::get(const K &key) // non-const
{
    return mmap.get(key).value;
}
template <typename K, typename V>
const vector<V> &MMap<K, V>::get(const K &key) const // const
{
    return mmap.get(key).value;
}
template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::find(const K &key)
{
    return Iterator(mmap.find(key));
}
template <typename K, typename V>
int MMap<K, V>::count(const K &key)
{
    return mmap.size();
}
// I have not writtent hese yet, but we will need them:
template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::lower_bound(const K &key)
{
    return Iterator(mmap.lower_bound(key));
}
template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::upper_bound(const K &key)
{
    return Iterator(mmap.upper_bound(key));
}
//    equal_range:
template <typename K, typename V>
bool MMap<K, V>::is_valid()
{
    return true;
}

template <typename K, typename V>
void MMap<K, V>::print_lookup()
{
    MMap<K, V>::Iterator it;
    for (it = mmap.begin(); it != mmap.end(); it++)
    {
        cout << *it << endl;
    }
}
#endif