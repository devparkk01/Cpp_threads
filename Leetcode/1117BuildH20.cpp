/*
https://leetcode.com/problems/building-h2o/
*/

// using semaphores 
class H2O {
public:
    counting_semaphore<2> hydSem(2); // some places we have to use curly braces {} for initial value 
    binary_semaphore oxySem{0};
    int hydCount = 0; // stores hydrogen count 
    H2O() {
        
    }

    void hydrogen(function<void()> releaseHydrogen) {
        hydSem.acquire(); 
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();
        hydCount++; 
        if( hydCount == 2) {
            oxySem.release(); 
        }
    }

    void oxygen(function<void()> releaseOxygen) {
        oxySem.acquire(); 
        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
        hydCount = 0 ; // reset hydrogen count; 
        hydSem.release();
        hydSem.release();
    }
};

// using mutex and condition variable 
class H2O {
public:
    int hydCount = 0; 
    condition_variable cv; 
    mutex mtx; 
    H2O() {
        
    }

    void hydrogen(function<void()> releaseHydrogen) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [this](){
            return (hydCount < 2);
        });
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();
        hydCount++; 
        cv.notify_all(); 
    }

    void oxygen(function<void()> releaseOxygen) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [this](){
            return (hydCount == 2);
        });
        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
        hydCounta -= 2; 
        cv.notify_all(); 
    }
};