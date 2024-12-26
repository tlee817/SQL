#include "../../includes/tokenizer/constants.h"
#include "../../includes/Tokens/Tokens.h"

Token::Token() : _token(""), _type(0) {}

Token::Token(string str, int type) : _token(str), _type(type) {}

ostream &operator<<(ostream &outs, const Token &t)
{
    // outs << t._token;
    t.print(outs);
    return outs;
}

int Token::type() const
{
    return _type;
}
string Token::type_string() const
{
    /*
    const int TOKEN_NUMBER = 1;
    const int TOKEN_ALPHA = 2;
    const int TOKEN_SPACE = 3;
    const int TOKEN_OPERATOR = 4;
    const int TOKEN_PUNC = 5;
    */

    switch (_type)
    {
    case TOKEN_NUMBER:
        return "Number";
    case TOKEN_ALPHA:
        return "ALPHA";
    case TOKEN_SPACE:
        return "Space";
    case TOKEN_OPERATOR:
        return "Operator";
    case TOKEN_PUNC:
        return "Punctuation";
    case TOKEN_DOUBLE:
        return "Double";
    case TOKEN_NAME:
        return "Name";
    case TOKEN_PAREN:
        return "Paren";
    default:
        return "Unknown";
        break;
    }
}

string Token::token_str() const
{
    return _token;
}

void Token::setType(int t)
{
    _type = t;
}
