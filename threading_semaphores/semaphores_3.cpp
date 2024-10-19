class Foo {
public:
    binary_semaphore firstJobDone{0};
    binary_semaphore secondJobDone{0};

    Foo() {
    }

    void first(function<void()> printFirst) {
        
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        // it will increase firstJobDone by 1
        firstJobDone.release();
    }

    void second(function<void()> printSecond) {

        firstJobDone.acquire();
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        // it will increase secondJobDone by 1
        secondJobDone.release();
    }

    void third(function<void()> printThird) {
        
        secondJobDone.acquire();
        // printThird() outputs "third". Do not change or remove this line.
        printThird();

    }
};