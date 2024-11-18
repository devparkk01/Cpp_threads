#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>

using namespace std; 

condition_variable cv;
mutex mtx; 

const int SIZE = 5;
int buff[SIZE];
bool shouldProduce = true; 


void produce() {
    {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [&]() {
            return (shouldProduce == true); 
        });
        cout << "Started producing \n";

        for(int i = 0 ; i < 5 ; ++i) {
            buff[i] = rand() % 200; 
            cout << buff[i] << " "; 
        }
        cout << "\nProducing is done \n";
        shouldProduce = false; 
    }
    cv.notify_one();
}


void consume() {
    {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [&]() {
            return (shouldProduce == false);
        });
        cout << "Started consuming \n";

        for(int i = 0 ; i < 5 ; ++i) {
            cout << buff[i] << " ";
        }
        cout << "\nConsuming is done\n"; 
        shouldProduce = true; 
    }
    cv.notify_one();
}

int main() {

    thread producer(produce);
    thread consumer(consume);


    producer.join();
    consumer.join();

    return 0 ; 
}