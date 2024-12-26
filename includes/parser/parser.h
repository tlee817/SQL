#ifndef PARSER_H
#define PARSER_H

#include "../../includes/tokenizer/constants.h"
#include "../../includes/table/typedefs.h"
#include "../../includes/tokenizer/state_machine_functions.h"
#include "../../includes/tokenizer/stokenize.h"

class Parser
{
public:
    Parser();
    Parser(char s[]);
    Parser(string s);
    // void print_lookup();
    void set_string(char s[]);
    bool get_parse_tree();    // sets ptree , returns true if ends at a success state , false otherwise
    int get_column(string s); // maps tokens to keyword constants like SELECT , FROM or symbols
    void make_table();        // Init. table with all -1
    bool fail();              // Return if the tree is successfully parsed
    mmap_ss parse_tree();   
    void build_keyword_list();

private:
    bool flag;
    mmap_ss _parsed_tree;
    Queue<string> _input_queue;
    char _buffer[MAX_BUFFER];
    map_sl _keyword_list;
    static int _table[MAX_ROWS][MAX_COLUMNS];
};

enum KEYWORD
{
    ZERO,
    SELECT,
    INSERT,
    MAKE,
    TABLE,
    STAR,
    WHERE,
    FROM,
    INTO,
    FIELDS,
    VALUES,
    SYM,
    COMMA
};

#endif