#include "../../includes/table/table.h"
#include <algorithm>

long Table::serial_Number = 0;
Table::Table()
{
    serial_Number++;
    filename = "Unknown.bin";
    table_name = to_string(serial_Number) + "_" + "Unknown";
    last_recno = 0;
}
Table::Table(const string &name)
{
    serial_Number++;
    filename = name + ".bin";
    table_name = to_string(serial_Number) + "_" + name;
    size = 0;
    last_recno = 0;
    fstream f;

    field_name_file = name + "_field.bin";
    FileRecord temp;
    vectorstr fnames = extract_string_from_file(field_name_file);
    //  cout << "field names extracted from field name file : " << fnames << endl;
    //  cout << "field name:" << field_names << endl;
    //   open_fileW(f, field_name_file.c_str());
    open_fileRW(f, field_name_file.c_str());
    set_fields(fnames);
    f.close();

    reindex();
}

Table::Table(const string &name, const vectorstr &fields) //
{
    fstream f;
    // serial_Number++;
    filename = name + ".bin";
    field_name_file = name + "_field.bin";
    table_name = name;
    size = 0;
    last_recno = 0;
    open_fileW(f, filename.c_str());
    f.close();

    set_fields(fields);
    open_fileW(f, field_name_file.c_str());
    FileRecord temp(fields);
    temp.write(f);
    // reindex();
    f.close();
}
string Table::get_table_name()
{
    return table_name;
}

void Table::insert_into(const vectorstr &row)
{
    fstream f;
    open_fileRW(f, filename.c_str());
    FileRecord record(row);
    last_recno = record.write(f);
    for (int i = 0; i < field_names.size(); i++)
    {
        indices[i].insert(row[i], last_recno);
    }
    // cout << indices[1];
    // cout<<record;
}

vectorlong Table::select_recnos()
{
    return selected_recnos;
}

Table Table::select(const vectorstr &field_names, Queue<Token *> post)
{
    serial_Number++;
    string new_table_name = "Select_" + to_string(serial_Number);
    vectorlong recno_Vec = get_recno_with_rpn(post);

    return create_table_with_recno(new_table_name, field_names, recno_Vec);
}
Table Table::select_all()
{
    return select(get_fields());
}
Table Table::select(const vectorstr &fields, const string &targeted_field, const string &condition, const string &entry)
{
    fstream f;
    serial_Number++;
    selected_recnos.clear();
    Table temp("select_" + to_string(serial_Number) + table_name, fields);
    vectorlong targeted_recno = get_recno_with_condition(targeted_field, condition, entry);
    open_fileW(f, temp.filename.c_str());

    for (int i = 0; i < targeted_recno.size(); i++)
    {
        vectorstr tempStrVec = get_row_with_recno(targeted_recno[i]);
        vectorstr insertStrVec;
        for (int i = 0; i < fields.size(); i++)
        {
            insertStrVec.push_back(tempStrVec[field_map[fields[i]]]);
        }
        // cout << "insertStrVec: " << insertStrVec << endl;
        selected_recnos.push_back(targeted_recno[i]);
        //  cout << "tempStrVec[i] : " << tempStrVec << endl;
        temp.insert_into(insertStrVec);
    }
    // cout << "Recno_from_prev_table: " << temp.selected_recnos << endl;
    f.close();
    return temp;
}
Table Table::select(const vectorstr &field_names, const vectorstr &infix_condition)
{
    Queue<Token *> post = infix_to_postfix(infix_condition);
    return select(field_names, post);
}

Table Table::select(const vectorstr &fields)
{
    selected_recnos.clear();
    int s_recno = 0;
    fstream f;
    serial_Number++;
    vectorstr str = extract_string_from_file(filename);
    Table temp("select_fields_" + to_string(serial_Number) + table_name, fields);
    // cout << "str: " << str << endl;

    for (int i = 0; i < str.size(); i = i + field_names.size())
    {
        vectorstr row_Vec;
        vectorstr insert_Vec;
        for (int j = i; j < i + field_names.size(); j++)
        {
            row_Vec.push_back(str[j]);
        }
        // cout << "row_Vec : " << row_Vec << endl;
        for (int k = 0; k < fields.size(); k++)
        {
            insert_Vec.push_back(row_Vec[field_map[fields[k]]]);
        }
        // cout << "insert_Vec : " << insert_Vec << endl;
        temp.insert_into(insert_Vec);
        selected_recnos.push_back(s_recno);
        s_recno++;
    }
    // cout << temp << endl;
    //  cout << temp.indices[1] << endl;
    return temp;
}

