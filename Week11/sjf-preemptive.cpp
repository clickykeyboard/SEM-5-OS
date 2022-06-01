#include <iostream>
#include <set>
#include <iterator>

using namespace std;

int processes;
int currentCPUTime = 0;
set<int> readyQueue;

void determineReadyQueue(int *arrivalTime) {
  for (int i = 0; i < processes; i++) {
    if (readyQueue.contains(i))
      continue;
		
    if (arrivalTime[i] <= currentCPUTime)
      readyQueue.insert(i);
  }
}

int getShortestJobProcess(int *burstTime) {
  set<int>::iterator process;
	
  int minimumProcessNumber = *readyQueue.begin();
  for (process = ++readyQueue.begin(); process != readyQueue.end(); process++) {
    if (burstTime[*process] <= burstTime[minimumProcessNumber])
      minimumProcessNumber = *process;
  }
	
  return minimumProcessNumber;
}


int main() {
	cout << "Enter number of processes: "; 
	cin >> processes;
	
	int burstTime[processes],
			completedBurstTime[processes],
			arrivalTime[processes],
			completedArrivalTime[processes], 
			completionTime[processes];

	for (int i = 0; i < processes; i++) {
    cout << "Enter arrival time for process " << i << ": ";
    cin >> arrivalTime[i];
    completedArrivalTime[i] = arrivalTime[i];
	
    cout << "Enter burst time for process " << i << ": ";
    cin >> burstTime[i];
    completedBurstTime[i] = burstTime[i];
    
    cout << "--------------------------" << endl;
  }
	
	int totalProcessesExecuted = 0;
	
	/* Pre-emptive Scheduler */
	while (totalProcessesExecuted != processes) {
		determineReadyQueue(arrivalTime);
		
		int shortestJobProcessNumber = getShortestJobProcess(burstTime);
		
		/* Execute process with shortest job for one time unit */;
		burstTime[shortestJobProcessNumber] = burstTime[shortestJobProcessNumber] - 1;
		
		/* Gantt chart */
		cout << "|P" << shortestJobProcessNumber << "|";
		
		/* Check if process has fully executed */
    if (burstTime[shortestJobProcessNumber] == 0) {
      completionTime[shortestJobProcessNumber] = currentCPUTime + 1; // We add 1 here because gantt chart starts from 0

      burstTime[shortestJobProcessNumber] = 9999;
      arrivalTime[shortestJobProcessNumber] = 9999;

      readyQueue.erase(shortestJobProcessNumber);
      
      totalProcessesExecuted++;
    }

    currentCPUTime += 1;
	}
	

  int turnaroundTime[processes] = {0}; /* Turnaround time (CT - AT) */
  int waitingTime[processes] = {0}; /* Waiting time (TAT - BT) */
  for (int i = 0; i < processes; i++) {
    turnaroundTime[i] = completionTime[i] - completedArrivalTime[i];
    waitingTime[i] = turnaroundTime[i] - completedBurstTime[i];
  }

  cout << endl << "P\t" << "AT\t" << "BT\t" << "CT\t" << "TAT\t" << "WT" << endl;
  for (int i = 0; i < processes; i++) {
    cout << "P" << i << "\t"
    << completedArrivalTime[i] << "\t"
    << completedBurstTime[i] << "\t"
    << completionTime[i] << "\t"
    << turnaroundTime[i] << "\t"
    << waitingTime[i] << endl;
  }
}
