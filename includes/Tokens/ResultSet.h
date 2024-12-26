#ifndef RESULTSET_H
#define RESULTSET_H
#include "../../includes/Tokens/Tokens.h"
#include <algorithm>
class ResultSet : public Token
{
public:
    ResultSet()
    {
        s = "";
    }
    ResultSet(string str)
    {
        s = str;
    }
    string get_string() override
    {
        return s;
    }
    int get_type() override
    {
        return RESULTSET;
    }
    void print(ostream &outs) const override
    {
        outs << recno_vector;
    }
    void set_recno_vector(vector<long> v)
    {
        recno_vector.clear();
        for (int i = 0; i < v.size(); i++)
        {
            recno_vector.push_back(v[i]);
        }
        sort(recno_vector.begin(), recno_vector.end());
    }
    vector<long> get_recno_vector()
    {
        return recno_vector;
    }

private:
    string s;
    vector<long> recno_vector;
};
#endif