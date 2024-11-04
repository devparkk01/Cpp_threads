#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>

using namespace std; 

condition_variable cv;
mutex mtx; 

int SIZE = 5;
int buff[5];


void produce() {


}


void consume() {
    unique_lock<mutex> ul(mtx);
    cv.wait(ul, )



}

int main() {

    thread producer(produce);
    thread consumer(consume);


    producer.join();
    consumer.join();

    return 0 ; 
}