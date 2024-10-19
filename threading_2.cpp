#include<iostream>
#include <thread>

using namespace std;

void print(int value) {
    cout << "printing " << endl;
    for(int i = 0 ; i < value; ++i) {
        cout << i << " " << endl; 
        this_thread::sleep_for(chrono::seconds(1));
    } 
    cout << "Printing done " << endl; 
}

// creating custom thread class 
class Thread {
    private:
    thread *t; 
    string name; 
    int value; 

    public:
    void some() {
        for(int i = 0 ;i < value; ++i) {
            cout << value << endl; 
        }
    }
    Thread(string name, int value) {
        this->name = name; 
        this->value = value; 
        t = new thread(print, value);
    } 
    void join() {
        t->join();
    }
};


int main() {

    Thread t1 = Thread("First", 10);
    t1.join();

    return 0; 
}