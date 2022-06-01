#include <iostream>
using namespace std;

int getProcessWithLowestPriority(int *priority, int processes) {
	int minimumPriorityProcessNumber = 0;
	for (int i = 1; i < processes; i++)
		if (priority[i] <= priority[minimumPriorityProcessNumber])
			minimumPriorityProcessNumber = i;

	return minimumPriorityProcessNumber;
}

int main() {
	
	int processes;
	cout << "Enter the number of processes: ";
	cin >> processes;
	
	
	int burstTime[processes];
	for (int i = 0; i < processes; i++ ) {
		cout << "Enter burst time for process " << i << ": ";
		cin >> burstTime[i];
	}
	
	int priority[processes];
	for (int i = 0; i < processes; i++ ) {
		cout << "Enter priority for process " << i << ": ";
		cin >> priority[i];
	}
	
	int ganttChart[processes];
	int completionTime[processes];
	int completionSum = 0;;
	
	for (int i = 0; i < processes; i++) {
		int minimumPriorityProcessNumber = getProcessWithLowestPriority(priority, processes);
		ganttChart[i] = minimumPriorityProcessNumber;
		
		/* Set priority number to a high number so it does not count next time */
		priority[minimumPriorityProcessNumber] = 9999;
		
		completionSum += burstTime[minimumPriorityProcessNumber];
		completionTime[minimumPriorityProcessNumber] = completionSum;
	}
	
	/* Printing gantt chart */
	for (int i = 0; i < processes; i++) {
		cout << "|P" << ganttChart[i] << '|';
	}
	
	int turnaroundTime[processes] = {0}; /* Turnaround time (CT - AT) */
  int waitingTime[processes] = {0}; /* Waiting time (TAT - BT) */
  for (int i = 0; i < processes; i++) {
  	turnaroundTime[i] = completionTime[i] - 0;
  	waitingTime[i] = turnaroundTime[i] - burstTime[i];
  }
  
  cout << endl << "P\t" << "AT\t" << "BT\t" << "CT\t" << "TAT\t" << "WT" << endl;
  for (int i = 0; i < processes; i++) {
    cout << "P" << i << "\t"
      << '0' << "\t"
      << burstTime[i] << "\t"
      << completionTime[i] << "\t"
      << turnaroundTime[i] << "\t"
      << waitingTime[i] << endl;
  }
}
