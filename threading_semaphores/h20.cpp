class H2O {
public:
    binary_semaphore release_oxygyen{0};
    counting_semaphore<2> release_hydrogen{2};
    int hydrogen_count ;
    H2O() {
        hydrogen_count = 0 ; 
    }

    void hydrogen(function<void()> releaseHydrogen) {
        
        release_hydrogen.acquire();
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();
        hydrogen_count++; 
        if ( hydrogen_count == 2) {
            release_oxygyen.release();
        }
    }

    void oxygen(function<void()> releaseOxygen) {
        
        release_oxygyen.acquire();
        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
        hydrogen_count = 0; 
        release_hydrogen.release();
        release_hydrogen.release();
    }
};