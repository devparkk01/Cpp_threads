#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void print_id(int id) {
    std::unique_lock<std::mutex> lock(mtx);
    // Wait until ready becomes true
    cv.wait(lock, [] { return ready; });
    // After being notified, proceed
    std::cout << "Thread " << id << '\n';
}

void go() {
    // std::unique_lock<std::mutex> lock(mtx);
    ready = true;
    std::cout << "Go signal sent, notifying all threads.\n";
    // Notify all waiting threads
    cv.notify_all();
}

int main() {
    std::thread threads[5];
    
    // Spawn 5 threads
    for (int i = 0; i < 5; ++i)
        threads[i] = std::thread(print_id, i);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    go(); // Signal all threads to proceed

    // Join all threads
    for (auto& th : threads) th.join();

    return 0;
}
