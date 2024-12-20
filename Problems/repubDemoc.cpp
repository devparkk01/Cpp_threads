/*
There is single Bathroom to be used in a Voting agency for both Democrats(D) and Republicans(R) 
* This single Bathroom which can accomodate 3 people at most 
* each person takes f(N) secs to do his thing. f(N) is a function of the person's name and returns varying number 
* CONDITION: At any given time, the bathroom cannot have a mixed set of people i.e. 
* CONDITION: Bathroom can have at most 3 people 
* these combinations aren't allowed (2D, 1R) or (1D,1R) * These are allowed (), (3D), (2D), (1R) i.e. pure Republicans or Pure Democrats 
* While the bathroom is occupied people are to wait in a queue 
* What is the most optimal system where you would manage people in this queue, 
so that  the most eligible person instants gets to use the bathroom whenever its has room, based on above conditions

 */

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

using namespace std;


mutex bathroomMutex;  // whenever someone wants to use the bathroom, he needs to acquire this mutex first 
// it controls the access to the bathroom
condition_variable cv;   // Condition variable to wait for access to a party ( democrat/ republican)

const int MAX_PEOPLE_IN_BATHROOM = 3;  // Max number of people allowed in the bathroom
int republicansInBathroom = 0;  // Count of Republicans in the bathroom
int democratsInBathroom = 0;    // Count of Democrats in the bathroom
int currentParty = 0;           // 0 for none, 1 for Republicans, 2 for Democrats


// Republican thread calls this function before entering the bathroom
void republicanWantsToEnter(int id) {
    unique_lock<mutex> lock(bathroomMutex); 
    // wait until bathroom is either free (no party is inside) or being used only by republicans, and not full 
    cv.wait(lock, [&](){
        return ( currentParty == 0 || (currentParty == 1 && republicansInBathroom < MAX_PEOPLE_IN_BATHROOM) );
    });
    // republicans take control of the bathroom if it's free
    if ( currentParty == 0) {
        currentParty = 1; 
    }
    // increment counter for republicans
    republicansInBathroom++; 
    cout << "Republican " << id << " is using the bathroom.\n";
}

// Republican thread calls this function before leaving the bathroom
void republicanLeaves(int id ) {
    unique_lock<mutex> lock(bathroomMutex);
    republicansInBathroom--;
    cout << "Republican " << id << " leaves the bathroom.\n";
    // If there are no republican remaining in the bathroom, set the currentParty status to 0
    if (republicansInBathroom == 0) {
        currentParty = 0 ; 
    }
    // notify other waiting threads
    cv.notify_all(); 
}

// Democrat thread calls this function before entering the bathroom
void democratWantsToEnter(int id) {
    unique_lock<mutex> lock(bathroomMutex);
    cv.wait(lock, [&](){
        return (currentParty == 0 || (currentParty == 2 && democratsInBathroom < MAX_PEOPLE_IN_BATHROOM ));
    });
    // Democrats take control of the bathroom if it's free
    if ( currentParty == 0) {
        currentParty = 2; 
    }
    // Increment counters for democrats
    democratsInBathroom++;
    cout << "Democrat " << id << " is using the bathroom.\n";
}

// Democrat thread calls this function before leaving the bathroom
void democratLeaves(int id) {
    unique_lock<mutex> lock(bathroomMutex);
    cout << "Democrat " << id << " leaves the bathroom.\n";
    democratsInBathroom--;
    // If there are no democrat remaining in the bathroom, set the currentParty status to 0
    if( democratsInBathroom == 0) {
        currentParty = 0 ;
    }
    // Notify other waiting threads
    cv.notify_all();
}

// Simulate the Republicans and Democrats using the bathroom
void republicanThread(int id) {
    republicanWantsToEnter(id);
    this_thread::sleep_for(chrono::seconds(1)); // Simulate bathroom usage
    republicanLeaves(id);
}

void democratThread(int id) {
    democratWantsToEnter(id);
    this_thread::sleep_for(chrono::seconds(1)); // Simulate bathroom usage
    democratLeaves(id);
}

int main() {

    thread People[12] = {
        thread(republicanThread, 1),
        thread(democratThread, 1),
        thread(republicanThread,2),
        thread(democratThread, 2),
        thread(democratThread, 3),
        thread(republicanThread,3),
        thread(democratThread, 4),
        thread(democratThread, 5),
        thread(republicanThread,4),
        thread(democratThread, 6),
    };
    this_thread::sleep_for(chrono::seconds(5));

    People[10] =  thread(republicanThread, 5);
    People[11] = thread(republicanThread, 6);

    for(int i = 0 ; i < 12 ; ++i ) {
        People[i].join();
    }

    return 0;
}
