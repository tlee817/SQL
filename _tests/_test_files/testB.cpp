#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
using namespace std;
#include "../../includes/sql/sql.h"
#include "../../includes/table/table.h"
#include "../../includes/table/typedefs.h"
bool test_stub(bool debug = false)
{
  if (debug)
  {
    cout << "testB:: test-sub() entering test_sub" << endl;
  }
  return true;
}

TEST(TEST_STUB, TestStub)
{

  // EXPECT_EQ(0, <your individual test functions are called here>);

  EXPECT_EQ(1, test_stub(false));
}
Table make_table()
{
  vectorstr fields = {"fname", "lname", "age", "grade", "city"};
  Table t("student", fields);
  vectorstr row;
  row = {"Joe", "Gomez", "20", "A", "LA"};
  t.insert_into(row);
  row = {"Karen", "Orozco", "21", "B", "SF"};
  t.insert_into(row);
  row = {"Flo", "Yao", "29", "A", "SD"};
  t.insert_into(row);
  row = {"Jack", "Yao", "19", "C", "LA"};
  t.insert_into(row);
  row = {"Flo", "Jackson", "20", "B", "SF"};
  t.insert_into(row);
  row = {"Flo", "Gomez", "20", "A", "SD"};
  t.insert_into(row);
  row = {"Karen", "Jackson", "15", "B", "LA"};
  t.insert_into(row);
  row = {"Alex", "Smith", "22", "C", "SF"};
  t.insert_into(row);
  row = {"Mary", "Johnson", "25", "B", "SD"};
  t.insert_into(row);
  row = {"Chris", "Lee", "18", "A", "LA"};
  t.insert_into(row);
  row = {"Pat", "Kim", "23", "C", "SF"};
  t.insert_into(row);
  row = {"Taylor", "Brown", "26", "A", "SD"};
  t.insert_into(row);
  row = {"Jordan", "Davis", "24", "B", "LA"};
  t.insert_into(row);
  row = {"Casey", "Miller", "27", "C", "SF"};
  t.insert_into(row);
  row = {"Alex", "Wilson", "28", "A", "SD"};
  t.insert_into(row);
  row = {"Jamie", "Moore", "19", "B", "LA"};
  t.insert_into(row);
  row = {"Morgan", "Taylor", "21", "C", "SF"};
  t.insert_into(row);
  row = {"Dakota", "Anderson", "22", "A", "SD"};
  t.insert_into(row);
  row = {"Reese", "Thomas", "20", "B", "LA"};
  t.insert_into(row);
  row = {"Jordan", "Jackson", "23", "C", "SF"};
  t.insert_into(row);
  return t;
}

const vector<string> command_list = {

    /*00*/ "make table employee fields  last,       first,         dep,      salary, year",
    /*01*/ "insert into employee values Blow,       Joe,           CS,       100000, 2018",
    /*02*/ "insert into employee values Blow,       JoAnn,         Physics,  200000, 2016",
    /*03*/ "insert into employee values Johnson,    Jack,          HR,       150000, 2014",
    /*04*/ "insert into employee values Johnson,    \"Jimmy\",     Chemistry,140000, 2018",

    /*05*/ "make table student fields  fname,          lname,    major,    age",
    /*06*/ "insert into student values Flo,            Yao, 	Art, 	20",
    /*07*/ "insert into student values Bo, 		     Yang, 	CS, 		28",
    /*08*/ "insert into student values \"Sammuel L.\", Jackson, 	CS, 		40",
    /*09*/ "insert into student values \"Billy\",	     Jackson, 	Math,	27",
    /*10*/ "insert into student values \"Mary Ann\",   Davis,	Math,	30",

    /*11*/ "select * from employee",
    /*12*/ "select last, first, age from employee",
    /*13*/ "select last from employee",
    /*14*/ "select * from employee where last = Johnson",
    /*15*/ "select * from employee where last=Blow and major=\"JoAnn\"",
    /*16*/ "select * from student",
    /*17*/ "select * from student where (major=CS or major=Art)",
    /*18*/ "select * from student where lname>J",
    /*19*/ "select * from student where lname>J and (major=CS or major=Art)"

};
void test_stk()
{
  Parser p("insert into student values \"Sammuel L.\", Jackson, 	CS, 		40");
  cout << p.parse_tree();
}
void test_create_table()
{
  SQL sql;
  Table t;
  cout << ">" << command_list[0] << endl;
  sql.command(command_list[0]);
  cout << "basic_test: table created." << endl
       << endl;

  for (int i = 0; i < 11; i++)
  {
    cout << ">" << command_list[i] << endl;
    sql.command(command_list[i]);
  }
  // cout << "here is the table after insert: " << sql._table << endl;
  // for (int i = 5; i < 13; i++)
  // {
  //   cout << ">" << command_list[i] << endl;
  //   sql.command(command_list[i]);
  //   cout << sql.select_recnos();
  // }
  cout << sql.command(command_list[19]);
  cout << "Selected recnos: " << sql.select_recnos() << endl;
  // cout << "here is the table after insert: " << sql._table << endl;

  // sql.command(command_list[11]);
  // Table t_fileds = Table("employee");
  //  vectorstr str = extract_string_from_file("employee.bin");
  //  cout << "str: " << str << endl;
}

