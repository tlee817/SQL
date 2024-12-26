// #include <iostream>
// #include <fstream>
// #include <cstring>
// #include <string>
// using namespace std;

// // utility functions
// bool file_exists(const char filename[]);

// // void open_fileRW(fstream& f, const char filename[]) throw(char*);
// void open_fileW(fstream &f, const char filename[]);
// void confuse_me();
// void simple_test();
// //----------------------------------------------------------------------------
// //                      C L A S S   R E C O R D
// //----------------------------------------------------------------------------

// class Record
// {
// public:
//     // when you construct a Record, it's either empty or it
//     //   contains a word
//     Record()
//     {
//         _record[0] = '\0';
//         recno = -1;
//     }

//     Record(char str[])
//     {
//         strncpy(_record, str, MAX);
//     }
//     Record(string s)
//     {
//         strncpy(_record, s.c_str(), MAX);
//     }

//     long write(fstream &outs);           // returns the record number
//     long read(fstream &ins, long recno); // returns the number of bytes
//                                          //       read = MAX, or zero if
//                                          //       read passed the end of file

//     friend ostream &operator<<(ostream &outs,
//                                const Record &r);

// private:
//     static const int MAX = 100;
//     int recno;
//     char _record[MAX + 1];
// };

// long Record::write(fstream &outs)
// {
//     // r.write(f); //take the Record r and write it into file f
//     //   and return the record number of this Record

//     // write to the end of the file.
//     outs.seekg(0, outs.end);

//     long pos = outs.tellp(); // retrieves the current position of the
//                              //       file pointer

//     // outs.write(&record[0], sizeof(record));
//     outs.write(_record, sizeof(_record));

//     return pos / sizeof(_record); // record number
// }

// long Record::read(fstream &ins, long recno)
// {
//     // returns the number of bytes read.
//     //     r.read(f, 6);
//     //     cout<<r<<endl;
//     long pos = recno * sizeof(_record);
//     ins.seekg(pos, ios_base::beg);

//     // ins.read(&_record[0], sizeof(_record))
//     ins.read(_record, sizeof(_record));
//     // don't you want to mark the end of  the cstring with null?
//     //_record[] => [zero'\0'trash trash trash trash]
//     // don't need the null character, but for those of us with OCD and PTSD:
//     _record[ins.gcount()] = '\0';
//     return ins.gcount();
// }
// ostream &operator<<(ostream &outs,
//                     const Record &r)
// {
//     outs << r._record;
//     return outs;
// }

// //----------------------------------------------------------------------------
// //                      F I L E   F U N C T I O N S
// //----------------------------------------------------------------------------

// //[    |    |     |    |    |     |]
// //-------------------------------------------------
// bool file_exists(const char filename[])
// {
//     const bool debug = false;
//     fstream ff;
//     ff.open(filename,
//             std::fstream::in | std::fstream::binary);
//     if (ff.fail())
//     {
//         if (debug)
//             cout << "file_exists(): File does NOT exist: " << filename << endl;
//         return false;
//     }
//     if (debug)
//         cout << "file_exists(): File DOES exist: " << filename << endl;
//     ff.close();
//     return true;
// }

// // void open_fileRW(fstream& f, const char filename[]) throw(char*){
// //     const bool debug = false;
// //     //opening a nonexistent file for in|out|app causes a fail()
// //     //  so, if the file does not exist, create it by openning it for
// //     //  output:
// //     if (!file_exists(filename)){
// //         //create the file
// //         f.open(filename, std::fstream::out|std::fstream::binary);
// //         if (f.fail()){
// //             cout<<"file open (RW) failed: with out|"<<filename<<"]"<<endl;
// //             throw("file RW failed  ");
// //         }
// //         else{
// //             if (debug) cout<<"open_fileRW: file created successfully: "<<filename<<endl;
// //         }
// //     }
// //     else{
// //         f.open (filename,
// //             std::fstream::in | std::fstream::out| std::fstream::binary );
// //         if (f.fail()){
// //             cout<<"file open (RW) failed. ["<<filename<<"]"<<endl;
// //             throw("file failed to open.");
// //         }
// //     }

// // }
// void open_fileW(fstream &f, const char filename[])
// {
//     f.open(filename,
//            std::fstream::out | std::fstream::binary);
//     if (f.fail())
//     {
//         cout << "file open failed: " << filename << endl;
//         throw("file failed to open.");
//     }
// }

// //----------------------------------------------------------------------------
// //                           M  A  I  N  (  )
// //----------------------------------------------------------------------------

// int main(int argc, char *argv[])
// {
//     cout << endl
//          << endl
//          << endl
//          << "================================" << endl;
//     // simple_test();
//     cout << "=,=,=,=,=,=,=,=,=,=,=,=,=,=,=,=,=,=,=,=,\n\n"
//          << endl;
//     confuse_me();
//     cout << endl
//          << endl
//          << ". . . . . . . . . . .. .. . . . ." << endl
//          << endl;

//     // confuse_me();

