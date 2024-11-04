

#include<iostream>
#include<queue>
#include<thread>
#include<mutex>
#include<condition_variable>

#define endl '\n'


using namespace std; 



class Task {
    int id; 
    int priority;

    public:
    Task(int id, int priority): id(id), priority(priority) {

    }
    void execute() {
        cout << "Executing task id " << id << endl; 
        this_thread::sleep_for(chrono::milliseconds(400));
        cout << "Executed task id " << id << endl; 
    }

    int getPriority() {
        return priority;
    }
    int getId() {
        return id; 
    }
};

class compare {
    public:
    bool operator() ( Task &a,  Task &b) {
        if ( a.getPriority() == b.getPriority()) {
            return a.getId() > b.getId() ; // greater id should be at the bottom of the priority queue 
        }
        return a.getPriority() > b.getPriority(); // which should be at the bottom of the priority queue 
    }
};

class Scheduler {
    int workerCount; 
    priority_queue<Task, vector<Task>, compare> taskQueue; 
    vector<thread>workers; 

    mutex mtx;
    condition_variable cv; 
    bool stop = false; 

    public:
    Scheduler(int workerCount): workerCount(workerCount) {
        workers.reserve(workerCount);
        for(int i = 0 ; i < workerCount; ++i) {
            workers.push_back(thread([this](){
                this->startExecuting();
            }));
        }
    }




    void startExecuting() {

        while(true) {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [&]() {
                return !taskQueue.empty() || stop ;
            });

            if (stop && taskQueue.empty()) {
                return; 
            }

            auto task = taskQueue.top(); taskQueue.pop(); 
            lock.unlock(); 
            task.execute(); 
        }

    }

    void addTask(const Task &t) {
        // get the lock
        unique_lock<mutex> lock(mtx);
        taskQueue.push(t);
        cv.notify_one(); // when a task is added, only one thread should be woken, not all of them
    }

    void stopExecuting() {
        stop = true; 
        cv.notify_all();
        for(int i = 0 ; i < workerCount; ++i) {
            workers[i].join(); 
        }
    }

};


int main () {
    Scheduler scheduler(2);
    scheduler.addTask(Task(1, 3));
    scheduler.addTask(Task(2, 2));
    scheduler.addTask(Task(3, 0));
    scheduler.addTask(Task(4, 3));
    scheduler.addTask(Task(5, 2));
    scheduler.addTask(Task(6, 1));
    scheduler.addTask(Task(7, 5));
    scheduler.addTask(Task(8, 2));
    scheduler.addTask(Task(9, 1));
    scheduler.addTask(Task(10, 3));

    scheduler.stopExecuting(); 

    return 0; 

}