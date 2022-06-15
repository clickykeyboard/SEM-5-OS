#include <stdio.h>

#define PRODUCER 1
#define CONSUMER 2

#define BUFFER_SIZE 10
#define MUTEX 1
#define EMPTY 2
#define FULL 3

struct Semaphore {
	int mutex;
	int full;
	int empty;
} semaphore;

void wait(int operation) {
	switch (operation) {
		case EMPTY:
			printf("\tChecking if empty...\n");
			
			if (semaphore.empty == 0) {
				printf("\tBuffer is empty... waiting for producer process to produce...\n");
				while (semaphore.empty == 0);
			}
			
			semaphore.empty += 1;
			break;
		
		case FULL:
			printf("\tChecking if full...\n");
			
			if (semaphore.full >= BUFFER_SIZE) {
				printf("\tBuffer is full... waiting for consumer process to consume...\n");
				while (semaphore.full >= BUFFER_SIZE);
			}
			
			semaphore.full += 1;
			break;
			
		case MUTEX:
			printf("\tChecking if locked...\n");
			
			if (semaphore.mutex == 1) {
				printf("\tAnother process is already holding lock.. waiting for process to release...\n");
				while (semaphore.mutex == 1);
			}
			
			semaphore.mutex = 1;
	}
}

void signal(int operation) {
	switch (operation) {
		case EMPTY:
			semaphore.empty -= 1;
			break;
		
		case FULL:
			printf("\tDecrementing full... \n");
			semaphore.full -= 1;
			break; 
		
		case MUTEX:
			printf("\tReleasing lock... \n");
			semaphore.mutex = 0;
	}
}

void Producer();
void Consumer();

int main() {
	
	struct Semaphore semaphore;
	semaphore.mutex = 0;
	semaphore.full = 0;
	semaphore.empty = BUFFER_SIZE;
	
	int choice = 0;
	while (1) {
		printf("Produce [1] / Consume [2]: ");
		scanf("%d", &choice);
		
		switch (choice) {
			/* Producer */
			case PRODUCER:
				printf("------|\n");
				Producer();
				printf("------|\n");
				break;
			
			/* Consumer */	
			case CONSUMER:
				printf("------|\n");
				Consumer();
				printf("------|\n");
				break;
			
			default:
				printf("Enter a valid option\n");
		}
	
	}	
}

void Producer() {
	wait(MUTEX);
	wait(FULL);
				
	printf("\t[ Producer producing ]...\n");
				
	signal(MUTEX);
	signal(EMPTY);
}

void Consumer() {
	wait(MUTEX);
	wait(EMPTY);
				
	printf("\t[ Consumer consuming ]...\n");
				
	signal(MUTEX);
	signal(FULL);
}
