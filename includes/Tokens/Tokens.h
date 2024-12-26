#include <iostream>
#ifndef TOKENS_H
#define TOKENS_H
using namespace std;

enum TOKEN_TYPE
{
    TOKEN,
    TOKENSTR,
    RESULTSET,
    OPERATOR,
    RELATIONAL,
    LOGICAL,
    LPAREN,
    RPAREN
};

class Token
{
public:
    Token();
    Token(string str, int type);
    friend ostream &operator<<(ostream &outs, const Token &t);
    int type() const;
    void setType(int t);
    string type_string() const;
    string token_str() const;
    // I added setString
    void setString(string s)
    {
        // if (_type == 9)
        // {
        //     cout << "entered type == 9" << endl;
        //     s.erase(s.begin());
        //     cout << "s: " << s << endl;
        // }
        _token = s;
    }
    friend ostream &operator<<(ostream &outs, const Token *t)
    {
        if (t != NULL)
        {
            outs << *t;
        }
        else
        {
            outs << "NULL TOKEN";
        }
        return outs;
    }

    // Virtual
    virtual string get_string()
    {
        return _token;
    }
    virtual int get_type()
    {
        return TOKEN;
    }
    virtual void print(ostream &outs) const
    {
        // outs << "Inside parent print()";
        outs << _token;
    }
    // virtual void eval()=0;

private:
    string _token;
    int _type;
};

#endif