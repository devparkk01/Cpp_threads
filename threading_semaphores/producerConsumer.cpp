#include<iostream>
#include<thread>
#include <semaphore>
using namespace std;

// intially producer can get started to produce
binary_semaphore produce_sem{1};
// consumer can not start unless producer releases(signals) the semaphore to start consuming
binary_semaphore consume_sem{0};

int SIZE = 5;
int buff[5];

void produce() {
    for(int i = 0 ; i < 10 ; ++i) {
        // wait for produce_sem to be free
        produce_sem.acquire();
        cout << "Producing " << i + 1 << " times " <<endl; 
        for(int j = 0 ; j < 5 ; ++j) {
            buff[j] = rand() % 200;
            cout << buff[j] << " ";
        }
        cout << endl; 
        // Release consume_sem. or signal consume_sem to start consuming
        consume_sem.release(); 
    }
}

void consume() {
    for(int i = 0 ; i < 10 ; ++i) {
        // wait for consume_sem to be free
        consume_sem.acquire(); 
        cout << "Consuming " << i + 1 << " times " <<endl; 
        for(int j = 0 ; j < 5 ; ++j) {
            cout << buff[j] << " ";
        }
        cout << endl; 
        // Release produce_sem. or signal produce_sem to start producing
        produce_sem.release();
    }
}


int main() {

    thread producer(produce);
    thread consumer(consume);


    producer.join();
    consumer.join();

    return 0 ; 
}