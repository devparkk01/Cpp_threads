#include<iostream>
#include <thread>

using namespace std; 

class Read{
    public:
    Read(){
    }

    void run(int times) {
        for(int i = 0 ; i < times; ++i){
            cout << "Reading " << endl; 
        }
    }
};

class Print {
    public:
    int count ;

    Print(int count) {
        this->count = count; 
    }
    void print(){
        for(int i = 0 ; i < count ; ++i) {
            cout << "Printing " << endl; 
        }
    }

};


int main() {
    // First create an object of the class 
    Read reader; 

    // Argumens: Reference of the member function, reference of the object, and parameters  
    // second argument: we need to provide the instance of the class on which the member function should be called.
    thread t(&Read::run, &reader, 5);
    t.join();

    Print *printer = new Print(3);

    // we can pass the reference of the object even through pointer
    thread t2(&Print::print,  printer );
    t2.join();
    return 0 ;
}