void test_select_with_field_vectorstr()
{
  // Table t("employee");
  // cout << t << endl;
  // Table t("student");
  // vectorstr fields = {"fname", "major"};
  // Table t_select_field = t.select(fields);
  // cout << "table after selecting fields: " << t_select_field << endl;
  // cout << "recno selected: " << t.select_recnos() << endl;

  // fields = {"fname", "lname", "major"};
  // Table t_select_field2 = t.select(fields);
  // cout << "table after selecting all: " << t_select_field2 << endl;
  // cout << "recno selected: " << t.select_recnos() << endl;
  // cout << str;
}

void test_table()
{
  Table t("employee");
  cout << "Here is the table :" << t << endl;
  cout << "Indice 2:" << endl;
  // t.indices[4].print_lookup();
}

void test_crash()
{
  // STokenizer stk("insert into student values \"Sammuel L,123a@41 a  .\", Jackson, 	CS, 		40");
  string str = "hello\" Sam H. \"28";
  // string str =""
  char temp[str.size() + 1];
  strcpy(temp, str.c_str());
  STokenizer stk(temp);
  Token t;
  stk >> t;
  while (stk.more())
  {
    cout << endl;
    cout << t.get_string();
    cout << endl;
    stk >> t;
  }
  // cout << endl;
  // cout << t.get_string();
  // cout << endl;
  // stk >> t;
  // cout << endl;
  // cout << t.get_string();
  // cout << endl;
  // cout << t.get_token() << endl;
}

void test_shuntingyard()
{
  Table t = make_table();
  cout << "Here is the original table: " << endl
       << t << endl;
  // vectorstr condition = {"(", "age", "<", "17", "or", "age", ">", "20", ")", "and", "(", "lname", "=", "Jackson", "or", "fname", "=", "Flo", ")", "and", "city", "=", "SF"};
  // vectorstr condition = {"Fname", "=", "Flo", "or", "age", ">", "27", "and", "city", "=", "LA"};
  //(lname>J and (major=CS or major=Art))
  // vectorstr condition = {"(", "lname", ">", "J", "and", "(", "major", "=", "CS", "or", "major", "=", "Art", ")", ")"};
  // vectorstr condition = {"(", "(", "(", "age", "<", "18", "or", "age", ">", "25", ")", "and", "(", "city", "=", "New York", "or", "city", "=", "Los Angeles", ")", ")", "and", "(", "grade", "=", "A", "or", "(", "grade", "=", "B", "and", "(", "lname", "=", "Smith", "or", "fname", "=", "John", ")", ")", ")", ")"};
  // vectorstr condition={"age", "<", "18", "or", "age", ">", "25", "and", "city", "=", "New York"};

  // vectorstr condition = {
  //     "(", "(", "age", "<", "20", "or", "age", ">", "25", ")", "and",
  //     "(", "city", "=", "SF", "or", "city", "=", "LA", ")", ")", "and",
  //     "(", "grade", "=", "A", "or", "grade", "=", "B", ")"};

  // Queue<Token *> post = t.infix_to_postfix(condition);
  // cout << "post: " << post << endl;
  // cout << "here is the selected table:" << endl;
  // Table t_select = t.select(t.get_fields(), post);
  // cout << "here is t_select:" << endl
  //      << t_select << endl
  //      << "selected_recno: " << t.select_recnos() << endl;
  // t_select.indices[0].print_lookup();

  SQL s;
  cout << s.command("select * from student where ( ( age < 20 or age > 25 ) and ( city = SF or city = LA )) and (grade = A or grade = B)");

  // s.run();
}

