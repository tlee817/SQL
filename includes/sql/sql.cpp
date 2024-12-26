#include "../../includes/sql/sql.h"
SQL::SQL()
{
}
Table SQL::command(string command)
{

    /*
    Function Overview:
    -> Parser will parse a tree.
    -> Once a parsed tree is obtained , perform actions with the given parsed tree.
    Note: A map of table is implemented to avoid reindexing every time.
          For instance, if the table name is not in the map , SQL will open the table , reindex it , then store in the map of table.
          And reindexing is not needed when select is performed again in SQL.
    */
    valid_command = true;
    char s[command.size() + 1];
    strcpy(s, command.c_str());
    Parser p(s);

    try
    {
        mmap_ss parsed_tree = p.parse_tree();
        if (parsed_tree["command"][0] == "select")
        {

            bool condition_exists = (parsed_tree.contains("where") && parsed_tree["where"][0] == "yes");

            if (_table_list.contains(parsed_tree["table_name"][0]))
            {
                // cout << "map contains key" << endl;
                _table = _table_list[parsed_tree["table_name"][0]];
            }
            else
            {
                // cout << "map does not contains key" << endl;
                _table_list.insert(parsed_tree["table_name"][0], Table(parsed_tree["table_name"][0]));
                _table = _table_list[parsed_tree["table_name"][0]];
            }

            if (parsed_tree["fields"][0] == "*")
            {
                //   cout << "table name: " << parsed_tree["table_name"][0] << endl;
                if (condition_exists)
                {
                    // cout << "fields* && condition_exists" << endl;
                    return _table.select(_table.get_fields(), parsed_tree["condition"]);
                }
                else // if(!condition_exists)
                {
                    // Select All:
                    return _table.select(_table.get_fields());
                }
            }
            else // parsed_tree["fields"][0] != "*"
            {
                if (condition_exists)
                {
                    //  cout << "fields!=* && condition_exists" << endl;
                    return _table.select(parsed_tree["fields"], parsed_tree["condition"]);
                }
                else // if(!condition_exists)
                {
                    // cout << "fields!=* && !condition_exists" << endl;
                    return _table.select(parsed_tree["fields"]);
                }
            }
        }
        else if (parsed_tree["command"][0] == "make")
        {
            // Sample Input:
            //  /*00*/ "make table employee fields  last,       first,         dep,      salary, year",
            // v2:
            _table_list.insert(parsed_tree["table_name"][0], Table(parsed_tree["table_name"][0], parsed_tree["col"]));
            return _table_list[parsed_tree["table_name"][0]];
        }
        else if (parsed_tree["command"][0] == "insert")
        {
            // Sample Input:
            //   /*03*/ "insert into employee values Johnson,    Jack,          HR,       150000, 2014",
            //   /*04*/ "insert into employee values Johnson,    \"Jimmy\",     Chemistry,140000, 2018",
            if (_table_list.contains(parsed_tree["table_name"][0]))
            {
                _table_list[parsed_tree["table_name"][0]].insert_into(parsed_tree["values"]);
                return _table_list[parsed_tree["table_name"][0]];
            }
            else
            {
                _table_list.insert(parsed_tree["table_name"][0], Table(parsed_tree["table_name"][0]));
                return _table_list[parsed_tree["table_name"][0]];
            }
        }
        else
        {
            cout << "IN SQL::command , YOU SHOULD NOT BE HERE." << endl;
        }
    }
    catch (runtime_error &e)
    {
        valid_command = false;
        cout << "Error caught in SQL::command() ---> " << e.what() << endl;
    }
    // cout << "here is the parsed_tree: " << parsed_tree << endl;
    // cout<<"here"<<endl;
    return Table();
}
vectorlong SQL::select_recnos()
{
    return _table.select_recnos();
}

bool SQL::is_valid()
{
    return valid_command;
}

