/*
https://leetcode.com/problems/design-bounded-blocking-queue/
*/


class BoundedBlockingQueue {
public:
    int capacity ;
    mutex m ;
    condition_variable cv; 
    queue<int>q; 
    BoundedBlockingQueue(int capacity) {
        this->capacity= capacity ; 
    }
    
    void enqueue(int element) {
        unique_lock<mutex> lock(m);
        cv.wait(lock, [this](){
            return (q.size() < capacity);
        });
        q.push(element);
        cv.notify_all(); // notify other waiting threads
    }
    
    int dequeue() {
        unique_lock<mutex> lock(m);
        cv.wait(lock, [this](){
            return (!q.empty());
        });
        int x = q.front(); q.pop(); 
        cv.notify_all();  // notify other waiting threads
        return x; 
    }
    
    int size() {
        return q.size() ;
    }
};