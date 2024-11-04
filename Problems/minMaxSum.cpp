/*
Finding the minimum, maximum, and sum of elements in an array can be parallelized efficiently using multithreading.
 Each thread is given a portion of the array to process and returns partial results, which are then 
 combined to get the final result.


*/

#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <limits>

#define endl '\n'

using namespace std; 

const int DATA_SIZE = 50;
const int NUMBER_OF_THREADS = 4;

vector<int> threadResultsSum(NUMBER_OF_THREADS);
vector<int> threadResultsMin(NUMBER_OF_THREADS, INT_MAX);
vector<int> threadResultsMax(NUMBER_OF_THREADS, INT_MIN);

void ThreadedSum(int threadId, vector<int>data, int start, int end) {
    int sum = 0;
    for (int i = start; i < end; ++i) {
        sum += data[i];
    }
    threadResultsSum[threadId] = sum;
}

void ThreadedMin(int threadId, vector<int>data, int start, int end) {
    int minimum = INT_MAX; 
    for (int i = start; i < end; ++i) {
        minimum = min(minimum, data[i]);
    }
    threadResultsMin[threadId] = minimum;
}

void ThreadedMax(int threadId, vector<int>data,  int start, int end) {
    int maximum = INT_MIN;
    for (int i = start; i < end; ++i) {
        maximum = max(maximum, data[i]);
    }
    threadResultsMax[threadId] = maximum;
}

int main() {
    vector<int>data(DATA_SIZE);

    for(int i = 0 ;  i < DATA_SIZE ; ++i) {
        data[i] = rand() % 500 ; 
    }

    vector<thread> threads;

    // Start threads for sum, min, and max calculations
    for (int i = 0; i < NUMBER_OF_THREADS; ++i) {
        int start = i * (DATA_SIZE / NUMBER_OF_THREADS);
        int end = (i + 1) * (DATA_SIZE / NUMBER_OF_THREADS);

        threads.emplace_back(ThreadedSum, i, data, start, end);
        threads.emplace_back(ThreadedMin, i, data, start, end);
        threads.emplace_back(ThreadedMax, i, data, start, end);
    }

    // Wait for threads to finish
    for (auto& t : threads) {
        t.join();
    }

    cout << "Sum is " << accumulate(threadResultsSum.begin(), threadResultsSum.end(), 0 ) << endl;
    cout << "Min is " << *min_element(threadResultsMin.begin(), threadResultsMin.end()) << endl;
    cout << "Max is " << *max_element(threadResultsMax.begin(), threadResultsMax.end()) << endl;

    return 0;
}
