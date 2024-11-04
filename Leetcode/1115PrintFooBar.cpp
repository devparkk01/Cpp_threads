/*
https://leetcode.com/problems/print-foobar-alternately/
*/

// First solution using semaphores
class FooBar {
private:
    int n;
    binary_semaphore print_foo{1};
    binary_semaphore print_bar{0};

public:
    FooBar(int n) {
        this->n = n;
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
            print_foo.acquire(); // decrements print_foo by 1
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
            print_bar.release(); // increases print_bar by 1. Signal print_bar that this semaphore is available now
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
            print_bar.acquire();  // decrements print_ar by 1
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
            print_foo.release(); // increment print_foo by 1. Signal print_foo that this semaphore is available now
        }
    }
};

// Second solution using mutex and condition variable 
class FooBar {
private:
    int n;
    mutex mtx;
    condition_variable cv; 
    bool isFoo = true; // stores if it's Foo's turn or Bar's turn

public:
    FooBar(int n) {
        this->n = n;
    }

    void foo(function<void()> printFoo) {
        for (int i = 0; i < n; i++) {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [this](){
                return isFoo == true; 
            });
        	printFoo();
            isFoo = false;
            cv.notify_one(); 
        }
    }

    void bar(function<void()> printBar) {
        for (int i = 0; i < n; i++) {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [this](){
                return isFoo == false; 
            }); 
        	printBar();
            isFoo = true; 
            cv.notify_one();
        }
    }
};