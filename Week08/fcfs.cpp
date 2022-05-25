#include <iostream>

using namespace std;

int main() {
  int processesNumber;
  cout << "Enter the number of processes: " << endl;
  cin >> processesNumber;

  int burstTime[processesNumber];
  for (int i = 0; i < processesNumber; i++) {
    cout << "Enter burst time for process " << i << endl;
    cin >> burstTime[i];
  }

  // Completion Time
  int completionTime[processesNumber] = {0};
  for (int i = 0; i < processesNumber; i++) {
    if (i == 0)
      completionTime[i] = burstTime[i];
    else
      completionTime[i] = burstTime[i] + completionTime[i - 1];
  }

  // Turnaround Time (CT - AT)
  int turnaroundTime[processesNumber] = {0};
  for (int i = 0; i < processesNumber; i++)
    turnaroundTime[i] = completionTime[i] - 0;

  // Waiting Time (TAT - BT)
  int waitingTime[processesNumber] = {0};
  for (int i = 0; i < processesNumber; i++)
    waitingTime[i] = turnaroundTime[i] - burstTime[i];

  cout << "------------------------" << endl;
  cout << "P\t" << "CT\t" << "BT\t" << "TAT\t" << "WT\t" << endl;
  cout << "------------------------" << endl;
  // Process CT, TAT, and WT
  for (int i = 0; i < processesNumber; i++) {
    cout << "P" << i << "\t";
    cout << completionTime[i] << "\t";
    cout << burstTime[i] << "\t";
    cout << turnaroundTime[i] << "\t";
    cout << waitingTime[i] << "\t";
    cout << endl;
  }

  cout << "------------------------" << endl;
  // Average WT and TAT
  float averageTAT = 0, averageWT = 0;
  for (int i = 0; i < processesNumber; i++) {
    averageTAT += turnaroundTime[i];
    averageWT += waitingTime[i];
  }

  averageTAT /= processesNumber;
  averageWT /= processesNumber;

  cout << "Average turnaround time: " << averageTAT << endl;
  cout << "Average waiting time: " << averageWT << endl;
}
