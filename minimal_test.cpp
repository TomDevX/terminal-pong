#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int main() {
    cout << "MINIMAL TEST - Starting..." << endl;
    
    for (int i = 0; i < 10; i++) {
        cout << "Frame " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    
    cout << "Test completed!" << endl;
    return 0;
}
