#include <iostream>
using namespace std;

int main() {
    cout << "⚡ NEW SPEED SYSTEM DEMO" << endl;
    cout << "========================" << endl;
    cout << endl;
    
    cout << "Speed progression (much more aggressive):" << endl;
    cout << "Default speed is now faster!" << endl;
    cout << endl;
    
    for (int speed = 1; speed <= 5; speed++) {
        int delay = 120 - (speed - 1) * 20;
        if (delay < 40) delay = 40;
        
        cout << "Speed " << speed << "x: ";
        cout << "Delay=" << delay << "ms ";
        cout << "(Ball moves " << speed << " pixels per frame) ";
        
        if (speed == 1) {
            cout << "⬅️ NEW DEFAULT (was 200ms!)";
        } else if (speed == 5) {
            cout << "🚀 MAXIMUM SPEED";
        }
        cout << endl;
    }
    
    cout << endl;
    cout << "🔥 IMPROVEMENTS:" << endl;
    cout << "• Default speed: 200ms → 120ms (much faster start)" << endl;
    cout << "• Speed jumps: 25ms → 20ms per level (bigger difference)" << endl;
    cout << "• Ball movement: Now moves multiple pixels at high speed" << endl;
    cout << "• Max speed: 75ms → 40ms (super fast!)" << endl;
    cout << endl;
    cout << "✅ You should feel real speed difference now!" << endl;
    
    return 0;
}
