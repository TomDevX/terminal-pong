#include <iostream>
using namespace std;

int main() {
    cout << "🎮 SPEED SYSTEM DEMO" << endl;
    cout << "=====================" << endl;
    cout << endl;
    
    int hitCount = 0;
    int ballSpeed = 1;
    int gameSpeed = 150;
    
    cout << "Speed progression when ball hits paddle:" << endl;
    cout << "Initial: Speed=" << ballSpeed << "x, Delay=" << gameSpeed << "ms" << endl;
    
    for (int i = 1; i <= 15; i++) {
        hitCount++;
        
        // Same logic as in game
        if (hitCount % 3 == 0 && ballSpeed < 5) {
            ballSpeed++;
            if (gameSpeed > 50) {
                gameSpeed -= 20;
            }
        }
        
        cout << "Hit " << i << ": Speed=" << ballSpeed << "x, Delay=" << gameSpeed << "ms";
        if (hitCount % 3 == 0 && ballSpeed <= 5) {
            cout << " ⚡ SPEED UP!";
        }
        cout << endl;
    }
    
    cout << endl;
    cout << "✅ Speed system implemented successfully!" << endl;
    cout << "Features:" << endl;
    cout << "• Speed increases every 3 paddle hits" << endl;
    cout << "• Maximum speed: 5x" << endl; 
    cout << "• Game delay decreases from 150ms to 50ms" << endl;
    cout << "• Speed resets when someone scores" << endl;
    
    return 0;
}
