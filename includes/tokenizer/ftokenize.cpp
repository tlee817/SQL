
// using namespace std;
#include "../../includes/tokenizer/ftokenize.h"

FTokenizer::FTokenizer(char *fname) : _pos(0), _blockPos(0), _more(true)
{
    // set string for stk
    // set done to false
    _f.open(fname);
    _stk = STokenizer();
    if (_f.fail())
    {
        cout << "Input file opening failed. " << endl;
        exit(1);
    }
    // get a block
    _more = get_new_block();
}

Token FTokenizer::next_token()
{
    Token t;

    if (_stk.done())
    {
        // cout << "INSIDE next_token() function , entered _stk.done() " << endl;
        //  _stk >> t;
        //   cout << "Last token string: " << t.token_str() << endl;
        if (!get_new_block())
        {
            /*
            cout << "Last Block in STK:";
            _stk.get_buffer();
            cout << endl;
            cout << "In next_token() function, Entered !get_new_block condition" << endl;
*/
            _more = false;
            return t;
        }
    }

    _stk >> t;
    // cout << "INSIDE next_token() function, reached bottom to extract token with STK" << endl;
    return t;
}

FTokenizer &operator>>(FTokenizer &f, Token &t)
{
    if (f._stk.more())
    {
        // cout << "INSIDE operator>>, in f._stk.more() condition" << endl;
        t = f.next_token();
    }
    else
    {
        if (f.get_new_block())
        {
            // cout << "INSIDE operator>>, in !f._stk.more() ->f.get_new_block() condition" << endl;
            t = f.next_token();
            //  f._stk >> t;
        }
    }
    return f;
}
/* t = f.next_token();

    if (!f._stk.more())
    {
        if (f.get_new_block())
        {
            f._stk >> t;
        }
        //f._stk >> t;
    }
    //    f._stk >> t;
    return f;*/

bool FTokenizer::get_new_block()
{
    //_blockPos = 0;
    if (!more())
    {
        // cout << "In get_new_block() function , entered !more() condition" << endl;

        return false;
    }
    char _buffer[MAX_BUFFER + 1] = "";
    _f.read(_buffer, MAX_BUFFER);
    if (_f.gcount() == 0)
    {

        cout << "---------------------------------------------------------------" << endl
             << "INSIDE GET NEW BLOCK FUNCTION: entered _f.gcount() == 0" << endl
             << "gcount()=  " << _f.gcount() << endl
             << "More : " << _more << " ( 0 = false , 1 = true)" << endl
             << "New block: " << _buffer << endl
             << "---------------------------------------------------------------" << endl;

        _more = false;
        return false;
    }

    cout << "---------------------------------------------------------------" << endl
         << "INSIDE GET NEW BLOCK FUNCTION: " << endl
         << "gcount()=  " << _f.gcount() << endl
         << "More : " << _more << " ( 0 = false , 1 = true)" << endl
         << "New block: " << _buffer << endl
         << "---------------------------------------------------------------" << endl;

    _buffer[_f.gcount()] = '\0';
    _stk.set_string(_buffer);
    //  _stk.get_buffer();
    // cout << "Inside get_new_block() function , Reached bottom of get_new_block(). returning true..." << endl;
    return true;
}
bool FTokenizer::more() // Done
{
    return _more;
}

int FTokenizer::pos() // Done
{
    return _pos;
}

int FTokenizer::block_pos() // Done
{
    return _blockPos;
}
/*

ifstream infile;
    infile.open(filename);
    if (infile.fail())
    {
        cout << "Input file opening failed. " << endl;
        exit(1);
    }

    string name;
    while (!infile.eof())
    {
        infile >> id >> name >> score;
        idArray[count] = id;
        nameArray[count] = name;
        scoreArray[count] = score;
        cout << setw(10) << id << setw(10) << name << setw(4) << score << endl;
        count++;
    }
*/