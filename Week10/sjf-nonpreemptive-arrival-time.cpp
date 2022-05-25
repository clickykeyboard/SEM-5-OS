#include <iostream>
#include <set>
#include <iterator>

using namespace std;

set<int> readyQueue;
set<int>::iterator process;

void determineProcessesInReadyQueue(int *arrivalTime, int *completedArrivalTime, int currentCPUTime, int processes) {
	for (int i = 0; i < processes; i++) {
		if (readyQueue.contains(i)) // If process already exists in ready queue, continue with next process
			continue;
		
		if (arrivalTime[i] <= currentCPUTime) {
			readyQueue.insert(i); // Insert process in ready queue
			completedArrivalTime[i] = arrivalTime[i]; // Copy completed arrival time to new array
			arrivalTime[i] = 9999; // Set arrival time to a high value so it doesn't count next iteration
		}
	}
}

int determineShortestJob(int *burstTime) {
  int minimumBurstTimeProcess = *readyQueue.begin(); // This will give us burst time for first process in ready queuequeue
  for (process = ++readyQueue.begin(); process != readyQueue.end(); process++) // Now we compare burst time for each process in ready queue
    if (burstTime[*process] < burstTime[minimumBurstTimeProcess]) {
      minimumBurstTimeProcess = *process;
  	}

  /* Return process number with lowest burst time */
  return minimumBurstTimeProcess;
}

int main() {
  int processes;
  cout << "Enter number of processes: ";
  cin >> processes;

  int arrivalTime[processes];
  int completedArrivalTime[processes];
  int burstTime[processes];
  
  int currentCPUTime = 0;
  int totalCPUTime = 0;

  int ganttChart[processes];
  int completedBurstTime[processes];

  /* Getting arrival times and burst times  */
  for (int i = 0; i < processes; i++) {
    cout << "Enter arrival time for process " << i << ": ";
    cin >> arrivalTime[i];
    cout << "Enter burst time for process " << i << ": ";
    cin >> burstTime[i];
    cout << "---------------------------------" << endl;
    
    totalCPUTime += burstTime[i];
  }
  
  determineProcessesInReadyQueue(arrivalTime, completedArrivalTime, currentCPUTime, processes);
  
  for (int i = 0; i < processes; i++) {
  	int shortestJobProcessNumber = determineShortestJob(burstTime);
  	// Set process in gantt chart
  	ganttChart[i] = shortestJobProcessNumber;
  	
  	// Remove from queue, set burst time to high value so it does not count for next iteration, copy burst time to another array
  	readyQueue.erase(shortestJobProcessNumber);
  	completedBurstTime[shortestJobProcessNumber] = burstTime[shortestJobProcessNumber];
  	burstTime[shortestJobProcessNumber] = 9999;
  	
  	// Update CPU time
  	currentCPUTime += completedBurstTime[shortestJobProcessNumber];
  	
  	determineProcessesInReadyQueue(arrivalTime, completedArrivalTime, currentCPUTime, processes);
  }
  
  for (int i = 0; i < processes; i++) {
    cout << "P" << ganttChart[i] << " ";
  }
  
  /* Completion Time */
  int completionTime[processes] = {0};
  int completionSum = 0;
  for (int i = 0; i < processes; i++) {
    /* Get burst time of processes in order from gantt chart
       and then add their sums */
    completionSum += completedBurstTime[ganttChart[i]];
    completionTime[ganttChart[i]] = completionSum;
  }
  
  int turnaroundTime[processes] = {0}; /* Turnaround time (CT - AT) */
  int waitingTime[processes] = {0}; /* Waiting time (TAT - BT) */
  for (int i = 0; i < processes; i++) {
  	turnaroundTime[i] = completionTime[i] - completedArrivalTime[i];
  	waitingTime[i] = turnaroundTime[i] - completedBurstTime[i];
  }
  
  cout << endl << "P\t" << "BT\t" << "CT\t" << "TAT\t" << "WT" << endl;
  for (int i = 0; i < processes; i++) {
    cout << "P" << i << "\t"
      << completedBurstTime[i] << "\t"
      << completionTime[i] << "\t"
      << turnaroundTime[i] << "\t"
      << waitingTime[i] << endl;
  }
}
