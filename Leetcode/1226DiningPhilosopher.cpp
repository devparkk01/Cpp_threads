/*
https://leetcode.com/problems/the-dining-philosophers/description/
*/

/*
Allow only 4 philosophers to eat at the same time, at least one philosopher will get both forks.

*/

// using 5 mutexes (each for a fork) and a counting semaphore
#include <thread>
#include <chrono>
#include <semaphore> 

class DiningPhilosophers {
private:
    mutex mtx[5];
    counting_semaphore<4> sem{4};
    
public:
    DiningPhilosophers() { }
    void wantsToEat(int philosopher, function<void()> pickLeftFork, function<void()> pickRightFork, function<void()> eat, function<void()> putLeftFork, function<void()> putRightFork) {

        int left = philosopher;
        int right = (philosopher + 1) % 5;
        
        sem.acquire(); // if there are 4 philosophers eating, thread will wait here

        unique_lock<mutex> lckLeft(mtx[left]);
        unique_lock<mutex> lckRight(mtx[right]);
        pickLeftFork(); 
        pickRightFork(); 
        eat(); 
        putLeftFork();
        putRightFork(); 
        
        lckLeft.unlock();
        lckRight.unlock();
        

        sem.release(); // finish eating, release 1 spot for other philosophers
    }
};


// using 5 binary_semaphore (each for a fork) and a counting semaphore

class DiningPhilosophers {
public:
    binary_semaphore sempFork[5] = {
        binary_semaphore{1},
        binary_semaphore{1},
        binary_semaphore{1},
        binary_semaphore{1},
        binary_semaphore{1}
    };
    counting_semaphore<4> pickSem{4};

    DiningPhilosophers() {

    }

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {

        
        int leftFork = philosopher;
        int rightFork = (philosopher + 1 ) % 5; 

        pickSem.acquire();
    
        sempFork[leftFork].acquire();
        sempFork[rightFork].acquire();
        pickLeftFork();
        pickRightFork();
        eat();
        putLeftFork();
        putRightFork();

        sempFork[leftFork].release();
        sempFork[rightFork].release();

        pickSem.release(); 
		
    }
};

// Another approach is to pick right then left fork for the last philosopher, and left then right for all other 
// philosophers


class DiningPhilosophers {
public:

    binary_semaphore semp[5] = {
        binary_semaphore(1),
        binary_semaphore(1),
        binary_semaphore(1),
        binary_semaphore(1),
        binary_semaphore(1)
    };

    DiningPhilosophers() {

    }

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {

        
        int leftFork = philosopher;
        int rightFork = (philosopher + 1 ) % 5; 

        // pick right then left for last philosopher
        if ( philosopher == 4) {
            semp[rightFork].acquire();
            semp[leftFork].acquire();
            pickRightFork();
            pickLeftFork();
            eat();
            putRightFork();
            putLeftFork();
            semp[rightFork].release();
            semp[leftFork].release();
        }
        // pick left then right for rest of the philosophers
        else {
            semp[leftFork].acquire();
            semp[rightFork].acquire();
            pickLeftFork();
            pickRightFork();
            eat();
            putLeftFork();
            putRightFork();
            semp[leftFork].release();
            semp[rightFork].release();
        }
    }
};