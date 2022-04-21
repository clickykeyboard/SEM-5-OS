#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
 int process = fork();
 if (process == 0) {
  cout << "Child process" << endl;
 } else {
  cout << "Parent process" << endl;
 }
}
