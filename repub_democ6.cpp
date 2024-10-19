#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex bathroomMutex;  // whenever someone wants to use the bathroom, he needs to acquire this mutex first 
// it controls the access to the bathroom
condition_variable cv;   // Condition variable to wait for access to a party ( democrat/ republican)

int republicansInBathroom = 0;  // Count of Republicans in the bathroom
int democratsInBathroom = 0;    // Count of Democrats in the bathroom
int currentParty = 0;           // 0 for none, 1 for Republicans, 2 for Democrats
int peopleInBathroom =0   ;      // Total no of people in the bathroom 

const int MAX_PEOPLE_IN_BATHROOM = 3;  // Max number of people allowed in the bathroom


void republicanWantsToEnter(int id) {
    unique_lock<mutex> lock(bathroomMutex); 
    // wait until bathroom is either free( no party is inside) or being used only by republicans, and not full 
    cv.wait(lock, [&](){
        return ( currentParty == 0 || (currentParty == 1 && republicansInBathroom < MAX_PEOPLE_IN_BATHROOM) );
    });

    // republicans take control of the bathroom if it's free
    if ( currentParty == 0) {
        currentParty = 1; 
    }

    // increment counter for republicans and total people
    republicansInBathroom++; 
    // peopleInBathroom++; 
    cout << "Republican " << id << " is using the bathroom.\n";
}

void republicanLeaves(int id ) {
    unique_lock<mutex> lock(bathroomMutex);
    republicansInBathroom--;
    // peopleInBathroom--;
    cout << "Republican " << id << " leaves the bathroom.\n";

    if (republicansInBathroom == 0) {
        currentParty = 0 ; 
    }
    // notify other waiting threads
    cv.notify_all(); 
}

void democratWantsToEnter(int id) {
    unique_lock<mutex> lock(bathroomMutex);
    cv.wait(lock, [&](){
        return (currentParty == 0 || (currentParty == 2 && democratsInBathroom < MAX_PEOPLE_IN_BATHROOM ));
    });

    // Democrats take control of the bathroom if it's free
    if ( currentParty == 0) {
        currentParty = 2; 
    }

    // Increment counters for democrats and total people
    democratsInBathroom++;
    // peopleInBathroom++;
    cout << "Democrat " << id << " is using the bathroom.\n";

}

void democratLeaves(int id) {
    unique_lock<mutex> lock(bathroomMutex);

    cout << "Democrat " << id << " leaves the bathroom.\n";
    // peopleInBathroom--;
    democratsInBathroom--;
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

    // Create threads for Republicans and Democrats
    // thread republicans[] = {
    //     thread(republicanThread, 1),
    //     thread(republicanThread, 2),
    //     thread(republicanThread, 3),
    //     thread(republicanThread, 4)
    // };

    // thread democrats[] = {
    //     thread(democratThread, 1),
    //     thread(democratThread, 2),
    //     thread(democratThread, 3),
    //     thread(democratThread, 4)
    // };

    // // Join threads
    // for (int i = 0; i < 4; i++) {
    //     republicans[i].join();
    //     democrats[i].join();
    // }

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
