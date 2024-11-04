
/*
https://leetcode.com/problems/print-zero-even-odd/description/

*/
class ZeroEvenOdd {
private:
    int n;
    binary_semaphore sem_zero{1};
    binary_semaphore sem_odd {0};
    binary_semaphore sem_even {0};

public:
    ZeroEvenOdd(int n) {
        this->n = n;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        for(int i = 1 ; i <= n ; ++i) {
            sem_zero.acquire();
            printNumber(0);
            if ( i % 2 == 0) {
                sem_even.release(); 
            } else {
                sem_odd.release(); 
            }
        }
    }

    void even(function<void(int)> printNumber) {
        for(int i = 2; i <= n; i+=2) {
            sem_even.acquire(); 
            printNumber(i);
            sem_zero.release();
        }
    }

    void odd(function<void(int)> printNumber) {
        for(int i = 1 ; i <= n ; i+= 2 ) {
            sem_odd.acquire(); 
            printNumber(i);
            sem_zero.release();
        }
    }
};
