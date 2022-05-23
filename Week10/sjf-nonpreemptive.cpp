#include <iostream>
using namespace std;

int main() {
  int processes;
  cout << "Enter processes" << endl;
  cin >> processes;

  int ganttChart[processes];
  int arrivalTime[processes];
  int burstTime[processes];

  int completedBurstTime[processes];

  /* Getting arrival times and burst times  */
  for (int i = 0; i < processes; i++) {
    cout << "Enter burst time for process " << i << endl;
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

  /* We get the index (number) of first executed process from gantt chart
     and then we get its burst time from that index */
  completionTime[0] = completedBurstTime[ganttChart[0]];
  for (int i = 1; i < processes; i++)
    completionTime[i] = completionTime[i - 1] + completedBurstTime[ganttChart[i]];

  for (int i = 0; i < processes; i++)
    cout << endl << completionTime[i] << endl;
}