void SQL::run()
{
    string choice = "y";
    SQL sql;
    string command;
    Table t_select;
    while (choice == "y")
    {
        // /*00*/ "make table employee fields  last,       first,         dep,      salary, year",
        // /*01*/ "insert into employee values Blow,       Joe,           CS,       100000, 2018",
        // /*02*/ "insert into employee values Blow,       JoAnn,         Physics,  200000, 2016",
        // /*03*/ "insert into employee values Johnson,    Jack,          HR,       150000, 2014",
        // /*04*/ "insert into employee values Johnson,    \"Jimmy\",     Chemistry,140000, 2018",

        // /*05*/ "make table student fields  fname,          lname,    major,    age",
        // /*06*/ "insert into student values Flo,            Yao, 	Art, 	20",
        // /*07*/ "insert into student values Bo, 		     Yang, 	CS, 		28",
        // /*08*/ "insert into student values \"Sammuel L.\", Jackson, 	CS, 		40",
        // /*09*/ "insert into student values \"Billy\",	     Jackson, 	Math,	27",
        // /*10*/ "insert into student values \"Mary Ann\",   Davis,	Math,	30",

        // /*11*/ "select * from employee",
        // /*12*/ "select last, first, age from employee",
        // /*13*/ "select last from employee",
        // /*14*/ "select * from employee where last = Johnson",
        // /*15*/ "select * from employee where last=Blow and major=\"JoAnn\"",

        // /*16*/ "select * from student",
        // /*17*/ "select * from student where ((major=CS or major=Art))",
        // /*18*/ "select * from student where lname>J",
        // /*19*/ "select * from student where lname>J and (major=CS or major=Art)"
        cout << "-------------------------------------------------------------------------------" << endl;
        cout << "Enter your command: " << endl;
        getline(cin, command);
        cout << "command entered : " << command << endl;
        t_select = sql.command(command);
        cout << endl
             << "SQL: Currently tracking these tables: " << endl
             << "-------------------------------------" << endl;
        sql.print_table_tracked();
        cout << "-------------------------------------" << endl;
        if (sql.is_valid())
        {
            cout << t_select << endl
                 << "Record number selected: " << sql.select_recnos() << endl;
        }

        cout << "Do you wish to keep going? (yes = 'y' , no = input any keys)" << endl;
        getline(cin, choice);
        cout << endl
             << "-------------------------------------------------------------------------------" << endl;
    }
    cout << "Program ends" << endl;
}

void SQL::print_table_tracked()
{
    _table_list.print_key();
}

void SQL::batch()
{
    vectorstr command_list =
        {
            // 0. valid command:
            "select lname, fname, major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson",
            // 1. Expected comma:
            "select lname fname, major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson",
            // 2. Expected: field name
            "select lname, , major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson",
            // 3. Expected from:
            "select lname, fname, major student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson",
            // 4. Expected table name:
            "select lname, fname, major from where ((lname=Yang or major=CS) and age<23 )or lname=Jackson",
            // 5. Expected condition:
            "select lname, fname, major from student where",
            // 6. Missing left paren:
            "select lname, fname, major from student where (lname=Yang or major=CS) and age<23 )or lname=Jackson",
            // 7. Missing right paren:
            "select lname, fname, major from student where ((lname=Yang or major=CS and age<23 )or lname=Jackson",
            // 8. Missing condition value:
            "select lname, fname, major from student where ((lname= or major=CS) and age<23 )or lname=Jackson",
            // 9. Valid command (same as 1):
            "select lname, fname, major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson",
            // 10. Missing logical operator:
            "select lname, fname, major from student where ((lname=Yang major=CS) and age<23 )or lname=Jackson",
            // 11. Missing condition value after "or":
            "select lname, fname, major from student where ((lname=Yang or ) and age<23 )or lname=Jackson",
            // 12. Missing condition after "or":
            "select lname, fname, major from student where ((lname=Yang or major=CS) and age<23 )or ",
            // 13. Valid command:
            "select lname, fname, major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson"};

    SQL sql;
    string command;
    Table t_select;
    for (int i = 0; i < command_list.size(); i++)
    {
        // cout << endl
        //      << "-------------------------------------------------------------------------------" << endl;
        command = command_list[i];
        cout << i << ": " << command << endl;
        t_select = sql.command(command);
        cout << endl
             << "SQL: Currently tracking these tables: " << endl
             << "-------------------------------------" << endl;
        sql.print_table_tracked();
        cout << "-------------------------------------" << endl;
        if (sql.is_valid())
        {
            cout << t_select << endl
                 << "Record number selected: " << sql.select_recnos() << endl;
        }
     cout << endl;
        //      << "-------------------------------------------------------------------------------" << endl;
    }
}