/*
https://leetcode.com/problems/fizz-buzz-multithreaded/description/
*/

class FizzBuzz {
private:
    int n;
    int i ;
    condition_variable cv; 
    mutex mtx;  

public:
    FizzBuzz(int n) {
        this->n = n;
        i = 1 ;
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        while(true) {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [this]() {
                return (i % 3 == 0 && i % 5 != 0) || i > n ;
            });
            if (i > n) {
                cv.notify_all();
                return ;
            }
            printFizz();
            i++;
            cv.notify_all(); 
        }
        
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        while(true) {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock,[this]() {
                return (i % 5 == 0 && i % 3 != 0) || i > n;
            });
            if (i > n) {
                cv.notify_all(); 
                return ;
            }
            printBuzz();
            i++;
            cv.notify_all(); 
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
        while(true) {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [this]() {
                return (i % 5 == 0 && i % 3 == 0) || i > n ;
            });
            if (i > n) {
                cv.notify_all(); 
                return ;
            }
            printFizzBuzz();
            i++;
            cv.notify_all(); 
        }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {

        while(true) {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [this]() {
                return (i % 5 != 0 && i % 3 != 0) || i > n ;
            });
            if (i > n) {
                cv.notify_all(); 
                return ;
            }
            printNumber(i);
            i++;
            cv.notify_all(); 
        }
        
    }
};