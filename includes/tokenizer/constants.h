#ifndef CONSTANTS_H
#define CONSTANTS_H

const int MAX_COLUMNS = 128;
const int MAX_ROWS = 100;
const int MAX_BUFFER = 200;

const char ALFA[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char DIGITS[] = "0123456789";
const char OPERATORS[] = "><=!+-%&|*"; // 5/30: Added * and () as OPERATORS --------->*** 6/5: updates: removed ()
const char PAREN[] = "()";             // 6/5: Added PAREN[] to handle ()
const char SPACES[] = {' ', '\t', '\n', '\0','\\'};
const char PUNC[] = "?.,:;'`~!";
const int START_DOUBLE = 0;
const int START_SPACES = 4;
const int START_ALPHA = 6;
const int START_OPERATOR = 20;
const int START_PUNC = 10;

// token types:
const int TOKEN_NUMBER = 1;
const int TOKEN_ALPHA = 2;
const int TOKEN_SPACE = 3;
const int TOKEN_OPERATOR = 4;
const int TOKEN_PUNC = 5;
const int TOKEN_DOUBLE = 7;
// const int TOKEN_NAME = 8;
const int TOKEN_NAME = 9;
const int TOKEN_PAREN = 10;

const int TOKEN_UNKNOWN = -1;
const int TOKEN_END = -2;

#endif