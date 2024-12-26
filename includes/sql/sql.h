#ifndef SQL_H
#define SQL_H
#include "../../includes/table/table.h"
#include "../../includes/parser/parser.h"
class SQL
{
public:
    SQL();                         // CTOR
    Table command(string command); // Given the command in string , perform actions by parsing through the command
    vectorlong select_recnos();    // Return the selected record number from the previous table
    void run();                    // Interactive function
    bool is_valid();               // Return if the input command is valid
    void batch();

private:
    void print_table_tracked();     // Helper Function: Print out table names that are in the table list
    Table _table;                   // Temp table object
    vectorlong _selected_recnos;    // History of selected record numbers
    Map<string, Table> _table_list; // Map of table (key: Table Name , value: Table) -> ex. ("stuendt", student Table object)
    bool valid_command;             // Boolean to check if the command is valid
};

#endif