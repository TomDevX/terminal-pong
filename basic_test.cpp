#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

int main() {
    cout << "🧪 BASIC LOOP TEST - No terminal controls" << endl;
    
    int ballX = 10, ballY = 5;
    int ballDirX = 1, ballDirY = 1;
    int score1 = 0, score2 = 0;
    
    for (int frame = 1; frame <= 100; frame++) {
        // Simple ball simulation
        ballX += ballDirX;
        ballY += ballDirY;
        
        if (ballY <= 0 || ballY >= 10) {
            ballDirY = -ballDirY;
        }
        
        if (ballX <= 0) {
            score2++;
            ballX = 10;
            ballDirX = 1;
        }
        
        if (ballX >= 20) {
            score1++;
            ballX = 10;
            ballDirX = -1;
        }
        
        // Output every 10 frames
        if (frame % 10 == 0) {
            cout << "Frame " << frame << ": Ball(" << ballX << "," << ballY << ") Score: " << score1 << "-" << score2 << endl;
        }
        
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    
    cout << "✅ Test completed - No freeze in basic loop!" << endl;
    return 0;
}
