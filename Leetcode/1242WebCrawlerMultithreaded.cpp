/*
https://leetcode.com/problems/web-crawler-multithreaded/description/

two solutions here 
*/

// First solution 
class Solution {
private:

    string extractHostName(string& url){
        int pos = url.substr(7).find('/');
        return url.substr(7 , pos) ; 
    }

public:

    vector<string> crawl(string startUrl, HtmlParser htmlParser){
        queue<string>q; 
        unordered_set<string>visited; 
        int thread_size = thread::hardware_concurrency();

        mutex m; 
        condition_variable cv; 
        int working = 0 ; 

        string hostname = extractHostName(startUrl);

        q.push(startUrl);
        visited.insert(startUrl);


        auto startCrawling = [&](){
            while(true) {
                unique_lock<mutex> lock(m);

                cv.wait_for(lock , 20ms, [&](){
                    return q.size() > 0; 
                });

                if ( q.size() == 0 ){
                    return ; 
                }
                string curUrl = q.front() ; q.pop(); 
                lock.unlock(); 

                vector<string> urls = htmlParser.getUrls(curUrl);

                lock.lock(); // lock the mutex because we are gonna modify the queue as well visited set
                for(auto &url: urls) {
                    if ( visited.find(url) == visited.end() && extractHostName(url) == hostname) {
                        visited.insert(url);
                        q.push(url);
                    }
                }
                lock.unlock(); // first release the lock, then notify_all waiting threads. 
                cv.notify_all(); 

            }
        };

        thread workers[thread_size];

        for(int i= 0 ; i < thread_size; ++i) {
            workers[i] = thread(startCrawling);
        }
        // join in a different loop 
        for(int i = 0 ; i < thread_size; ++i) {
            workers[i].join();
        }

        return vector<string>(visited.begin(), visited.end());
    }

};

// Second solution

class Solution {
private:

    string extractHostName(string& url){
        int pos = url.substr(7).find('/');
        return url.substr(7 , pos) ; 
    }

public:

    vector<string> crawl(string startUrl, HtmlParser htmlParser){
        queue<string>q; 
        unordered_set<string>visited; 
        int thread_size = thread::hardware_concurrency();

        mutex m; 
        condition_variable cv; 
        int working = 0 ; // stores the count of currently working threads 

        string hostname = extractHostName(startUrl);

        q.push(startUrl);
        visited.insert(startUrl);


        auto startCrawling = [&](){
            while(true) {
                unique_lock<mutex> lock(m);
                // wait until there is some item in the queue or no threads are currently working 
                cv.wait(lock, [&](){ 
                    return !q.empty() || working == 0 ; 
                });
                // if the queue is empty, we are done
                if ( q.empty()){
                    return ; 
                }
                // this thread will start working (crawling), so increment working count
                working++; 

                string curUrl = q.front() ; q.pop(); 
                lock.unlock(); 
                vector<string> urls = htmlParser.getUrls(curUrl);
                
                lock.lock(); // lock the mutex because we are gonna modify the queue as well visited set
                for(auto &url: urls) {
                    if ( visited.find(url) == visited.end() && extractHostName(url) == hostname) {
                        visited.insert(url);
                        q.push(url);
                    }
                }
                working--; // this thread is done crawling, so decrement working count
                lock.unlock();   // first release the lock, then notify other threads 
                cv.notify_all(); 
            }
        };

        thread workers[thread_size];

        for(int i= 0 ; i < thread_size; ++i) {
            workers[i] = thread(startCrawling);
        }

        for(int i = 0 ; i < thread_size; ++i) {
            workers[i].join();
        }

        return vector<string>(visited.begin(), visited.end());
    }
};