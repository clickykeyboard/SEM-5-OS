// Round Robin
#include <iostream>

using namespace std;

int main() {
    int processes = 4;
    int timeQuantum = 5;
    
    int burstTimes[processes] = { 10, 4, 6, 8 };
    int burstTimesCopy[processes] = { 10, 4, 6, 8 };
    
    int completionTime[processes];
    
    int processesCompleted = 0;
    int completedProcesses[processes] = { 0 };
    
    int CPUTime = 0;
    while (processesCompleted != processes) {
        for (int i = 0; i < processes; i++) {
            if (completedProcesses[i] == 1)
                continue;
            
            
            if (burstTimes[i] <= timeQuantum) {
                CPUTime += burstTimes[i];
                
                burstTimes[i] = 0;
                completedProcesses[i] = 1;
                processesCompleted += 1;
                
                completionTime[i] = CPUTime;
            } else {
                CPUTime += timeQuantum;
                
                burstTimes[i] = burstTimes[i] - timeQuantum;
            }
            
            cout << "P" << i;
            cout << "|" << CPUTime << "|";
        }
    }
    
    // Turnaround Time
    int turnaroundTime[processes];
    int averageTurnaroundTime = 0;
    
    for (int i = 0; i < processes; i++) {
        turnaroundTime[i] = completionTime[i] - 0;
        averageTurnaroundTime += turnaroundTime[i];
    }
    averageTurnaroundTime /= processes;
    
    // Waiting Time
    int waitingTime[processes];
    int averageWaitingTime = 0;
    for (int i = 0; i < processes; i++) {
        waitingTime[i] = turnaroundTime[i] - burstTimesCopy[i];
        averageWaitingTime += waitingTime[i];
    }
    averageWaitingTime /= processes;z
    
    cout << endl << 
        "P\t" << "AT\t" << "BT\t" << "CT\t" << "TAT\t" << "WT"
         << endl;
    for (int i = 0; i < processes; i++) {
        cout << i                 << "\t"
             << 0                 << "\t"
             << burstTimesCopy[i]     << "\t"
             << completionTime[i] << "\t"
             << turnaroundTime[i] << "\t"
             << waitingTime[i]    << endl;
    }
    
}
