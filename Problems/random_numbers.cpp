/*
Implement a data structure to generate random numbers between 1 to N without repeating numbers in a window until all numbers are exhausted.


We will maintain a count of elements visited in a window and that cnt will help us to pick random number that hasn't been visited yet.
 once a number is visited we will move it to the back of the array and update the cnt.

Ex: n= 3
1st run: 1,2,3 , cnt =3, random number idx= rand() %cnt , => 1 (assuming), move the visited number at the back of the 
array and fill this position with unvisited number from front and decrement the cnt.
2nd run 1,3,2, cnt =2 and so on.
*/

// int ar(n) // filled with 1..n
// int cnt =n;

// int get_random(int n)
// {
//     int rand_idx = rand()%cnt;
//     int rand_no=ar[rand_idx];

//     ar.push_back(rand_no); // move back now it won't come in current window
//     ar[rand_idx] = ar[0]; // filling that position with unvisited number from front;
//     ar.pop_front(); // removing the duplicate front number;
//     cnt--; // decrementing random window

//     if(cnt==0) // first window complete, reintiating for new window
//     {
//         cnt=n;
//     }
//     return rand_no;
// }


#include<iostream>
#include<vector>
#include<random>

using namespace std; 
class RandomGen{
    vector<int>arr; 
    int n;
    int curSize ; 
    public:
    RandomGen(int n): n(n){
        curSize = n ; 
        arr.reserve(n);
        for(int i = 0 ; i < n ; ++i) {
            arr.push_back(i + 1);
        }
    }
    void reset() {
        // cout << "Resetting " << endl; 
        curSize = n ; 
    }

    int generate() {
        int randIndex = rand() % curSize; 
        int randNo = arr[randIndex];
        swap(arr[randIndex], arr[curSize - 1]);
        curSize-- ; 
        if ( curSize == 0) {
            reset(); 
        }
        return randNo; 
    }

};

int main () {


    RandomGen randomGen(10);

    cout << randomGen.generate() << endl; 
    cout << randomGen.generate() << endl; 
    cout << randomGen.generate() << endl; 
    cout << randomGen.generate() << endl; 
    cout << randomGen.generate() << endl; 
    cout << randomGen.generate() << endl; 
    cout << randomGen.generate() << endl; 
    cout << randomGen.generate() << endl; 
    cout << randomGen.generate() << endl; 
    cout << randomGen.generate() << endl; 
    cout << randomGen.generate() << endl; 
    cout << randomGen.generate() << endl; 
    cout << randomGen.generate() << endl; 

    return 0; 
}