vectorstr Table::get_row_with_recno(const long &recno) // Given the RecNo. , return a vector<string> of row
{
    vectorstr temp;
    fstream f;
    open_fileRW(f, filename.c_str());
    long byte = bucket.read(f, recno);
    // cout << "byte: " << byte << endl;
    for (int i = 0; i < field_names.size(); i++)
    {
        string value = "";
        // for (int j = 0; j < field_names.size() && bucket._record[i][0] != '\0'; j++)
        for (int j = 0; j < bucket.MAX && bucket._record[i][j] != '\0'; j++)
        {
            // cout << "bucket._record[i][j]: " << bucket._record[i][j] << endl;
            value += bucket._record[i][j];
        }
        // cout << "value: " << value << endl;
        temp.push_back(value);
    }
    f.close();
    return temp;
}
vectorlong Table::get_recno_with_rpn(Queue<Token *> post) // RPN
{
    Stack<Token *> stack;
    while (!post.empty())
    {
        Token *temp = post.pop();
        // if (temp->get_type() == LPAREN || temp->get_type() == RPAREN)
        // {
        //     throw runtime_error("Invalid Expression: LParen");
        // }
        if (temp->get_type() == TOKENSTR)
        {
            // cout << "Inside TOKENSTR:" << endl;
            // cout << "-> Token* temp is pushed to the stack. " << endl;
            stack.push(temp);
        }
        else if (temp->get_type() == RELATIONAL)
        {
            if (stack.size() < 2)
            {
                throw runtime_error("RPN: Invalid expression: Relational");
            }

            // cout << "Inside RELATIONAL: " << endl;
            Token *stack_pop_1 = stack.pop();
            Token *stack_pop_2 = stack.pop();
            // cout << "-> stack_pop_2 string: " << stack_pop_2->get_string() << endl;
            // cout << "-> temp string: " << temp->get_string() << endl;
            // cout << "-> stack_pop_1 string: " << stack_pop_1->get_string() << endl;

            vectorlong recno_vec = get_recno_with_condition(stack_pop_2->get_string(), temp->get_string(), stack_pop_1->get_string());

            //  cout << "-> recno_vec: " << recno_vec << endl;
            ResultSet *r = new ResultSet();
            r->set_recno_vector(recno_vec);
            //  cout << recno_vec << " | pushed into stack as ResultSet Token *" << endl;
            stack.push(r);
        }
        else if (temp->get_type() == LOGICAL)
        {
            if (stack.size() < 2)
            {
                throw runtime_error("Invalid expression: Logical");
            }
            //  cout << "Inside LOGICAL: " << endl;
            Token *v1 = stack.pop(); // Type: ResultSet ,static_cast<ResultSet *>
            Token *v2 = stack.pop(); // Type: ResultSet
            vectorlong recno_vec;
            if (temp->get_string() == "and" || temp->get_string() == "or")
            {
                recno_vec = static_cast<Logical *>(temp)->eval(static_cast<ResultSet *>(v1)->get_recno_vector(), static_cast<ResultSet *>(v2)->get_recno_vector());
            }

            ResultSet *r = new ResultSet();
            r->set_recno_vector(recno_vec);
            //    cout << recno_vec << " | pushed into stack as ResultSet Token *" << endl;
            stack.push(r);
        }
    }
    vector<long> result;
    // cout << "stack.size(): " << stack.size() << endl;
    // cout << "queue.empty(): " << post.empty() << endl;
    if (stack.size() == 1 && post.empty())
    {

        //    cout << "(stack.size() == 1 && queue.empty()): " << endl;
        Token *final_token = stack.pop();
        ResultSet *resultSetPtr = static_cast<ResultSet *>(final_token);
        // ResultSet *resultSetPtr = static_cast<ResultSet *>(stack.pop());
        result = resultSetPtr->get_recno_vector();
        //   cout << "Final Recno Vector: " << result;
        // removeDups(result);
        return result;
    }
    else
    {
        throw runtime_error("RPN: Invalid expression");
    }

    cout << "YOU SHOULD NOT BE HERE" << endl;
    return result;
}

