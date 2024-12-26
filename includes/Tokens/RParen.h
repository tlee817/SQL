#ifndef RPAREN_H
#define RPAREN_H
#include "../../includes/Tokens/Tokens.h"
class RParen : public Token
{
public:
    RParen()
    {
        s = ")";
    }
    string get_string() override
    {
        return s;
    }
    int get_type() override
    {
        return RPAREN;
    }
    void print(ostream &outs) const override
    {
        outs << s;
    }

private:
    string s;
};
#endif