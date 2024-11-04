#include<iostream>
#include <thread>

using namespace std; 

class Read{
    public:
    Read(){
    }

    void run(int times) {
        for(int i = 0 ; i < times; ++i){
            cout << "Reading " << "\n"; 
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
            cout << "Printing " << "\n"; 
        }
    }

};


int main() {
    // First create an object of the class 
    Read reader; 

    // Argumens: Reference of the member function, reference of the object, and parameters  
    // second argument: we need to provide the instance of the class on which the member function should be called.
    thread t1(&Read::run, &reader, 100);
    t1.join();  // caller thread(main thread) is blocked until t1 finishes execution

    Print *printer = new Print(3);

    // we can pass the reference of the object even through pointer
    thread t2(&Print::print,  printer );   // caller thread(main thread) is blocked until t2 finishes execution
    t2.join();
    return 0 ;
}