//     // cout <<endl<<endl<<endl<< "================================" << endl;
//     return 0;
// }

// //----------------------------------------------------------------------------
// //                        T E S T   F U N C T I O N S
// //----------------------------------------------------------------------------

// void simple_test()
// {

//     fstream f;
//     // reset the file: use this for new files
//     open_fileW(f, "record_list.bin");

//     Record r;
//     int recno = -1;
//     r = Record("Joe Zero"); // filling the envelop
//     recno = r.write(f);
//     cout << "wrote into record: " << recno << endl;

//     r = Record("One Arm Jane"); // filling the envelop
//     recno = r.write(f);
//     cout << "wrote into record: " << recno << endl;

//     r = Record("Two face Harvey"); // filling the envelop
//     recno = r.write(f);
//     cout << "wrote into record: " << recno << endl;

//     r = Record("Three Eyed Raven"); // filling the envelop
//     recno = r.write(f);
//     cout << "wrote into record: " << recno << endl;

//     r = Record("Four Eyes, Four Eyes! "); // filling the envelop
//     recno = r.write(f);
//     cout << "wrote into record: " << recno << endl;

//     r = Record("Cinco De Mayo, Bryan! "); // filling the envelop
//     recno = r.write(f);
//     cout << "wrote into record: " << recno << endl;

//     r = Record("The Six Shooter Kid! "); // filling the envelop
//     recno = r.write(f);
//     cout << "wrote into record: " << recno << endl;

//     f.close();

//     Record r2;
//     // open the file for reading and writing.
//     open_fileRW(f, "record_list.bin");
//     r2.read(f, 3);                      // empty envelop to be filled by the Record object
//     cout << "record 3: " << r2 << endl; // insertion operator of the Record object
//     r2.read(f, 6);
//     cout << "record 6: " << r2 << endl;

//     // reading passed the end of file:
//     long bytes = r2.read(f, 19);
//     cout << "number of bytes read: " << bytes << endl;
// }
// void confuse_me()
// {
//     string list[10] = {"zero",
//                        "one",
//                        "two",
//                        "three",
//                        "four",
//                        "five",
//                        "six",
//                        "seven",
//                        "eight",
//                        "nine"};

//     cout << "[ ]Show the list of input records:" << endl;
//     cout << "------------------------------" << endl;

//     for (int i = 0; i < 10; i++)
//     {
//         cout << "|" << setw(6) << list[i] << "|" << endl;
//     }
//     cout << endl
//          << endl;

//     cout << "[ ]Write / INSERT records into the file:" << endl;
//     cout << "--------------------------------------------" << endl;

//     fstream f;
//     // reset the file:
//     open_fileW(f, "record_list.bin");
//     for (int i = 0; i < 10; i++)
//     {
//         Record r(list[i]); // filling the envelop
//         long recno = r.write(f);
//         cout << "[" << setw(5) << list[i] << "]" << " was written into file as record: " << setw(2) << recno << endl;
//     }
//     f.close();
//     cout << endl
//          << endl;
//     cout << "\n\n[ ]Read / RETRIEVE / SELECT ALL records in the file: " << endl;
//     cout << "------------------------------------------------------" << endl;

//     // open the file for reading and writing.
//     Record rec;
//     open_fileRW(f, "record_list.bin");

//     int i = 0;
//     // the famous Golden While Loop:
//     rec.read(f, i); // read the first record
//     while (!f.eof())
//     {
//         cout << "reading record " << setw(3) << i << ": " << rec << endl;
//         i++;
//         rec.read(f, i); // read next record.
//     }
//     f.close();
//     cout << endl
//          << endl;

//     cout << "[ ]Read / RETRIEVE / SELECT records from the file: " << endl;
//     cout << "------------------------------------------------------" << endl;

//     Record r;
//     int selected_records[] = {4, 6, 8, 9};
//     // open the file for reading and writing.
//     open_fileRW(f, "record_list.bin");
//     for (int i = 0; i < 4; i++)
//     {
//         r.read(f, selected_records[i]);
//         cout << "reading record " << selected_records[i] << ": " << r << endl;
//     }
//     f.close();
//     cout << endl
//          << endl;

//     cout << "\n\n[ ]Reading passed the end of file: " << endl;
//     cout << "---------------------------------------------" << endl;

//     long bytes = r.read(f, 19);
//     cout << "  number of bytes read: " << bytes << endl;

//     cout << endl
//          << endl;
//     cout << "----------------------------------------------------" << endl;
//     cout << "                     E N D " << endl;
//     cout << "----------------------------------------------------" << endl;
// }

// //----------------------------------------------------------------------------
// //                                  J U N K
// //----------------------------------------------------------------------------

// /*
//  *
//  *     int recno = 0;
//     //get_record returns a vector containing all
//     //      the rows of the Record object.
//     r.read(f, recno); //first record
//     while (!f.eof()){
//         cout<<"["<<recno<<"]"<<r.get_record()<<endl;
//         recno++;

//         r.read(f, recno); //read the next record

//  *
//  *
//  */
