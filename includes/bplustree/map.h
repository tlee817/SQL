#ifndef MAP_H
#define MAP_H
#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include "../../includes/bplustree/bplustree.h"
using namespace std;

template <typename K, typename V>
struct Pair
{
    K key;
    V value;
    Pair(const K &k = K(), const V &v = V()) : key(k), value(v)
    {
    }
    friend ostream &operator<<(ostream &outs, const Pair<K, V> &print_me)
    {
        // 100:1001 , key:value
        // outs << print_me.key << ":" << print_me.value;
        outs << setw(15) << print_me.key << ":" << setw(5) << print_me.value;
        return outs;
    }
    friend bool operator==(const Pair<K, V> &lhs, const Pair<K, V> &rhs)
    {
        return (lhs.key == rhs.key);
    }
    friend bool operator<(const Pair<K, V> &lhs, const Pair<K, V> &rhs)
    {
        return (lhs.key < rhs.key);
    }
    friend bool operator>(const Pair<K, V> &lhs, const Pair<K, V> &rhs)
    {
        return (lhs.key > rhs.key);
    }
    friend bool operator<=(const Pair<K, V> &lhs, const Pair<K, V> &rhs)
    {
        return (lhs.key <= rhs.key);
    }
    friend bool operator>=(const Pair<K, V> &lhs, const Pair<K, V> &rhs)
    {
        return (lhs.key >= rhs.key);
    }
    friend Pair<K, V> operator+(const Pair<K, V> &lhs, const Pair<K, V> &rhs)
    {
        // Map : *** Overwrite lhs ***
        Pair<K, V> temp(rhs.key, rhs.value);
        return temp;
    }
};

template <typename K, typename V>
class Map
{
public:
    typedef BPlusTree<Pair<K, V>> map_base;
    class Iterator
    {
    public:
        friend class Map;
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
        Pair<K, V> operator*()
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

    Map();
    //  Iterators
    Iterator begin();
    Iterator end();

    //  Capacity
    int size() const;
    bool empty() const;

    //  Element Access

    V &operator[](const K &key);
    const V &operator[](const K &key) const;
    V &at(const K &key);
    const V &at(const K &key) const;

    //  Modifiers
    void insert(const K &k, const V &v);
    void erase(const K &key);
    void clear();
    V get(const K &key);

    //  Operations:
    Iterator find(const K &key);
    bool contains(const Pair<K, V> &target) const;

    // I have not writtent hese yet, but we will need them:
    //    int count(const K& key);
    Iterator lower_bound(const K &key);
    Iterator upper_bound(const K &key);
    //    equal_range:

    bool is_valid() { return map.is_valid(); }

    friend ostream &operator<<(ostream &outs, const Map<K, V> &print_me)
    {
        outs << print_me.map << endl;
        return outs;
    }
    void print_lookup();
    void print_key();

private:
    int key_count;
    BPlusTree<Pair<K, V>> map;
};

// MAP
template <typename K, typename V>
Map<K, V>::Map() : key_count(0) {}

template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::begin()
{
    return Iterator(map.begin());
}
template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::end()
{
    return Iterator(map.end());
}
template <typename K, typename V>
int Map<K, V>::size() const
{
    return (map.size());
}
template <typename K, typename V>
bool Map<K, V>::empty() const
{
    return (map.size() == 0);
}
template <typename K, typename V>
V &Map<K, V>::operator[](const K &key) // Non-const
{
    return at(key);
}
template <typename K, typename V> // Const
const V &Map<K, V>::operator[](const K &key) const
{
    return at(key);
}
template <typename K, typename V>
V &Map<K, V>::at(const K &key) // Non-const
{
    return map.get(key).value;
}
template <typename K, typename V> // Const
const V &Map<K, V>::at(const K &key) const
{
    return map.get(key).value;
}
template <typename K, typename V>
void Map<K, V>::insert(const K &k, const V &v)
{
    Pair<K, V> temp(k, v);
    map.insert(temp);
}
template <typename K, typename V>
void Map<K, V>::erase(const K &key)
{
    map.remove(key);
}
template <typename K, typename V>
V Map<K, V>::get(const K &key)
{
    return map.get(key).value;
}
template <typename K, typename V>
void Map<K, V>::clear()
{
    map.clear_tree();
}
template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::find(const K &key)
{
    return Iterator(map.find(key));
}
template <typename K, typename V>
bool Map<K, V>::contains(const Pair<K, V> &target) const
{
    return map.contains(target);
}
template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::lower_bound(const K &key)
{
    return Iterator(map.lower_bound(key));
}
template <typename K, typename V>
typename Map<K, V>::Iterator Map<K, V>::upper_bound(const K &key)
{
    return Iterator(map.upper_bound(key));
}

template <typename K, typename V>
void Map<K, V>::print_lookup()
{
    Map<K, V>::Iterator it;
    for (it = map.begin(); it != map.end(); it++)
    {
        cout << *it << endl;
    }
}

template <typename K, typename V>
void Map<K, V>::print_key()
{
    Map<K, V>::Iterator it;
    for (it = map.begin(); it != map.end(); it++)
    {
        cout << "-> " << (*it).key << endl;
    }
}
// ITERATOR
// template <typename K, typename V>
// Map<K, V>::Iterator::Iterator(typename map_base::Iterator it) : _it(it) {}
// template <typename K, typename V>
// typename Map<K, V>::Iterator Map<K, V>::Iterator::operator++(int unused)
// {
//     Iterator bruh;
//     return bruh;
// }
// template <typename K, typename V>
// typename Map<K, V>::Iterator Map<K, V>::Iterator::operator++()
// {
//     return *this;
// }
// template <typename K, typename V>
// Pair<K, V> Map<K, V>::Iterator::operator*()
// {
// }

#endif