void test_interactive()
{
  SQL s;
  s.run();
}

void test_string()
{
  // cout << "Enter your command: " << endl;
  // getline(cin, command);
  // cout << "command entered : " << command << endl;
  string temp = "lee\\";
  cout << "temp: " << temp << endl;
  for (int i = 0; i < temp.size(); i++)
  {
    if (temp[i] == '\\')
    {
      temp.erase(i);
    }
  }
  cout << "temp: " << temp << endl;
}

void test_error_handling()
{
  SQL sql;
  Table t_select;
  // Valid command:
  // string command = "select last, first, major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson";
  // Invalid commands:
  //--------------------------------------------------------------------------------------------------------------------------------------
  // Imbalace Parenthesis (COMPLETE)
  // string command = "select last, first, major from student where (lname=Yang or major=CS) and age<23 )or lname=Jackson";
  // string command = "select last, first, major from student where ((lname=Yang or major=CS and age<23 )or lname=Jackson";
  //--------------------------------------------------------------------------------------------------------------------------------------
  // Missing comma (COMPLETE)
  // string command = "select last first, major from student where major = CS";
  //--------------------------------------------------------------------------------------------------------------------------------------
  // Missing field names (COMPLETE)
  // string command="select last, , major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson";
  //--------------------------------------------------------------------------------------------------------------------------------------
  // Missing FROM (COMPLETE)
  // string command = "select last, first, major  student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson";
  //--------------------------------------------------------------------------------------------------------------------------------------
  // Missing Table Name (COMPLETE)
  // string command = "select last, first, major from  where ((lname=Yang or major=CS) and age<23 )or lname=Jackson";
  //--------------------------------------------------------------------------------------------------------------------------------------
  // Missing Condition
  // string command = "select last, first, major from student where ";
  //--------------------------------------------------------------------------------------------------------------------------------------
  // OTHER TESTING:
  // string command="select last, first, major from student where ((lname= or major=CS) and age<23 )or lname=Jackson";
  //  string command="select last, first, major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson";  // <--Valid
  // string command="select last, first, major from student where ((lname=Yang  major=CS) and age<23 )or lname=Jackson";
  // string command = "select last, first, major from student where ((lname=Yang or ) and age<23 )or lname=Jackson";
  // string command = "select last, first, major from student where ((lname=Yang or major=CS) and age<23 )or ";
  // string command = "select last, first, major from student where ((lname=Yang or major=CS) and age<23 )or lname=Jackson";  // <--Valid
  string command = "";
  cout << "Command: " << command << endl
       << endl;
  t_select = sql.command(command);
  if (sql.is_valid())
  {
    cout << t_select << endl
         << "Record number selected: " << sql.select_recnos() << endl;
  }
}

void test_batch()
{
  SQL sql;
  sql.batch();
}
int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  std::cout << "\n\n----------running testB.cpp---------\n\n"
            << std::endl;
  // test_stk();
  // test_create_table();
  // test_table();
  //  test_select_with_field_vectorstr();
  // test_crash();
  // test_shuntingyard();
  // test_string();
  // test_interactive();
  // test_error_handling();
  test_batch();
  return RUN_ALL_TESTS();
}
