#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

int main() {
    cout << "🧪 Testing speed system without freeze..." << endl;
    
    int ballSpeed = 1;
    int hitCount = 0;
    
    for (int frame = 1; frame <= 20; frame++) {
        cout << "Frame " << frame << ": Speed=" << ballSpeed << "x, Hits=" << hitCount;
        
        // Simulate paddle hit every few frames
        if (frame % 4 == 0) {
            hitCount++;
            cout << " [HIT!]";
            
            // Increase speed every 3 hits
            if (hitCount % 3 == 0 && ballSpeed < 5) {
                ballSpeed++;
                cout << " [SPEED UP to " << ballSpeed << "x!]";
            }
        }
        
        cout << endl;
        this_thread::sleep_for(chrono::milliseconds(200));
    }
    
    cout << "✅ Test completed without freezing!" << endl;
    return 0;
}
