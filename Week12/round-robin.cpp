#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

deque<int> readyQueue;
int currentCPUTime = 0;
int processes;

int processJustExecuted = -1;

void determineReadyQueue(int *arrivalTime, int *burstTime) {
  for (int i = 0; i < processes; i++) {
    if (i == processJustExecuted || burstTime[i] < 0)
      continue;
    
    if (arrivalTime[i] <= currentCPUTime) {
      // Check if process does not already exist in ready queue
      if (find(readyQueue.begin(), readyQueue.end(), i) == readyQueue.end())
        readyQueue.push_back(i);
    
    }
  }
  
  // Add the process that was just executed to the end of queue
  if (processJustExecuted != -1 && burstTime[processJustExecuted] != 9999)
    readyQueue.push_back(processJustExecuted);
}

int main() {
  cout << "Enter the number of processes: ";
  cin >> processes;
  
  int timeQuantum;
  cout << "Enter time quantum: ";
  cin >> timeQuantum;
  
  int totalArrivalTime[processes],
      remainingArrivalTime[processes],
      totalBurstTime[processes],
      remainingBurstTime[processes],
      completionTime[processes];
  
  for (int i = 0; i < processes; i++) {
    cout << "Enter arrival time for process " << i << ": ";
    cin >> totalArrivalTime[i];
    remainingArrivalTime[i] = totalArrivalTime[i];
    
    cout << "Enter burst time for process " << i << ": ";
    cin >> totalBurstTime[i];
    remainingBurstTime[i] = totalBurstTime[i];
  }

  /* Round Robin Scheduling */
  int completedProcesses = 0;
  int modifiedTimeQuantum;
  while (completedProcesses != processes) {
    modifiedTimeQuantum = timeQuantum;
  	
    determineReadyQueue(remainingArrivalTime, remainingBurstTime);
    
    processJustExecuted = readyQueue.front();
    readyQueue.pop_front();
    
    if (remainingBurstTime[processJustExecuted] < timeQuantum)
      modifiedTimeQuantum = remainingBurstTime[processJustExecuted];
    
    remainingBurstTime[processJustExecuted] -= modifiedTimeQuantum;
    
    /* Gantt chart */
    cout << "|P" << processJustExecuted + 1<< "|";

    currentCPUTime += modifiedTimeQuantum;
    if (remainingBurstTime[processJustExecuted] <= 0) {
      completionTime[processJustExecuted] = currentCPUTime;
        
      remainingBurstTime[processJustExecuted] = 9999;
      remainingArrivalTime[processJustExecuted] = 9999;
          
      completedProcesses++;
    }
  }

  int turnaroundTime[processes] = {0}; /* Turnaround time (CT - AT) */
  int waitingTime[processes] = {0}; /* Waiting time (TAT - BT) */
  for (int i = 0; i < processes; i++) {
    turnaroundTime[i] = completionTime[i] - totalArrivalTime[i];
    waitingTime[i] = turnaroundTime[i] - totalBurstTime[i];
  }
  
  cout << endl << "P\t" << "AT\t" << "BT\t" << "CT\t" << "TAT\t" << "WT" << endl;
  for (int i = 0; i < processes; i++) {
    cout << "P" << i + 1 << "\t"
          << totalArrivalTime[i] << "\t"
          << totalBurstTime[i] << "\t"
          << completionTime[i] << "\t"
          << turnaroundTime[i] << "\t"
          << waitingTime[i] << endl;
  }
}
