#include <iostream>
using namespace std;

int convertToPhysicalAddress(int segment, int offset) {
    return segment + offset;
}

int main() {
    int segment;
    cin >> hex >> segment;
    segment = segment * 16;
    
    int offset;
    cin >> hex >> offset;
    
    int physicalAddress = convertToPhysicalAddress(segment, offset);
    cout << hex << physicalAddress;
}
