#ifndef FILE_RECORD_H
#define FILE_RECORD_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <string>
#include <vector>

// #include "../../includes/file_record.cpp"

using namespace std;

struct FileRecord
{
    // when you construct a Record, it's either empty or it contains a word
    FileRecord()
    {
        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < MAX + 1; j++)
            {
                _record[i][j] = '\0';
            }
        }
        // for (int i = 0; i < ROW; i++)
        // {
        //     //  _record[ROW][0] = '\0';
        //     _record[i][0] = '\0';
        // }
        recno = -1;
    }
    FileRecord(vector<string> v)
    {
        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < MAX + 1; j++)
            {
                _record[i][j] = '\0';
            }
        }
        for (int i = 0; i < v.size(); i++)
        {
            strncpy(_record[i], v[i].c_str(), MAX);
            // cout << "row_used++" << endl;
        }
    }
    FileRecord(char str[])
    {
        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < MAX + 1; j++)
            {
                _record[i][j] = '\0';
            }
        }
        strncpy(_record[0], str, MAX);
    }
    FileRecord(string s)
    {
        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < MAX + 1; j++)
            {
                _record[i][j] = '\0';
            }
        }
        strncpy(_record[0], s.c_str(), MAX);
    }

    long write(fstream &outs);           // returns the record number
    long read(fstream &ins, long recno); // returns the number of bytes read = MAX, or zero if read passed the end of file

    friend ostream &operator<<(ostream &outs, const FileRecord &r);

    static const int MAX = 100;
    // static const int ROW = 100;
    static const int ROW = 30;
    int recno;
    char _record[ROW][MAX + 1];
};

// //----------------------------------------------------------------------------
// //                      F I L E   F U N C T I O N S
// //----------------------------------------------------------------------------

//[    |    |     |    |    |     |]
//-------------------------------------------------

bool file_exists(const char filename[]);

void open_fileRW(fstream &f, const char filename[]); // throw(char *);

void open_fileW(fstream &f, const char filename[]);

vector<string> extract_string_from_file(const string &filename);

#endif