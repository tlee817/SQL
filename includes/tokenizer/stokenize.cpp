#include <cstring>
#include "../../includes/tokenizer/stokenize.h"
#include <iomanip>
#include <iostream>

// Definitions
STokenizer::STokenizer()
{
    _pos = 0;
    _buffer[0] = '\0';
    make_table();
}
STokenizer::STokenizer(char str[])
{
    _pos = 0;
    t = 0;
    strcpy(_buffer, str);
    // cout << "length: " << strlen(_buffer) << endl;
    make_table();
}
bool STokenizer::done() // true: there are no more tokens
{
    // if pos=='\0', pos++, return f
    /*
    if (_buffer[_pos - 1] == '\0')
    {
        // cout << "enter _pos == NULL condition" << endl
        //     << "Position : " << _pos << endl;

        //   _pos++;
        return true;
    }*/
    // if(_buffer[_pos-1]=='\0')
    // {
    //     return true;
    // }
    if (_pos > strlen(_buffer))
    {
        //   cout << "enter condition 1:True" << endl ;
        //  cout << "Positon in done: " << _pos << endl;
        // cout << "Buffer length: " << strlen(_buffer) << endl;
        //  cout<<"DONE"<<endl;
        // t = 0;
        return true;
    }
    else
    {
        // cout << "enter condition 2:False" <<endl;
        // cout << "Positon in done: " << _pos << endl;
        //  cout << "Buffer length: " << strlen(_buffer) << endl;
        //  cout<<"NOT DONE"<<endl;
        // if (t > 100)
        // {
        //     t=0;
        //     return true;
        // }
        // t++;
        return false;
    }

    // if pos>strlength, return t
    cout << "Passed 2 conditions." << endl;
    return false;
}
bool STokenizer::more() // true: there are more tokens
{
    return (!done());
}
STokenizer &operator>>(STokenizer &s, Token &t) // set a new string as the input string
{
    int state = 0;
    if (s.done()) // No more tokens
    {
        //  cout << "No more tokens" << endl;
        return s;
    }
    else
    {
        s.get_token(state, t);
    }
    // if(get_token())
    return s;
}
void STokenizer::set_string(char str[])
{
    strcpy(_buffer, str);
    _pos = 0;
}
int STokenizer::get_position()
{
    return _pos;
}
void STokenizer::make_table()
{
    init_table(_table);
    //
    // doubles:
    mark_fail(_table, 6);
    mark_success(_table, 7);
    mark_cell(1, _table, '.', 6);
    mark_cells(6, _table, DIGITS, 7);
    mark_cells(7, _table, DIGITS, 7);
    //

    mark_cells(0, _table, DIGITS, 1);
    mark_cells(0, _table, ALFA, 2);
    mark_cell(0, _table, ' ', TOKEN_SPACE);
    mark_cell(0, _table, '\t', TOKEN_SPACE);
    mark_cell(0, _table, '\n', TOKEN_SPACE);
    mark_cell(0, _table, '\0', TOKEN_SPACE);
    mark_cells(0, _table, OPERATORS, TOKEN_OPERATOR);
    mark_cells(0, _table, PUNC, TOKEN_PUNC);
    // mark_cells(0, _table, SPACES, TOKEN_SPACE);

    mark_cells(0, _table, PAREN, TOKEN_PAREN);
    mark_cells(1, _table, DIGITS, TOKEN_NUMBER);
    mark_cells(2, _table, ALFA, TOKEN_ALPHA);
    mark_cell(3, _table, ' ', TOKEN_SPACE);
    mark_cell(3, _table, '\t', TOKEN_SPACE);
    mark_cell(3, _table, '\n', TOKEN_SPACE);
    mark_cell(3, _table, '\0', TOKEN_SPACE);
    // mark_cell(3, _table,SPACES , TOKEN_SPACE);
    mark_cells(4, _table, OPERATORS, TOKEN_OPERATOR);
    mark_cells(5, _table, PUNC, TOKEN_PUNC);

    mark_success(_table, TOKEN_SPACE);
    mark_success(_table, TOKEN_NUMBER);
    mark_success(_table, TOKEN_ALPHA);
    mark_success(_table, TOKEN_SPACE);
    mark_success(_table, TOKEN_OPERATOR);
    mark_success(_table, TOKEN_PUNC);
    mark_success(_table, TOKEN_PAREN);

    // 5/29 handle double quote:
    mark_cell(0, _table, '\"', 8);
    mark_cells(8, _table, ALFA, 8);
    mark_cells(8, _table, SPACES, 8);
    mark_cells(8, _table, ".", 8);
    mark_cells(8, _table, PUNC, 8);
    mark_cells(8, _table, DIGITS, 8);
    mark_cells(8, _table, OPERATORS, 8);
    mark_cell(8, _table, '\\', 8);
    mark_cell(8, _table, '\"', 9); // 6/2 6:33 pm: added this to handle \"Sammuel L.\"
    mark_success(_table, 9);
    mark_cells(9, _table, "\"", TOKEN_NAME);
    //  mark_fail(_table, 8);
}
bool STokenizer::get_token(int &start_state, Token &t)
{
    string input(_buffer);
    //   cout << "After copying string : " << input << endl;
    if (_pos > input.size())
    {
        cout << "Input size <= position. Out of bound" << endl
             << "Position: " << _pos << endl;

        return false;
    }

    // bool tokenFound = false;
    bool success = false;
    int nextState = 0;
    int last_success_state = 0;
    int starting_pos = _pos;
    int Last_Success_State_pos = 0;
    int traveser_position = _pos;
    string tokenOutput = "";
    start_state = _table[start_state][input[traveser_position]];

    while (traveser_position <= input.size()) // traveser_position <= input.size() // && nextState != -1 // haven't handle cases where traverser reaches the end and finds no tokens yet
    {
        // start_state = _table[start_state][input[traveser_position]];
        nextState = _table[start_state][input[traveser_position + 1]];
        if (input[traveser_position + 1] == '\0')
        {
            nextState = -1;
        }

        /*cout << setw(20) << "Current State: " << start_state << endl
             << setw(20) << "Next State: " << nextState << endl;
             */

        /* if(input[traveser_position+1]=='\0')
         {
             nextState=-1;
         }
         */
        if (is_success(_table, start_state))
        {
            success = true;
            Last_Success_State_pos = traveser_position;
            last_success_state = _table[start_state][input[traveser_position]];
            // cout << setw(20) << "Success: " << success << " (0= unsuccessful , 1= successful)" << endl;
        }

        // cout
        //     << endl
        //cout << setw(20) << "Current Char: " << input[traveser_position] << endl;
        //     << setw(20) << "Current State: " << start_state << endl
        //     << setw(20) << "Next State: " << nextState << endl
        //     << setw(20) << "Position: " << _pos << endl
        //     //   << setw(20) << "Starting Position: " << starting_pos << endl
        //     << setw(20) << "Walker Position: " << traveser_position << endl
        //     << setw(20) << "Last Success Position: " << Last_Success_State_pos << endl
        //     << setw(20) << "Success: " << success << " (0= unsuccessful , 1= successful)" << endl
        //     << endl;

        if (success == true)
        {
            // currentCharacter = input[traveser_position];
            // tokenOutput += currentCharacter;

            // Last_Success_State_pos = traveser_position;
            if (nextState == -1 || input[traveser_position] == '\0')
            {
                // cout << "Enter nextState==-1" << endl;
                //  set input substring from pos to last_success_pos
                //  cout << "Substring from Position " << _pos << " to Position " << Last_Success_State_pos << endl;
                tokenOutput = input.substr(_pos, Last_Success_State_pos - _pos + 1);
                // cout << "Token: " << tokenOutput << endl;

                start_state = last_success_state;

                _pos = Last_Success_State_pos + 1;
                t.setString(tokenOutput);
                // cout << "Tokenoutput: " << tokenOutput << endl;
                // cout << "start_state: " << start_state << endl;
                if (tokenOutput == "(" || tokenOutput == ")")
                {
                    t.setType(TOKEN_PAREN);
                }
                else
                {
                    t.setType(start_state);
                }

                //  cout << "POS: " << _pos << endl;
                return true;
            }
        }
        if (start_state == -1 && success == false)
        {
            _pos++;
            //  cout << "POS: " << _pos << endl;
            return false;
        }
        start_state = nextState;
        traveser_position++;
    }
    return false;
}

