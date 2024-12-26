#ifndef STOKENIZE_H
#define STOKENIZE_H

#include "../../includes/tokenizer/constants.h"
#include "../../includes/Tokens/Tokens.h"
#include "../../includes/tokenizer/state_machine_functions.h"

class STokenizer
{
public:
    STokenizer();
    STokenizer(char str[]);
    static int _table[MAX_ROWS][MAX_COLUMNS]; // private
    bool done();                              // true: there are no more tokens
    bool more();                              // true: there are more tokens
    //

    //---------------
    // extract one token (very similar to the way cin >> works)
    friend STokenizer &operator>>(STokenizer &s, Token &t);

    // set a new string as the input string
    void set_string(char str[]);
    int get_position();
    // extract the longest string that match one of the acceptable token types
    bool get_token(int &start_state, Token &t); // private
    // create table for all the tokens we will recognize (e.g. doubles, words, etc.)
    void make_table(); // private
    void get_buffer();

private:
    //---------------------------------
    char _buffer[MAX_BUFFER]; // input string
    int _pos;                 // current position in the string
    int t;
};

#endif