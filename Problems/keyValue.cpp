/*
Implement a multi threaded key value store
*/

#include <iostream>
#include <unordered_map>
#include <string>
#include <shared_mutex>
#include <thread>

using namespace std; 

class KeyValueStore {
private:
    unordered_map<string, string> store;
    shared_mutex mutex;

public:
    // Set key-value pair (write access)
    void set(const string& key, const string& value) {
        unique_lock<shared_mutex> lock(mutex); // Exclusive access for write
        store[key] = value;
    }

    // Get value by key (read access)
    string get(const string& key) {
        shared_lock<shared_mutex> lock(mutex); // Shared access for read
        if (store.find(key) != store.end()) {
            return store[key];
        }
        return ""; // Or handle missing key differently
    }

    // Remove key-value pair
    void remove(const string& key) {
        unique_lock<shared_mutex> lock(mutex); // Exclusive access for delete
        store.erase(key);
    }
};

void writerThread(KeyValueStore& kvStore, const string& key, const string& value) {
    kvStore.set(key, value);
    cout << "Set key: " << key << " to value: " << value << "\n";
}

void readerThread(KeyValueStore& kvStore, const string& key) {
    string value = kvStore.get(key);
    cout << "Read key: " << key << " value: " << (value.empty() ? "not found" : value) << "\n";
}

int main() {
    KeyValueStore kvStore;

    thread t1(writerThread, ref(kvStore), "user1", "Alice");
    thread t2(writerThread, ref(kvStore), "user2", "Bob");
    thread t3(readerThread, ref(kvStore), "user1");
    thread t4(readerThread, ref(kvStore), "user2");
    thread t5(&KeyValueStore::get, &kvStore, "user1");

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    t5.join(); 
    return 0;
}