// void STokenizer::get_buffer()
// {
//     cout << "Stk Buffer: " << _buffer << endl;
// }
/*
bool STokenizer::get_token(int &start_state, Token &t)
{
    if (_pos >= strlen(_buffer))
    {
        cout << "Position is out of bounds" << endl;
        return false;
    }
    // bool tokenFound = false;
    bool success = false;
    int state = start_state;
    int lastSuccessState=0;
    int nextState = 0;
    string tokenOutput = "";
    int traverser_position = _pos;
    while (traverser_position < strlen(_buffer) && state != -1) // haven't handle cases where traverser reaches the end and finds no tokens yet
    {
        // nextState = table[state][input[traveser_position]];
        char currentChar = _buffer[traverser_position];
        int column = (int)currentChar;
        nextState = _table[state][column];
        // cout << "_table[2]['a']" << _table[2]['a'] << endl;
        if (is_success(_table, nextState))
        {
            success = true;
            lastSuccessState=nextState;
        }

        cout << endl
             << "Current Char: " << currentChar << endl
             << "Current State: " << state << endl
             << "Next State: " << nextState << endl
             << "Starting Position: " << _pos << endl
             << "Walker Position: " << traverser_position << endl
             << "Success: " << success << " (0= unsuccessful , 1= successful)" << endl
             << endl;

        if (success == true)
        {
            // currentCharacter = input[traveser_position];
            // tokenOutput += currentCharacter;
            if (_buffer[traverser_position + 1] == '\0')
            {
                //   cout << "enter (NULL) condition" << endl;

                if (nextState == -1)
                {
                    // tokenOutput = input.substr(_pos, traverser_position);
                }
                else
                {
                    // tokenOutput = input.substr(_pos, traverser_position + 1);
                    tokenOutput += currentChar;
                }

                t.setString(tokenOutput);
                t.setType(state);
                _pos = traverser_position + 1;

                return true;
            }
            if (nextState == -1)
            {
                //  cout << "enter (nextState==-1) condition" << endl;
                // tokenOutput = input.substr(position, traverser_position);
                t.setString(tokenOutput);
                t.setType(state);
                _pos = traverser_position;

                return true;
            }
        }
        else if (success == false && nextState == -1)
        {
            _pos++;
            return false;
        }
        tokenOutput += currentChar;
        state = nextState;
        traverser_position++;
    }
    return false;
}
*/

int STokenizer::_table[MAX_ROWS][MAX_COLUMNS] = {};
