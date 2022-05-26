#include <iostream>
#include <iterator>
#include <set>

using namespace std;

set<int> readyQueue;
int processes;
int currentCPUTime = 0;
int totalCPUTime = 0;

void determineReadyQueue(int *arrivalTime, int *completedArrivalTime) {
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
	
  cout << "Enter the number of processes: ";
  cin >> processes;
	
  int burstTime[processes];
  int completedBurstTime[processes];
	
  int arrivalTime[processes];
  int completedArrivalTime[processes];
	
  int completionTime[processes];

  for (int i = 0; i < processes; i++) {
    cout << "Enter arrival time for process " << i << ": ";
      cin >> arrivalTime[i];
      completedArrivalTime[i] = arrivalTime[i];
		
      cout << "Enter burst time for process " << i << ": ";
      cin >> burstTime[i];
      completedBurstTime[i] = burstTime[i];
		
      totalCPUTime += burstTime[i];
		
      cout << "--------------------------" << endl;
  }
	
	
  int ganttChart[totalCPUTime];

  for (int i = 0; i < totalCPUTime; i++) {
    determineReadyQueue(arrivalTime, completedArrivalTime);

    int shortestJobProcessNumber = getShortestJobProcess(burstTime);
    ganttChart[i] = shortestJobProcessNumber;

    burstTime[shortestJobProcessNumber] = burstTime[shortestJobProcessNumber] - 1;
    if (burstTime[shortestJobProcessNumber] == 0) {
      completionTime[shortestJobProcessNumber] = currentCPUTime + 1; // We add 1 here because gantt chart starts from 0

      burstTime[shortestJobProcessNumber] = 9999;
      arrivalTime[shortestJobProcessNumber] = 9999;

      readyQueue.erase(shortestJobProcessNumber);
    }

    currentCPUTime += 1;
  }

  for (int i = 0; i < totalCPUTime; i++) {
    cout << "|P" << ganttChart[i] << "|";
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
