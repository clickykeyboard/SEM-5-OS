#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
 int process = fork();
 if (process == 0) {
  cout << "Parent process" << endl;
 } else {
  cout << "Child process" << endl;
 }
}
