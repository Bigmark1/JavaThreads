#include<iostream>
#include<thread>
#include<string>
#include<mutex>





using namespace std;
std::condition_variable wait;




struct sharedData { 
	
	unsigned short int count_function; // shared data. short int is bestfor our calculations 
	int getGuard() {
		return count_function;
	}
	};

struct countMutex {
	
	sharedData safeGaurd;
	std::mutex m;
	
};

countMutex protect;

void countDown() { // Thread1 counts down to 0; 
	
	std::unique_lock<mutex> key(protect.m);
	
	wait.wait(key); //waits for t1 to finish executing. 
	
	int value = protect.safeGaurd.getGuard();

	for (int i = value; i >= 0; i--) {
		protect.safeGaurd.count_function--;
		std::cout << protect.safeGaurd.count_function << " ";

		std::this_thread::sleep_for(chrono::milliseconds(500));
		
	} 
	key.unlock(); 
	 
}
void countUp() { // Thread2 counts up to 20
	
	std::unique_lock<mutex> locker(protect.m);

	for (int i = 0; i <= 20; i++) {
		protect.safeGaurd.count_function++;

		std::cout << protect.safeGaurd.count_function << " ";
		
		std::this_thread::sleep_for(chrono::milliseconds(500));
	}
	std::cout << '\n';
	locker.unlock(); 
	wait.notify_one(); // notifies t2 when its done; 
}

int main() {




	std::thread t1(countUp);
	std::thread t2(countDown);
	t1.join();
	t2.join();

	
		
	std::cout << " \n Both threads have completed execution" << endl;
	
	
	
	
	return 0; 
}