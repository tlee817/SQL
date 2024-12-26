#ifndef RELATIONAL_H
#define RELATIONAL_H
#include "../../includes/Tokens/Tokens.h"
class Relational : public Token
{
public:
    Relational()
    {
        s = "";
    }
    Relational(string str)
    {
        s = str;
    }
    string get_string() override
    {
        return s;
    }
    int get_type() override
    {
        return RELATIONAL;
    }
    void print(ostream &outs) const override
    {
        outs << s;
    }

private:
    string s;
};
#endif