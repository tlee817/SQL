#ifndef B_PLUS_TREE_ARRAY_FUNCS_H
#define B_PLUS_TREE_ARRAY_FUNCS_H
#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
using namespace std;

template <class T>
T maximal(const T &a, const T &b) // return the larger of the two items
{
    if (a >= b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

template <class T>
void swap(T &a, T &b) // swap the two items
{
    T temp = a;
    a = b;
    b = temp;
}
template <class T>
void print_array(const T data[], int n, int pos = -1) // print array data
{
    for (int i = 0; i < n; i++)
    {
        cout << data[i] << " ";
    }
}

template <class T>
int index_of_maximal(T data[], int n) // return index of the largest item in data
{
    int index = 0;
    T largest = data[0];
    for (int i = 0; i < n; i++)
    {
        if (largest < data[i])
        {
            index = i;
            largest = data[i];
        }
    }
    return index;
}
template <class T>
void insert_item(T data[], int i, int &n, T entry) // insert entry at index i in data
{
    for (int j = n; j > i; j--)
    {
        data[j] = data[j - 1];
    }
    data[i] = entry;
    n++;
}
template <class T>
void ordered_insert(T data[], int &n, T entry) // insert entry into the sorted array data with length n
{
    int i = 0;
    while (i < n && data[i] < entry)
    {
        i++;
    }
    insert_item(data, i, n, entry);
}
template <class T>
int first_ge(const T data[], int n, const T &entry) // return the first element in data that is not less than entry
{
    for (int i = 0; i < n; i++)
    {
        if (data[i] >= entry)
        {
            return i;
        }
    }
    // cout << "IN first_ge() , ALL ELEMENTS IN DATA ARE LESS THAN ENTRY , RETURNING SIZE" << endl;
    return n;
}
template <class T>
void attach_item(T data[], int &n, const T &entry) // append entry to the right of data
{
    data[n] = entry;
    n++;
}

template <class T>
void detach_item(T data[], int &n, T &entry) // remove the last element in data and place it in entry
{
    if (n <= 0)
    {
        cout << "In detach_item() , (n<=0) coniditon , returning..." << endl;
        return;
    }

    entry = data[n - 1];
    data[n - 1] = T();
    n--;
    // cout << "n: " << n << endl;
}
template <class T>
void delete_item(T data[], int i, int &n, T &entry) // delete item at index i and place it in entry
{
    if (i > n)
    {
        cout << "In delete_item() , i > n" << endl;
        return;
    }
    if (n == 0)
    {
        return;
    }
    entry = data[i];
    //   cout << "In delete_item() ,entry = " << entry << endl;
    for (int j = i; j < n - 1; j++)
    {
        data[j] = data[j + 1];
    }
    data[n - 1] = 0;
    n--;
}
template <class T>
void merge(T data1[], int &n1, T data2[], int &n2) // append data2 to the right of data1
{
    for (int i = 0; i < n2; i++)
    {
        data1[n1 + i] = data2[i];
        //   cout << "n1++" << endl;
    }
    n1 = n1 + n2;
    // Reset data 2 and its size
    for (int j = 0; j < n2; j++)
    {
        data2[j] = 0;
    }
    n2 = 0;
}
template <class T>
void split(T data1[], int &n1, T data2[], int &n2) // move n/2 elements from the right of data1 and move to data2
{
    // Assuming data2[] is empty and data2_size = 0
    // int start = (n1 / 2);
    int start = (n1 + 1) / 2;
    n2 = 0;
    // cout << "In spilt() , start: " << start << " n1:" << n1 << endl;
    for (int i = start; i < n1; i++)
    {
        data2[n2] = data1[i];
      //  data1[i] = 0;
      data1[i] = T();
        // cout << "In spilt() , " << data2[j] << endl;
        n2++;
    }
    n1 = n1 - n2;
    // cout << " data1[] : ";
    // print_array(data1,n1);
    // cout << endl;
    // cout << " data2[] : ";
    // print_array(data2,n2);
    // cout << endl;
}
template <class T>
void copy_array(T dest[], const T src[], int &dest_size, int src_size) // copy src[] into dest[]
{
    for (int i = 0; i < src_size; i++)
    {
        dest[i] = src[i];
    }
    dest_size = src_size;
}

template <class T>
bool is_gt(const T data[], int n, const T &item) // item > all data[i]
{
    for (int i = 0; i < n; i++)
    {
        if (item <= data[i])
        {
            return false;
        }
    }
    return true;
}

template <class T>
bool is_le(const T data[], int n, const T &item) // item <= all data[i]
{
    for (int i = 0; i < n; i++)
    {
        if (item > data[i])
        {
            return false;
        }
    }
    return true;
}

//-------------- Vector Extra operators: ---------------------

template <typename T>
ostream &operator<<(ostream &outs, const vector<T> &list) // print vector list
{
    outs<<" < ";
    for (int i = 0; i < list.size(); i++)
    {
        outs<<"[ " << list[i] << " ]";
    }
     outs<<"> ";
    return outs;
}
template <typename T>
vector<T> &operator+=(vector<T> &list, const T &addme) // list.push_back addme
{
    list.push_back(addme);
    return list;
}

#endif