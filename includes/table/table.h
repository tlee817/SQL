#ifndef TABLE_H
#define TABLE_H
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <iomanip>
#include <vector>
#include "../../includes/table/typedefs.h"

using namespace std;

class Table
{
public:
    //*** MUST DOUBLE CHECK: these bc I got these from the grader errors ***
    Table();                                            // create an empty table
    Table(const string &name);                          // retrieve data from existing file and create a table with it
    Table(const string &name, const vectorstr &fields); // create an empty table with given field(s)

    void insert_into(const vectorstr &row);                                                                                 // insert a row into a table and its indices
    Table select(const vectorstr &field_names, const string &targeted_field, const string &condition, const string &entry); // Given a condition , return a table
    Table select(const vectorstr &field_names, Queue<Token *> post);                                                        // Given a an expression in postfix , return a table
    Table select(const vectorstr &field_names, const vectorstr &infix_condition);                                           // Given a an expression in infix , return a table
    Table select(const vectorstr &fields);                                                                                  // Given a vector of field names , return everything in the table with only the selected fields
    Table select_all();                                                                                                     // Returning everything in the table
    vectorlong select_recnos();                                                                                             // return the selected record numbers in the previous table
    friend ostream &operator<<(ostream &outs, const Table &t);

    string get_table_name(); // Getter for table name
    vectorstr get_fields();  // Getter for field names

private:
    vectorstr get_row_with_recno(const long &recno);                                                                 // Helper function: Given a recno , get the row.  ex. recno 1 --> return < Joe , Gomez , 19 , CS >
    void set_fields(vectorstr fields);                                                                               // Given a vector of field name , set the fields for the table object
    void reindex();                                                                                                  // Reindex the indices of table when retreiving data from an old table
    Table create_table_with_recno(string new_table_name, vectorstr fields, vectorlong recno_Vec);                    // Helper function: Given a vector of field names and record number , return a new table
    vectorlong get_recno_with_condition(const string &targeted_field, const string &condition, const string &entry); // Given an expression , return a vector of record number
    vectorlong get_recno_with_rpn(Queue<Token *> post);                                                              // Given a postfix expression , return a vector of record number using RPN algorithm
    Queue<Token *> infix_to_postfix(vectorstr infix);                                                                // Helper function: Given a vector of string in an infix format , return it in a Queue of Token pointer type using Shunting Yard algorithm

    // Private Member
    int size;                   // unused for now
    vectorlong selected_recnos; // Selected Recnos.
    FileRecord bucket;          // Temp bucket to store data
    vectorstr field_names;      // Field names: Fname , Lname , Age
    string table_name;          // "tabename"
    map_sl field_map;           // map of fields {fname,0} , {lname,1} , {age,2}
    vector<mmap_sl> indices;    // multimap of recno {fname,recno vector} , {lname,recno vector} , {age,recno vector}
    string filename;            //"table.bin"
    string field_name_file;     //"tablename_field.bin"
    static long serial_Number;  //
    long last_recno;            // Last recno written
};

#endif