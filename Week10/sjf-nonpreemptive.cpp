#include <iostream>
using namespace std;

int determineShortestJob(int *burstTime, int processes) {
  int minimumBurstTimeIndex = 0;
  for (int i = 1; i < processes; i++) {
    if (burstTime[i] < burstTime[minimumBurstTimeIndex])
      minimumBurstTimeIndex = i;
  }

  /* Return process number with lowest burst time */
  return minimumBurstTimeIndex;
}

int main() {
  int processes;
  cout << "Enter number of processes: ";
  cin >> processes;

  int ganttChart[processes];
  int arrivalTime[processes];
  int burstTime[processes];

  int completedBurstTime[processes];

  /* Getting arrival times and burst times  */
  for (int i = 0; i < processes; i++) {
    cout << "Enter burst time for process " << i << ": ";
    cin >> burstTime[i];
  }

  for (int i = 0; i < processes; i++) {
    /* Get shortest job: whatever the index is, is also process number */
    int shortestJobIndex = determineShortestJob(burstTime, processes);
    ganttChart[i] = shortestJobIndex;

    /* Afer executing process, copy its burst time to the new burst time array
       and also set the executed process burst time to high value so it doesnt count next iteration */
    completedBurstTime[shortestJobIndex] = burstTime[shortestJobIndex];
    burstTime[shortestJobIndex] = 9999;
  }

  /* Gantt Chart */
  for (int i = 0; i < processes; i++)
    cout << "|P " << ganttChart[i] << "|";

  /* Completion Time */
  int completionTime[processes] = {0};
  int completionSum = 0;
  for (int i = 0; i < processes; i++) {
    /* Get burst time of processes in order from gantt chart
       and then add their sums */
    completionSum += completedBurstTime[ganttChart[i]];
    completionTime[ganttChart[i]] = completionSum;
  }

  /* Turnaround Time (CT - AT) */
  int turnaroundTime[processes] = {0};
  for (int i = 0; i < processes; i++) {
    turnaroundTime[i] = completionTime[i] - 0;
  }

  /* Waiting Time (TAT - BT)*/
  int waitingTime[processes] = {0};
  for (int i = 0; i < processes; i++) {
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
