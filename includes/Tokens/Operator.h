#ifndef OPERATOR_H
#define OPERATOR_H
#include "../../includes/Tokens/Tokens.h"
class Operator : public Token
{
public:
    Operator()
    {
        s = "";
    }
    Operator(string str)
    {
        s = str;
    }
    string get_string() override
    {
        return s;
    }
    int get_type() override
    {
        return OPERATOR;
    }
    void print(ostream &outs) const override
    {
        outs << s;
    }
  

private:
 
    string s;
};
#endif