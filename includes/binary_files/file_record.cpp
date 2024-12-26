
#include "../../includes/binary_files/file_record.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <iomanip>
#include <vector>

long FileRecord::write(fstream &outs)
{
    // r.write(f); //take the Record r and write it into file f and return the record number of this Record

    // write to the end of the file.
    outs.seekg(0, outs.end);
    long pos = outs.tellp(); // retrieves the current position of the file pointer
    // outs.write(&record[0], sizeof(record));
    outs.write(&_record[0][0], sizeof(_record));

    return pos / sizeof(_record); // record number
}

long FileRecord::read(fstream &ins, long recno)
{
    // returns the number of bytes read.
    //     r.read(f, 6);
    //     cout<<r<<endl;
    long pos = recno * sizeof(_record);
    ins.seekg(pos, ios_base::beg);

    // ins.read(&_record[0], sizeof(_record))
    ins.read(&_record[0][0], sizeof(_record));
    // don't you want to mark the end of  the cstring with null?
    //_record[] => [zero'\0'trash trash trash trash]
    // don't need the null character, but for those of us with OCD and PTSD:
    //  _record[ins.gcount()] = '\0';
    return ins.gcount();
}

ostream &operator<<(ostream &outs, const FileRecord &r)
{
    //  outs << "row used: " << r.row_used << endl;

    // Add a private member variable?
    // for (int i = 0; i < r.row_used; i++)
    // {
    //     outs << setw(25) << r._record[i];
    // }
    for (int i = 0; i < r.MAX + 1 && r._record[i][0] != '\0'; i++)
    {
        outs << setw(25) << r._record[i];
    }
    //  outs << endl;
    return outs;
}

// //----------------------------------------------------------------------------
// //                      F I L E   F U N C T I O N S
// //----------------------------------------------------------------------------

//[    |    |     |    |    |     |]

bool file_exists(const char filename[])
{
    const bool debug = false;
    fstream ff;
    ff.open(filename,
            std::fstream::in | std::fstream::binary);
    if (ff.fail())
    {
        if (debug)
            cout << "file_exists(): File does NOT exist: " << filename << endl;
        return false;
    }
    if (debug)
        cout << "file_exists(): File DOES exist: " << filename << endl;
    ff.close();
    return true;
}

void open_fileRW(fstream &f, const char filename[]) // throw(char *)
{
    const bool debug = false;
    // opening a nonexistent file for in|out|app causes a fail()
    //   so, if the file does not exist, create it by openning it for
    //   output:
    if (!file_exists(filename))
    {
        // create the file
        f.open(filename, std::fstream::out | std::fstream::binary);
        if (f.fail())
        {
            cout << "file open (RW) failed: with out|" << filename << "]" << endl;
            throw("file RW failed  ");
        }
        else
        {
            if (debug)
                cout << "open_fileRW: file created successfully: " << filename << endl;
        }
    }
    else
    {
        f.open(filename,
               std::fstream::in | std::fstream::out | std::fstream::binary);
        if (f.fail())
        {
            cout << "file open (RW) failed. [" << filename << "]" << endl;
            throw("file failed to open.");
        }
    }
}

void open_fileW(fstream &f, const char filename[])
{
    f.open(filename,
           std::fstream::out | std::fstream::binary);
    if (f.fail())
    {
        cout << "file open failed: " << filename << endl;
        throw("file failed to open.");
    }
}

vector<string> extract_string_from_file(const string &filename)
{
    // After extracting from file: <[ Joe ][ Gomez ][ 20 ][ Karen ][ Orozco ][ 21 ]>
    // SUPER IMPORTANT!!!!
    // Seperate to insert into indices: <[ Joe ][ Gomez ][ 20 ]>  <[ Karen ][ Orozco ][ 21 ]>
    //***Rememeber to store into a vectorstr before inserting to indices***

    vector<string> temp;
    fstream f;
    open_fileRW(f, filename.c_str());
    FileRecord r;
    long recno = 0;
    // for (int i = 0; i < 3; i++)
    for (int i = 0; r.read(f, i) > 0; i++)
    {
        for (int j = 0; r._record[j][0] != '\0'; j++)
        {
            // cout << "r._record[i]: " << r._record[i] << endl;
            temp.push_back(r._record[j]);
        }
    }
    f.close();
    return temp;
}