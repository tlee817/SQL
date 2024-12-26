#include "../../includes/parser/parser.h"
#include <string>

Parser::Parser()
{
    build_keyword_list();
    make_table();
    flag = false;
}
Parser::Parser(string s)
{
    build_keyword_list();
    flag = false;
    char str[s.size() + 1];
    strcpy(str, s.c_str());
    // cout << "In parser CTOR , setting string" << endl;
    set_string(str);
    make_table();
}

Parser::Parser(char s[])
{
    build_keyword_list();
    flag = false;
    set_string(s);
    make_table();
}
mmap_ss Parser::parse_tree()
{
    flag = get_parse_tree();
    return _parsed_tree;
}
void Parser::set_string(char s[]) // * Test again in testB -> test_tokenize() if needed *
{
    STokenizer stk(s);
    Token t;
    stk >> t;
    while (stk.more())
    {
        // cout << setw(15) << t.type_string() << setw(15) << t << setw(15) << t.type() << endl;
        string temp = t.get_string();
        if (t.type() == TOKEN_NAME) // Convert "Teresa Mae" -> Teresa Mae before pushing into the queue
        {
            //   cout << "Name: " << temp << endl;
            for (int i = 0; i < temp.size(); i++)
            {
                if (temp[i] == '\\')
                {
                    temp.erase(i + 1);
                }
            }
            temp.erase(temp.begin());
            temp.erase(temp.end() - 1);
            // cout << "pushing " << temp << " into input queue" << endl;
            _input_queue.push(temp);
        }
        else if (t.type() == TOKEN_ALPHA || t.type() == TOKEN_NUMBER || t.type() == TOKEN_OPERATOR || t.type() == TOKEN_PAREN || t.type() == TOKEN_PUNC) // Only push ALPHA , NUM , OPERATOR into the queue
        {
            _input_queue.push(temp);
        }
        // process token here...
        t = Token();
        stk >> t;
    }
    // cout << endl
    //      << "Printing queue: " << _input_queue << endl;
}
bool Parser::get_parse_tree() // sets ptree , returns true if ends at a success state , false otherwise
{
    _parsed_tree.clear();
    int state = 0, col = 0;
    while (!_input_queue.empty())
    {
        string queue_pop = _input_queue.pop();
        col = get_column(queue_pop);
        // cout << "queue_pop: " << queue_pop << endl;
        // cout << "col: " << col << endl;
        // cout << "state: " << state << endl;
        switch (state)
        {
        case 0: // Select , Insert , Make
            _parsed_tree.insert("command", queue_pop);
            state = _table[state][col];
            break;

        case 1: // FROM , INTO , SYM
            // if (col == FROM || col == INTO || col == SYM)
            if (col == STAR)
            {
                _parsed_tree.insert("fields", "*");
            }
            if (col == SYM)
            {
                _parsed_tree.insert("fields", queue_pop);
            }
            state = _table[state][col];
            break;
        case 2: // COMMA
            if (col == COMMA)
            {
                state = _table[state][col];
            }
            else if (col == FROM)
            {
                state = _table[state][col];
            }
            else
            {
                throw runtime_error("Parser : missing comma or from");
            }
            break;
        case 10: // Select Machine: Set table name
            if (col == SYM)
            {
                //  cout << "setting table name:" << endl;
                _parsed_tree.insert("table_name", queue_pop);
            }
            state = _table[state][col];
            break;
        case 11: // Check if there are conditions
            if (col == WHERE)
            {
                _parsed_tree.insert("where", "yes");
            }

            state = _table[state][col];
            break;
        case 12: // Setting conditions
            if (col == SYM)
            {
                _parsed_tree.insert("condition", queue_pop);
            }
            state = _table[state][col];
            break;
        case 13: // (SUCCESS STATE) -> End of Select Machine
            if (col == SYM)
            {
                _parsed_tree.insert("condition", queue_pop);
            }
            state = _table[state][col];
            break;
        case 20: // Insert Machine : Set Table name
            if (col == SYM)
            {
                _parsed_tree.insert("table_name", queue_pop);
            }
            state = _table[state][col];
            break;
        case 21: // Double Check if "values" needs to be init here.
            state = _table[state][col];
            break;
        case 22:
            if (col == SYM)
            {
                _parsed_tree.insert("values", queue_pop);
            }
            state = _table[state][col];
            break;
        case 23: // (SUCCESS STATE) -> End of Insert Machine
            if (col == SYM)
            {
                _parsed_tree.insert("values", queue_pop);
            }
            state = _table[state][col];
            break;

        case 30: // Make Table Machine: Set table name
            if (col == SYM)
            {
                _parsed_tree.insert("table_name", queue_pop);
            }
            state = _table[state][col];
            break;
        case 31: // Keyword: FIELDS
            state = _table[state][col];
            break;
        case 32:
            if (col == SYM)
            {
                _parsed_tree.insert("col", queue_pop);
            }
            state = _table[state][col];
            break;
        case 33: // (SUCCESS STATE) -> End of Make Table Machine
            if (col == SYM)
            {
                _parsed_tree.insert("col", queue_pop);
            }
            state = _table[state][col];
            break;
        default:
            //  cout << "In get_parse_tree() , switch statement , at default" << endl;
            state = _table[state][col];
            break;
        }
    }

    // cout << "state: " << state << endl;
    // cout << "is_success: " << is_success(_table, state) << endl;
    if (state == -1 || is_success(_table, state) == false)
    {
        // cout << "In get_parsed_tree() , invalid command , returning false..." << endl;
        throw runtime_error("Error Thrown in Parser : Invalid command entered");
    }
    else
    {
        //  cout << "In get_parsed_tree() , valid command , returning true..." << endl;
        return true;
    }
}
int Parser::get_column(string s) // maps tokens to keyword constants like SELECT , FROM or symbols
{
    if (_keyword_list.contains(s))
    {
        return _keyword_list[s];
    }
    return SYM;
}
void Parser::make_table()
{
    init_table(_table);
    // Command
    mark_cell(0, _table, SELECT, 1);
    mark_cell(0, _table, INSERT, 1);
    mark_cell(0, _table, MAKE, 1);

    // Select machine
    mark_cell(1, _table, STAR, 1); // select *
    mark_cell(1, _table, SYM, 2);  // select lname , fname
    mark_cell(1, _table, FROM, 10);
    // COMMMA
    mark_cell(2, _table, COMMA, 1);
    mark_cell(2, _table, FROM, 10); // select * from
    //
    mark_cell(10, _table, SYM, 11);   // select * from student (<- success state)
    mark_cell(11, _table, WHERE, 12); // select * from student where
    mark_cell(12, _table, SYM, 13);   // select * from student where age
    mark_cell(13, _table, SYM, 13);   // select * from student where age < 20 (<- success state)
                                      //
    mark_success(_table, 11);         // Select fname,lname from student
    mark_success(_table, 13);         // Select fname,lname from student where age > 20
                                      //
    // Insert machine    -->v2
    mark_cell(1, _table, INTO, 20);    // insert into
    mark_cell(20, _table, SYM, 21);    // insert into student
    mark_cell(21, _table, VALUES, 22); // insert into student values
    mark_cell(22, _table, SYM, 23);    // insert into student values age
    mark_cell(23, _table, SYM, 23);    // insert into student values Blow , Joan , Physics (<- success state)
    mark_cell(23, _table, COMMA, 23);  //
    mark_success(_table, 23);          // insert into student values Blow , Joan , Physics

    // Make Table machine
    mark_cell(1, _table, TABLE, 30);   // make table
    mark_cell(30, _table, SYM, 31);    // make table student
    mark_cell(31, _table, FIELDS, 32); // make table student fields
    mark_cell(32, _table, SYM, 33);    // make table student fields last
    mark_cell(33, _table, SYM, 33);    // make table student fields last , first , age , major , class  (<- success state)
    mark_cell(33, _table, COMMA, 33);
    //
    mark_success(_table, 33); // make table student fields last , first , age , major , class
}
bool Parser::fail()
{
    return (flag == false);
}
void Parser::build_keyword_list()
{
    // ZERO,
    // SELECT,
    // INSERT,
    // MAKE,
    // TABLE,
    // STAR,
    // WHERE,
    // FROM,
    // INTO,
    // TABLE,
    // FIELDS,
    // VALUES,
    // SYM  *** -> if the map does not contain any of the input , return SYM in get_col()

    _keyword_list.insert("select", SELECT);
    _keyword_list.insert("make", MAKE);
    _keyword_list.insert("table", TABLE);
    _keyword_list.insert("insert", INSERT);
    _keyword_list.insert("into", INTO);
    _keyword_list.insert("*", STAR);
    _keyword_list.insert("where", WHERE);
    _keyword_list.insert("from", FROM);
    _keyword_list.insert("fields", FIELDS);
    _keyword_list.insert("values", VALUES);
    _keyword_list.insert(",", COMMA);
}

int Parser::_table[MAX_ROWS][MAX_COLUMNS];