#ifndef LPAREN_H
#define LPAREN_H
#include "../../includes/Tokens/Tokens.h"
class LParen : public Token
{
public:
    LParen()
    {
        s = "(";
    }
    string get_string() override
    {
        return s;
    }
    int get_type() override
    {
        return LPAREN;
    }
    void print(ostream &outs) const override
    {
        outs << s;
    }

private:
    string s;
};
#endif