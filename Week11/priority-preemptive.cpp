#include <iostream>
#include <set>
#include <iterator>

using namespace std;

set<int> readyQueue;
int totalProcesses;
int currentCPUTime = 0;

void determineReadyQueue(int *arrivalTime) {
	for (int i = 0; i < totalProcesses; i++) {
		if (readyQueue.contains(i))
			continue;
		
		if (arrivalTime[i] <= currentCPUTime)
			readyQueue.insert(i); 
	}
}

int getHighestPriority(int *priority) {
	set<int>::iterator process;
	
  int minimumProcessNumber = *readyQueue.begin();
  for (process = ++readyQueue.begin(); process != readyQueue.end(); process++) {
    if (priority[*process] <= priority[minimumProcessNumber])
      minimumProcessNumber = *process;
  }
	
  return minimumProcessNumber;
}


int main() {
	cout << "Enter number of processes: ";
	cin >> totalProcesses;
	
	int arrivalTime[totalProcesses];
	int completedArrivalTime[totalProcesses];
	int completionTime[totalProcesses];
	
	for (int i = 0; i < totalProcesses; i++) {
		cout << "Enter arrival time for process " << i << ": ";
		cin >> arrivalTime[i];
		completedArrivalTime[i] = arrivalTime[i];
	}
	
	int burstTime[totalProcesses];
	int completedBurstTime[totalProcesses];
	for (int i = 0; i < totalProcesses; i++) {
		cout << "Enter burst time for process " << i << ": ";
		cin >> burstTime[i];
		completedBurstTime[i] = burstTime[i];
	}
	
	int priority[totalProcesses];
	for (int i = 0; i < totalProcesses; i++) {
		cout << "Enter priority for process " << i << ": ";
		cin >> priority[i];
	}
	
	int completedProcesses = 0;
	while (completedProcesses != totalProcesses) {
		determineReadyQueue(arrivalTime);
		
		int process = getHighestPriority(priority);
		
		/* Gantt chart */
		cout << "|P" << process << "|";
		
		/* Execute process for one burst time */
		burstTime[process] = burstTime[process] - 1;
		if (burstTime[process] == 0) {
			completionTime[process] = currentCPUTime + 1; // We add 1 here because gantt chart starts from 0

      burstTime[process] = 9999;
      arrivalTime[process] = 9999;
      priority[process] = 9999;

      readyQueue.erase(process);
      
      completedProcesses++;	
		}
		
		currentCPUTime += 1;
	}
	
  int turnaroundTime[totalProcesses] = {0}; /* Turnaround time (CT - AT) */
  int waitingTime[totalProcesses] = {0}; /* Waiting time (TAT - BT) */
  for (int i = 0; i < totalProcesses; i++) {
    turnaroundTime[i] = completionTime[i] - completedArrivalTime[i];
    waitingTime[i] = turnaroundTime[i] - completedBurstTime[i];
  }

  cout << endl << "P\t" << "AT\t" << "BT\t" << "CT\t" << "TAT\t" << "WT" << endl;
  for (int i = 0; i < totalProcesses; i++) {
    cout << "P" << i << "\t"
    << completedArrivalTime[i] << "\t"
    << completedBurstTime[i] << "\t"
    << completionTime[i] << "\t"
    << turnaroundTime[i] << "\t"
    << waitingTime[i] << endl;
  }
}
