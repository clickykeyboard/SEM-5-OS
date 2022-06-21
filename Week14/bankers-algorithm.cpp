#include <iostream>
using namespace std;

bool isExecutable(int *need, int *available, int resources) {
	for (int i = 0; i < resources; i++)
		if (need[i] > available[i])
			return false;
	
	return true;
}

bool isProcessExecuted(int processNumber, int *processesExecuted, int totalProcessesExecuted) {
	for (int i = 0; i < totalProcessesExecuted; i++)
		if (processesExecuted[i] == processNumber)
			return true;

	return false;
}

int main() {
	int resources,
		  processes;
	
	cout << "Enter the number of resources: ";
	cin >> resources;
	
	cout << "Enter the number of processes: ";
	cin >> processes;
	
	int allocation
		[processes][resources];
	
	int max
		[processes][resources];

	int need
		[processes][resources];
	
	int available[resources];
	
	int totalInstances[resources] = { 0, 0, 0 };

  cout << "Enter allocation for processes: " << endl;
	for (int processNumber = 0; processNumber < processes; processNumber++) {
		cout << "P" << processNumber << endl;
		
	  for (int resourceNumber = 0; resourceNumber < resources; resourceNumber++) {
	      cin >> allocation[processNumber][resourceNumber];
	      totalInstances[resourceNumber] += allocation[processNumber][resourceNumber];
	  }
  }
  
  cout << "Enter maximum for processes: " << endl;
	for (int processNumber = 0; processNumber < processes; processNumber++) {
		cout << "P" << processNumber << endl;
		
	  for (int resourceNumber = 0; resourceNumber < resources; resourceNumber++) {
	      cin >> max[processNumber][resourceNumber];
	      
	      /* Also determine need */
	      need[processNumber][resourceNumber] = 
	      	max[processNumber][resourceNumber] - allocation[processNumber][resourceNumber];
	  }
  }
  
  cout << "Enter availabe instances for resources: " << endl;
  for (int resourceNumber = 0; resourceNumber < resources; resourceNumber++) {
		cin >> available[resourceNumber];
		totalInstances[resourceNumber] += available[resourceNumber];
	}
	
	/* Banker's Algorithm */
	int totalProcessesExecuted = 0;
	int processesExecuted[processes] = { 0 };
	
	bool canContinue = true;
	while (canContinue) {
		canContinue = false;

		for (int i = 0; i < processes; i++) {
			/* If process is already executed, move and check next */
			if (isProcessExecuted(i, processesExecuted, totalProcessesExecuted))
				continue;

			/* If process cannot be executed, move on and check other processes */
			if (!isExecutable(need[i], available, resources))
				continue;
				
			processesExecuted[totalProcessesExecuted] = i;
			totalProcessesExecuted += 1;
			/* Add allocation for process just executed */
			for (int j = 0; j < resources; j++)
				available[j] += allocation[i][j];
			
			/* If the available has increased, system has the capability
			   to check further processes if their need can be fulfilled
			*/
			canContinue = true;
		}
	}
	
	if (totalProcessesExecuted == processes) {
		cout << "The system is in safe state" << endl;
		for (int i = 0; i < processes; i++)
			cout << "P" << processesExecuted[i] << " ";
	}
	else
		cout << "The system is in unsafe state" << endl;
		
}
