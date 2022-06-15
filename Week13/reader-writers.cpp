#include <iostream>
using namespace std;

#define READ 1
#define WRITE 2
#define MUTEX 3

/* 
		We will use "readers" value to increment
		when a reader process is reading, or decrement when it stops
		reading
*/
int readers = 0;

struct Semaphore {
	int mutex;
	int writer;
} semaphore;

/* Declare functions */
void wait(int operation) {
	switch (operation) {
		case WRITE:
			cout << "\t" << "Checking if another process writing..." << endl;
			if (semaphore.writer == 1) {
				cout << "\t" << "Another process is currently writing... waiting for process to stop writing" << endl;
				
				/* This while look will stop execution till writer becomes 0 (writer stops writing) */
				while (semaphore.writer == 1);
			}
			
			semaphore.writer = 1;
			break;
	
		case MUTEX:
			cout << "\t" << "Checking if locked..." << endl;
			if (semaphore.mutex == 1) {
				cout << "\t" << "Another process is currently holding lock.. waiting for process to release" << endl;
				
				/* This while look will stop execution till mutex becomes 0 (lock is released) */
				while (semaphore.mutex == 1);
			}
			
			/* If not locked by other process, set lock */
			semaphore.mutex = 1;
	}
}
void signal(int operation) {
	switch (operation) {
		case WRITE:
			/* If a process is writing and it signals write, then release writer lock */
			semaphore.writer = 0;
			break;
		
		case MUTEX:
			/* If a process is currently holding lock to increment "readers", release lock */
			semaphore.mutex = 0;
			break;
	}
}

void Read();
void Write();

int main() {
	
	/* Make semaphore variable "semaphore" */
	Semaphore semaphore;
	
	/* Set initial values for the semaphore */
	semaphore.mutex = 0; /* Initial value for lock is 0 */
	semaphore.writer = 0; /* Initial value for writer is 0 */
	
	int choice = 0;
	while (true) {
		cout << "Read [1] / Write [2]: ";
		cin >> choice;
		
		switch (choice) {
			case READ:
				cout << "-------|" << endl;
				Read();
				cout << "-------|" << endl;
				break;
			
			case WRITE:
				cout << "-------|" << endl;
				Write();
				cout << "-------|" << endl;
				break;
			
			default:
				cout << "Enter a valid option" << endl; 
		}
	}
}

void Write() {
	/* Wait if any other writer is writing or reader is reading */
	wait(WRITE);
	
	cout << "\t" << "[Writer is writing...]" << endl;
	
	/* Release writer lock */
	signal(WRITE);
}

void Read() {
	/* Wait and acquire lock to increment "readers" value */
	wait(MUTEX);
	readers += 1;
	
	/* Check if at least 1 reader then that means there can be no writer writing, so lock writer */
	if (readers == 1)
		wait(WRITE); /* Locking writer from writing because at least one reader is reading */
	
	signal(MUTEX); /* Allow other readers to enter */
	cout << "\t" << "[Reader is reading...]" << endl;
	/* The reader is done reading and about to exit, so we lock mutex and decrement value */
	wait(MUTEX);
	readers -= 1;
	signal(MUTEX); /* Release lock */
	
	/* If there are 0 readers then writer can be allowed to write again, so release writer lock */
	if (readers == 0)
		signal(WRITE);
}
