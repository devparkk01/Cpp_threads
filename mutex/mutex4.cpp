/* This is about shared_mutex and shared_lock  

in order to use shared_mutex, include the header <shared_mutex>
shared_mutex is available only after c++17. 

We can use shared_lock for both exclusive as well as shared locking.
*/


#include<iostream>
#include<thread>
#include<shared_mutex>
#include<vector>

using namespace std; 


class ReaderWriter {

    shared_mutex mtx; 
    unordered_map<string, int> phonebook; 

    public:
    ReaderWriter() {
        phonebook = unordered_map<string, int>{{"AJAY", 1972}, {"SHYAM", 1976}, 
                                   {"RAM", 1983}};
    }

    void addContact(string name, int number ) {
        // get the exclusive lock for write
        unique_lock<shared_mutex> writerLock(mtx);
        cout << "Starting update \n"; 
        phonebook[name] = number; 
        this_thread::sleep_for(chrono::seconds(2));
        cout << "Ending update \n";
    }

    void readContact(string name) {
        // get the shared lock for reads
        shared_lock<shared_mutex> readerLock(mtx);
        if ( phonebook.count(name)) {
            cout << name << " : " << phonebook[name] << "\n";
        } else {
            cout << name << " does not exist \n";
        }
    }

};


int main () {
    ReaderWriter readerwriter; 

    thread reader1([&readerwriter]() {
        readerwriter.readContact("AJAY");
    });

    thread reader2([&readerwriter]() {
        readerwriter.readContact("SHYAM");
    });

    thread reader3([&readerwriter]() {
        readerwriter.readContact("TOM");
    });

    thread writer1([&readerwriter]() {
        readerwriter.addContact("TOM", 2342);
    });


    thread reader4([&readerwriter]() {
        readerwriter.readContact("TOM");
    });


    thread reader5([&readerwriter]() {
        readerwriter.readContact("JOHN");
    });


    thread writer2([&readerwriter]() {
        readerwriter.addContact("TOSH" , 3333);
    });

    thread reader6([&readerwriter]() {
        readerwriter.readContact("TOSH");
    });

    reader1.join();
    reader2.join();
    reader3.join();
    reader4.join();
    reader5.join();
    reader6.join();


    writer1.join();
    writer2.join(); 
    return 0 ; 
}
