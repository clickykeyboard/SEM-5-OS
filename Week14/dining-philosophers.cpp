#include <iostream>
using namespace std;

#define CHOPSTICKS 5

struct Semaphore {
	int chopsticks[CHOPSTICKS];
} semaphore;

void wait(int chopstick) {
	if (semaphore.chopsticks[chopstick] == 0) {
		cout << "Chopstick already in use" << endl;
		while (semaphore.chopsticks[chopstick] == 0);
	}
	
	semaphore.chopsticks[chopstick] = 0;
}

void signal(int chopstick) {
	semaphore.chopsticks[chopstick] = 1;
}

int main() {
 	for (int i = 0; i < CHOPSTICKS; i++)
 		semaphore.chopsticks[i] = 1;
	
	for (int i = 0; i < CHOPSTICKS; i++) {
		wait(i);
		wait((i + 1) % CHOPSTICKS);
		
		cout << "Philosopher eating with chopstick " 
			<< i << " and chopstick " << (i + 1) % CHOPSTICKS << endl;
		
		signal(i);
		signal((i + 1) % CHOPSTICKS);
	}
}
