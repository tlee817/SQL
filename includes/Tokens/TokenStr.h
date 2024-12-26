#ifndef TOKENSTR_H
#define TOKENSTR_H
#include "../../includes/Tokens/Tokens.h"
class TokenStr : public Token
{
public:
    TokenStr()
    {
        s = "";
    }
    TokenStr(string str)
    {
        s = str;
    }
    string get_string() override
    {
        return s;
    }
    int get_type() override
    {
        return TOKENSTR;
    }
    void print(ostream &outs) const override
    {
        outs << s;
    }

private:
    string s;
};
#endif