Table Table::create_table_with_recno(string new_table_name, vectorstr fields, vectorlong recno_Vec) //,vectorstr fields // Given a vector of recnos. , create a new table with the vector of recnos.
{
    selected_recnos.clear();
    Table new_table(new_table_name, fields);

    for (int i = 0; i < recno_Vec.size(); i++)
    {
        vectorstr tempStrVec = get_row_with_recno(recno_Vec[i]);
        vectorstr insertStrVec;
        for (int j = 0; j < fields.size(); j++)
        {
            insertStrVec.push_back(tempStrVec[field_map[fields[j]]]);
        }
        //       cout << "insertStrVec: " << insertStrVec << endl;
        selected_recnos.push_back(recno_Vec[i]);
        //  cout << "tempStrVec[i] : " << tempStrVec << endl;
        new_table.insert_into(insertStrVec);
    }
    // cout<<"new table: "<<new_table<<endl;
    return new_table;
}

ostream &operator<<(ostream &outs, const Table &t)
{
    fstream f;
    outs << "Table name: " << t.table_name << ", Record: " << (t.last_recno) + 1 << endl
         << endl;
    outs << setw(20) << "record";
    for (int i = 0; i < t.field_names.size(); i++)
    {
        // outs << "t.field_names.size() = " << t.field_names.size() << endl;
        outs << setw(25) << t.field_names[i];
    }
    outs << endl;
    // outs << "last recno : " << t.last_recno << endl;
    open_fileRW(f, t.filename.c_str());
    FileRecord bucket;
    for (int i = 0; i <= t.last_recno; i++)
    {
        bucket.read(f, i);
        outs << setw(20) << i << setw(20) << bucket << endl;
    }
    f.close();
    return outs;
    // Table name: student, records: 7
    //                record                    fname                    lname                      age
    //                     0                      Joe                    Gomez
}

// private:
vectorstr Table::get_fields()
{
    return field_names;
}

void Table::set_fields(vectorstr fields)
{
    //{lname , fname , age}
    //{    0,     1,    2}
    // cout << "Inside set_field: " << fields.size() << endl;
    // indices.clear();
    // field_names.clear();
    for (int i = 0; i < fields.size(); i++)
    {
        field_names.push_back(fields[i]);
        indices.push_back(mmap_sl());
        field_map.insert(fields[i], i);
    }
}

void Table::reindex()
{
    fstream f;
    field_map = map_sl();
    for (int i = 0; i < field_names.size(); i++)
    {
        indices[i] = mmap_sl();
    }

    for (int i = 0; i < field_names.size(); i++)
    {
        //    cout << "field_names[i]: " << field_names[i] << " , i:" << i << endl;
        field_map.insert(field_names[i], i);
    }
    vector<string> file_data_Vec = extract_string_from_file(filename.c_str());
    // cout << "file_data_Vec: " << file_data_Vec << endl
    //      << "file_data_Vec.size(): " << file_data_Vec.size() << endl
    //      << "field_names.size(): " << field_names.size() << endl;
    open_fileW(f, filename.c_str());

    for (int i = 0; i < file_data_Vec.size(); i = i + field_names.size())
    {
        vector<string> single_data_Vec;
        // single_data_Vec.push_back(file_data_Vec[i]);
        // single_data_Vec.push_back(file_data_Vec[i + 1]);
        // single_data_Vec.push_back(file_data_Vec[i + 2]);
        for (int j = i; j < i + field_names.size(); j++)
        {
            single_data_Vec.push_back(file_data_Vec[j]);
        }
        insert_into(single_data_Vec); //***** last_recno is updated in the insert_into() function *****
        // cout << "single_data_Vec: " << single_data_Vec << endl
        //      << "file_data_Vec.size(): " << file_data_Vec.size() << endl;
    }

    f.close();
}

