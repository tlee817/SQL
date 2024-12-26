#ifndef STATE_MACHINE_FUNCTIONS_H
#define STATE_MACHINE_FUNCTIONS_H
#include <iomanip>

#include "../../includes/tokenizer/state_machine_functions.h"

// Fill all cells of the array with -1
void init_table(int _table[][MAX_COLUMNS])
{
    for (int i = 0; i < MAX_ROWS; ++i)
    {
        for (int j = 0; j < MAX_COLUMNS; ++j)
        {
            _table[i][j] = -1;
        }
    }
    /*
    _table[0][0] = 0; // state 0 success
    _table[1][0] = 1; // state 1 success
    _table[2][0] = 0;
    _table[3][0] = 1;
    _table[0]['a'] = 1;
    _table[0]['b'] = 2;
    _table[1]['a'] = 1;
    _table[1]['b'] = 2;
    _table[2]['a'] = 3;
    _table[2]['b'] = -1;
    _table[3]['a'] = 3;
    _table[3]['b'] = -1;
    */
}

// Mark this state (row) with a 1 (success)
void mark_success(int _table[][MAX_COLUMNS], int state)
{
    _table[state][0] = 1;
}

// Mark this state (row) with a 0 (fail)
void mark_fail(int _table[][MAX_COLUMNS], int state)
{
    _table[state][0] = 0;
}

// true if state is a success state
bool is_success(int _table[][MAX_COLUMNS], int state)
{
    if (_table[state][0] == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Mark a range of cells in the array.
void mark_cells(int row, int _table[][MAX_COLUMNS], int from, int to, int state)
{
    for (int i = from; i < to; i++)
    {
        _table[row][i] = state;
    }
}

// Mark columns represented by the string columns[] for this row
void mark_cells(int row, int _table[][MAX_COLUMNS], const char columns[], int state)
{

    for (int i = 0; columns[i] != '\0'; i++)
    {
        int col = static_cast<unsigned char>(columns[i]);
        _table[row][col] = state;
        // cout << "Marked " << setw(10) << " row : " << row << setw(10) << " column: " << col << setw(25) << "Table[row][col]: " << _table[row][col] << endl;
    }
}

// Mark this row and column
void mark_cell(int row, int table[][MAX_COLUMNS], int column, int state)
{
    table[row][column] = state;
}

// This can realistically be used on a small table
void print_table(int _table[][MAX_COLUMNS])
{
    for (int i = 0; i < MAX_ROWS; ++i)
    {
        for (int j = 0; j < MAX_COLUMNS; ++j)
        {
            cout << _table[i][j] << " ";
        }
        cout << "\n";
    }
}

// show string s and mark this position on the string:
// hello world   pos: 7
//        ^
void show_string(char s[], int _pos)
{
    cout << s << endl;
    for (int i = 0; i < _pos; i++)
    {
        cout << " ";
    }
    cout << "^" << endl;
}

#endif