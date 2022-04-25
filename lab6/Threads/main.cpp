#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

void log(std::string msg) {
    std::cout << msg << std::endl;
}
using namespace std::literals::chrono_literals;

std::atomic<bool> ready (false);

void countmil(int id)
{
    while (!ready) {
        std::this_thread::yield();
    }

    for (int i=0; i<1000000; i++)
    {
        std::cout<< i<< ' ';
    }
    std::cout << id << ' ';
}


std::mutex vectLock;
std::vector<unsigned int> primeVec;

void findPrimes(int start, int end)
{
    for ( int x = start; x <= end; x += 2)
    {
        for ( int y = 2; y < x; y++)
        {
            if ((x % y) == 0)
                break;

            else if ((y + 1) == x)
            {
                std::lock_guard<std::mutex> lock(vectLock);
                primeVec.push_back(x);
            }
        }
    }
}

void findPrimesWithThreads(int start, int end, int numThreads)
{
     std::vector<std::jthread> threadVect;
     int threadSpread = end / numThreads;
     int newEnd = start + threadSpread - 1;

    for ( int x = 0; x < numThreads; x++)
    {
        threadVect.emplace_back(findPrimes, start, newEnd);
        start += threadSpread;
        newEnd += threadSpread;
    }
}


int main()
{
    log ("-----Task 1&2-----");
    int counter = 0;

    std::mutex m;

    //lambda func
    auto incr = [&counter, &m]()
            {
        m.lock();
        counter++;
        m.unlock();
        };

    std::vector<std::thread> pool; //thread pool
    //pool.reserve(1000);
    for (int i = 0; i<50; i++)
    {
        pool.emplace_back(std::thread (incr));
    }

    for (int i = 0; i<50; i++)
    {
        pool[i].join();
    }
    std::cout<<counter<<std::endl;

    log("-----End of Task 1&2-----");

    log ("-----Task 3-----");
    std::thread threads[10];

    for (int i=0; i<10; i++)
    {
        threads[i]=std::thread(countmil,i);
    }
    ready = true;
    for (auto& thr : threads) thr.join();

    log(" ");
    log("-----End of Task 3-----");

    log ("-----Task 4-----");

    int startTime = clock();
    // findPrimesWithThreads(1, 1000000, 1);
    int endTime = clock();

    // for (auto &n : primeVec) std::cout << n << std::endl;
    std::cout << "Execution time (one thread): "
              << (endTime - startTime) / double(CLOCKS_PER_SEC) << std::endl;

    primeVec.clear();
    startTime = clock();
    findPrimesWithThreads(1, 1000000, 7);
    endTime = clock();

    std::cout << "Execution time (more threads): "
              << (endTime - startTime) / double(CLOCKS_PER_SEC) << std::endl;

    log("-----End of Task 4-----");

    return 0;
}

