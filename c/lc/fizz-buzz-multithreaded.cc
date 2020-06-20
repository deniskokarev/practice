// https://leetcode.com/problems/fizz-buzz-multithreaded
enum {N, F, B, FB, TSZ};
constexpr int CSZ = 15;
constexpr int CYCLE[CSZ] {FB, N, N, F, N, B, F, N, N, F, B, N, F, N, N};

class FizzBuzz {
    volatile int i;
    const int upto;
    mutex mtx;
    condition_variable cv[TSZ];

    void run_all(int me, function<void(int)> print) {
        unique_lock<mutex> lck(mtx);
        while (i<=upto) {
            while (i<=upto && CYCLE[i%CSZ] != me)
                cv[me].wait(lck);
            if (i<=upto)
                print(i);
            i++;
            cv[CYCLE[i%CSZ]].notify_one();
        }
        for (auto &c:cv)
            c.notify_one();
    }
public:
    FizzBuzz(int n):upto(n),i(1) {
    }
    // printFizz() outputs "fizz".
    void fizz(function<void()> print) {
        run_all(F, [print](int){print();});
    }
    // printBuzz() outputs "buzz".
    void buzz(function<void()> print) {
        run_all(B, [print](int){print();});
    }
    // printFizzBuzz() outputs "fizzbuzz".
    void fizzbuzz(function<void()> print) {
        run_all(FB, [print](int){print();});
    }
    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> print) {
        run_all(N, print);
    }
};
