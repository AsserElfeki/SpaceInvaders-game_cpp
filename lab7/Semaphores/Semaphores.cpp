#include<iostream>
#include<barrier>
#include <semaphore>
#include <thread>
#include <random>
#include <chrono>


void log(std::string msg) {std::cout << msg << std::endl;}


/*1. Create functions printA(), printB() and printC() that repeatedly print a character
‘A’, ‘B’ or ‘C’ in a for loop. Run those function in parallel and using semaphores, synchronize them,
so that the printed output will have a pattern like ACBBCACBBC… The functions can finish execution after
the pattern was printed at least 3 times (make sure all threads exit loop).​
*/
std::binary_semaphore sem_A{ 1 }; //controller
std::binary_semaphore sem_B{ 0 };
std::binary_semaphore sem_C{ 0 };

void printA() 
{
	for (int i = 0; i < 6; i++) 
	{
		sem_A.acquire();
		std::cout << "A";
		sem_C.release();
		sem_A.acquire();
		sem_B.release();
		sem_A.acquire();
		sem_C.release();
	}
}

void printB() 
{
	for (int i = 0; i < 6; i++) 
	{
		sem_B.acquire();
		std::cout << "BB";
		sem_A.release();
	}
}
void printC() 
{
	for (int i = 0; i < 12; i++) 
	{
		sem_C.acquire();
		std::cout << "C";
		sem_A.release();
	}
}

/*2. Declare a global array “int buffer[4]”.
Create and execute in parallel functions producer() and consumer().
Producer fills the buffer with numbers from 0 to 29 and gets blocked if there’s no space left in the buffer.
Consumer takes the oldest value from the buffer and prints it, it gets blocked if there’s no data left in the buffer.​*/
std::counting_semaphore<4> semFree{ 4 }, semOccupied{ 0 };
std::binary_semaphore semaphoreBuffer{ 1 };
int buffer[4];

void producer() 
{
	for (int i = 0; i < 30; i++) 
	{
		semFree.acquire();
		semaphoreBuffer.acquire();
		buffer[i % 4] = i;
		semaphoreBuffer.release();
		semOccupied.release();
	}
}
void consumer() 
{
	for (int i = 0; i < 30; i++) 
	{
		semOccupied.acquire();
		semaphoreBuffer.acquire();
		std::cout << buffer[i % 4] << ' ';
		semaphoreBuffer.release();
		semFree.release();
	}
}

/*3. Declare 2 global arrays – “int calories[5]” and “binary_semaphore fork[5]”.
Create function philosopher(int i) and run it on5 threads in parallel.
The i-th philosopher repeatedly tries to increment calories[i], but can only do it if it has both forks [i] and [(i+1)%5] acquired.
All threads finish execution when every element in calories reaches 10000. Make sure that no deadlock can occur.​
*/
int calories[5] = { 0,0,0,0,0 };
std::binary_semaphore fork[5] = { std::binary_semaphore(1), std::binary_semaphore(1), std::binary_semaphore(1), std::binary_semaphore(1), std::binary_semaphore(1) };


void philosopher(int i) 
{
	int left, right;

	left = i;
	right = (i + 1) % 5;

	while (calories[0] < 10000 || calories[1] < 10000 || calories[2] < 10000 || calories[3] < 10000 || calories[4] < 10000)
	{
		if (fork[left].try_acquire()) 
		{
			if (fork[right].try_acquire()) 
			{
				calories[i] += 1; 
				fork[right].release();
			}
			fork[left].release(); //failsafe to prevent deadlock
		}
	}
}


/*4. Create a function that will create x elements (increment a local counter in a loop x times) and run it on 10 threads.
After 10 elements created, use  them (subtract 10 from the counter).
Every time elements are used, print a message which time it is being used.*/
int RandomNumber()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist100(1, 100);

	return dist100(rng);
}

std::atomic<int> counter(0);
int substracting_counter = 0;

void use() noexcept 
{
	counter -= 10;
	substracting_counter++;
	if (substracting_counter > 3)
		std::cout << "Substracting from the counter for the " << substracting_counter << "th time \n";
	else if (substracting_counter == 3)
		log("Substracting from the counter for the third time");
	else if (substracting_counter == 2)
		log("Substracting from the counter for the second time");
	else
		log("Substracting from the counter for the first time");


}

std::barrier bar(10, use);

void increment(int x) 
{
	for (int i = 0; i < x; i++) {
		counter++;
		bar.arrive_and_wait();
	}
}

std::vector<int> vec;
std::barrier bar2(10);
std::binary_semaphore stack_semaphore{ 1 };
std::atomic<int> sum(0);


void  roll() {
	for (int i = 0; i < 10; i++)
	{
		stack_semaphore.acquire();
		int randNumTmp = RandomNumber();

		if (std::find(vec.begin(), vec.end(), randNumTmp) != vec.end()) {
			i--;
		}
		else {
			vec.push_back(randNumTmp);
		}
		stack_semaphore.release();

	}
	bar2.arrive_and_wait();
	for (int i = 0; i < 10; i++)
	{
		stack_semaphore.acquire();
		sum += vec[vec.size() - 1];
		vec.pop_back();
		stack_semaphore.release();
	}
}



using namespace std::chrono_literals;

int main() {
	log("Task 1:");

	std::jthread thrA(printA);
	std::jthread thrB(printB);
	std::jthread thrC(printC);
	/*thrA.join();
	thrB.join();
	thrC.join();*/
	std::this_thread::sleep_for(100ms); 

	log("");
	log("");

	/*#######################################*/

	log("Task 2:");

	std::thread thrPro(producer);
	std::thread thrCon(consumer);
	thrPro.join();
	thrCon.join();
	log("");
	log("");

	/*#######################################*/

	log("Task 3:");

	std::thread philosopher1(philosopher, 0);
	std::thread philosopher2(philosopher, 1);
	std::thread philosopher3(philosopher, 2);
	std::thread philosopher4(philosopher, 3);
	std::thread philosopher5(philosopher, 4);
	philosopher1.join();
	philosopher2.join();
	philosopher3.join();
	philosopher4.join();
	philosopher5.join();

	log("Task completed");
	log("");


	/*#######################################*/

	log("Task 4:");
	std::vector<std::thread> threads;

	for (int i = 0; i < 10; i++)
		threads.push_back(std::thread(increment, 15));

	for (auto& th : threads)
		th.join();
	log("");

	/*#######################################*/
	/*5. Create a vector of integers.
Create a function that will roll 10 random original numbers (from 1 to 100) and add them to the vector and run it on 10 threads.
After adding 100 numbers, in the next phase, the function should sum 10 elements and remove them from the vector.
After that, print the sum (it should be 5050 and the vector should be empty so it could be used once more).
*/
	log("Task 5:");
	std::vector<std::thread> threads2;

	for (int i = 0; i < 10; i++)
		threads2.push_back(std::thread(roll));
	for (auto& th : threads2)
		th.join();

	std::cout << "All threads done and the sum is  " << sum << std::endl;

}