vectorlong Table::get_recno_with_condition(const string &targeted_field, const string &condition, const string &entry)
{
    vectorlong targeted_recno;
    if (condition == "=")
    {
        targeted_recno = indices[field_map[targeted_field]][entry];
    }
    else if (condition == ">")
    {
        for (mmap_sl::Iterator it = indices[field_map[targeted_field]].upper_bound(entry); it != indices[field_map[targeted_field]].end(); it++)
        {
            for (int i = 0; i < (*it).value_list.size(); i++)
            {
                targeted_recno.push_back((*it).value_list[i]);
            }
        }
        //  cout << "targeted_recno: " << targeted_recno << endl;
    }
    else if (condition == "<")
    {
        for (mmap_sl::Iterator it = indices[field_map[targeted_field]].begin(); it != indices[field_map[targeted_field]].lower_bound(entry); it++)
        {
            for (int i = 0; i < (*it).value_list.size(); i++)
            {
                targeted_recno.push_back((*it).value_list[i]);
            }
        }
    }
    else if (condition == ">=")
    {
        for (mmap_sl::Iterator it = indices[field_map[targeted_field]].lower_bound(entry); it != indices[field_map[targeted_field]].end(); it++)
        {
            for (int i = 0; i < (*it).value_list.size(); i++)
            {
                targeted_recno.push_back((*it).value_list[i]);
            }
        }
    }
    else if (condition == "<=")
    {
        for (mmap_sl::Iterator it = indices[field_map[targeted_field]].begin(); it != indices[field_map[targeted_field]].upper_bound(entry); it++)
        {
            // targeted_recno += (*it).value_list;
            for (int i = 0; i < (*it).value_list.size(); i++)
            {
                targeted_recno.push_back((*it).value_list[i]);
            }
        }
    }
    return targeted_recno;
}
Queue<Token *> Table::infix_to_postfix(vectorstr infix) // Shunting Yard
{
    Stack<Token *> stack;
    Queue<Token *> queue;

    int i = 0;
    while (i < infix.size())
    {
        Token *t;
        // cout << "infix[i]: " << infix[i] << endl;
        if (infix[i] == "(")
        {
            t = new LParen();
            stack.push(t); //"(" pushed into stack
        }
        else if (infix[i] == ")")
        {
            bool isLeftParen = false;
            while (!isLeftParen)
            {
                if (stack.size() == 0)
                {
                    cout << "here" << endl;
                    throw runtime_error("Shunting yard : imbalance parentheis");
                }
                t = stack.pop();
                if (t->get_string() == "(")
                {
                    isLeftParen = true;
                    delete t;
                }
                else
                {
                    queue.push(t);
                }
            }
        }
        else if (infix[i] == "<" || infix[i] == ">" || infix[i] == "<=" || infix[i] == ">=" || infix[i] == "=")
        {
            t = new Relational(infix[i]);
            while (!stack.empty() && stack.top()->get_type() == RELATIONAL)
            {
                queue.push(static_cast<Relational *>(stack.pop()));
            }
            stack.push(t);
        }
        else if (infix[i] == "or")
        {
            t = new Logical(infix[i]);
            while (!stack.empty() && (stack.top()->get_type() == RELATIONAL || stack.top()->get_type() == LOGICAL))
            {
                if (stack.top()->get_type() == RELATIONAL)
                {
                    queue.push(static_cast<Relational *>(stack.pop()));
                }
                else if (stack.top()->get_type() == LOGICAL)
                {
                    queue.push(static_cast<Logical *>(stack.pop()));
                }
            }
            stack.push(t);
        }
        else if (infix[i] == "and")
        {
            t = new Logical(infix[i]);
            while (!stack.empty() && (stack.top()->get_type() == RELATIONAL || stack.top()->get_type() == LOGICAL && stack.top()->get_string() == "and"))
            {
                if (stack.top()->get_type() == RELATIONAL)
                {
                    queue.push(static_cast<Relational *>(stack.pop()));
                }
                else if (stack.top()->get_type() == LOGICAL && stack.top()->get_string() == "and")
                {
                    queue.push(static_cast<Logical *>(stack.pop()));
                }
            }
            stack.push(t);
        }
        else
        {
            t = new TokenStr(infix[i]);
            queue.push(t);
        }
        i++;
    }
    while (!stack.empty())
    {
        if (stack.top()->get_string() == "(")
        {
            throw runtime_error("Shunting yard : imbalance parentheis");
        }
        queue.push(stack.pop());
    }
    //   cout << "Stack: " << stack << endl;
    // cout << "Queue: " << queue << endl
    //      << endl;
    return queue;
}
