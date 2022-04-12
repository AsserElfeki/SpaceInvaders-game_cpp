#include <future>
#include <iostream>
#include <random>
#include <array>
#include <chrono>

//#include <thread>
#define ARR_SZ 20

int rand_num() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(0, 100);
    return distribution(rng);
};


int log(std::string msg) {
    std::cout << msg << std::endl;
}

int increment(int n){
    return n + 1;
}

int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}


int main() {

    log("Task1: ");
    auto T1 = std::async(std::launch::async, increment, 5);
    std::cout << T1.get() << std::endl;
    log("");

    log("Task2: ");
    auto gen1 = []() {
        int res = 0;

        while (res != 50) {
            res = rand_num();
            //std::cout << "gen1 trial, rand_num = " << res <<std::endl;
        }
    };

    auto gen2 = []() {
        int res = 0;

        while (res != 50) {
            res = rand_num();
            //std::cout << "gen2 trial, rand_num = " << res <<std::endl;
        }
    };

    auto T2_1 = std::async(std::launch::async, gen1);
    auto T2_2 = std::async(std::launch::async, gen2);
    log("");


    log("Task3: ");
    std::array<int, ARR_SZ> arr1;
    std::array<int, ARR_SZ> arr2;


    auto asyncAssign = [&arr1]() {
        auto fib_async1 = std::async(std::launch::async, [&]() {
            for (int i = 0; i < ARR_SZ / 2; i++) {
                arr1[i] = fibonacci(i);
            }
        });

        auto fib_async2 = std::async(std::launch::async, [&]() {
            for (int i = ARR_SZ / 2; i < ARR_SZ; i++) {
                arr1[i] = fibonacci(i);
            }
        });
    };

    auto seqAssign = [&arr2]() {
        for (int i = 0; i < ARR_SZ; i++) {
            arr2[i] = fibonacci(i);
        }
    };

    auto f2 = std::async(std::launch::async, asyncAssign);
    auto f1 = std::async(std::launch::async, seqAssign);

    for (int i = 0; i < ARR_SZ; i++) {
        //log("abc");
        std::cout << arr1[i] << " , " << arr2[2] << std::endl;
    }
    log("");


    log("Task4: ");
    std::future_status seqAssignStatus;
    auto seqAssignStartTime = std::chrono::system_clock::now();
    

    log("");


    return 0;
}
