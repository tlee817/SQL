#ifndef LOGICAL_H
#define LOGICAL_H
#include "../../includes/Tokens/Tokens.h"
#include <algorithm>
class Logical : public Token
{
public:
    Logical()
    {
        s = "";
    }
    Logical(string str)
    {
        s = str;
    }
    string get_string() override
    {
        return s;
    }
    int get_type() override
    {
        return LOGICAL;
    }
    void print(ostream &outs) const override
    {
        outs << s;
    }
    vector<long> eval(vector<long> v1, vector<long> v2)
    {
        vector<long> result;
        if (s == "and")
        {
            // return set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end());
            return vectors_intersection(v1, v2);
        }
        else if (s == "or")
        {
            return vectors_union(v1, v2);
        }
        else
        {
            cout << "In eval() , YOU SHOULD NOT BE HERE" << endl;
            return result;
        }
    }

private:
    vector<long> vectors_intersection(vector<long> v1, vector<long> v2)
    {
        //     v1: {1,2,3,4,5,6}
        //     v2: {3,4,5,7}
        // result: {3,4,5}
        vector<long> result;
        for (int i = 0; i < v1.size(); i++)
        {
            for (int j = 0; j < v2.size(); j++)
            {
                if (v1[i] == v2[j] && !element_exists(result, v1[i]))
                {
                    result.push_back(v1[i]);
                }
            }
        }
        sort(result.begin(), result.end());
        return result;
    }
    vector<long> vectors_union(vector<long> v1, vector<long> v2)
    {
        //     v1: {1,2,3,4,5,6}
        //     v2: {3,4,5,7}
        // result: {1,2,3,4,5,6,7}
        vector<long> result;
        for (int i = 0; i < v1.size(); i++)
        {
            if (!element_exists(result, v1[i]))
            {
                result.push_back(v1[i]);
            }
        }
        for (int i = 0; i < v2.size(); i++)
        {
            if (!element_exists(result, v2[i]))
            {
                result.push_back(v2[i]);
            }
        }
        sort(result.begin(), result.end());
        return result;
    }

    bool element_exists(vector<long> search_me, long element)
    {
        for (int i = 0; i < search_me.size(); i++)
        {
            if (search_me[i] == element)
            {
                return true;
            }
        }
        return false;
    }
    string s;
};
#endif