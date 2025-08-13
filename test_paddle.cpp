#include <iostream>
using namespace std;

// Same constants as game
const int width = 40;  
const int height = 18; 
const int paddleSize = 4; 
int player1Y = height / 2 - paddleSize / 2;
int player2Y = height / 2 - paddleSize / 2;

#ifndef BOT_MODE
#define BOT_MODE 1  // Test with Human vs Bot
#endif

int main() {
    cout << "🔧 PADDLE MOVEMENT TEST" << endl;
    cout << "BOT_MODE: " << BOT_MODE << endl;
    cout << "Width: " << width << ", Height: " << height << endl;
    cout << "Paddle size: " << paddleSize << endl;
    cout << "Initial P1Y: " << player1Y << ", P2Y: " << player2Y << endl;
    cout << endl;
    
    // Test W key (Player 1 up)
    cout << "Testing W (Player 1 up):" << endl;
    cout << "  Before: P1Y = " << player1Y << endl;
    cout << "  BOT_MODE != 2? " << (BOT_MODE != 2 ? "YES" : "NO") << endl;
    cout << "  player1Y > 0? " << (player1Y > 0 ? "YES" : "NO") << endl;
    
    if (BOT_MODE != 2 && player1Y > 0) {
        player1Y--;
        cout << "  Action: player1Y-- executed" << endl;
    } else {
        cout << "  Action: BLOCKED" << endl;
    }
    cout << "  After: P1Y = " << player1Y << endl;
    cout << endl;
    
    // Test S key (Player 1 down)
    cout << "Testing S (Player 1 down):" << endl;
    cout << "  Before: P1Y = " << player1Y << endl;
    cout << "  BOT_MODE != 2? " << (BOT_MODE != 2 ? "YES" : "NO") << endl;
    cout << "  player1Y + paddleSize < height? " << ((player1Y + paddleSize < height) ? "YES" : "NO") << endl;
    cout << "  " << player1Y << " + " << paddleSize << " = " << (player1Y + paddleSize) << " < " << height << "?" << endl;
    
    if (BOT_MODE != 2 && player1Y + paddleSize < height) {
        player1Y++;
        cout << "  Action: player1Y++ executed" << endl;
    } else {
        cout << "  Action: BLOCKED" << endl;
    }
    cout << "  After: P1Y = " << player1Y << endl;
    cout << endl;
    
    // Test I key (Player 2 up) 
    cout << "Testing I (Player 2 up):" << endl;
    cout << "  Before: P2Y = " << player2Y << endl;
    cout << "  BOT_MODE == 0? " << (BOT_MODE == 0 ? "YES" : "NO") << endl;
    cout << "  player2Y > 0? " << (player2Y > 0 ? "YES" : "NO") << endl;
    
    if (BOT_MODE == 0 && player2Y > 0) {
        player2Y--;
        cout << "  Action: player2Y-- executed" << endl;
    } else {
        cout << "  Action: BLOCKED (expected for BOT_MODE=" << BOT_MODE << ")" << endl;
    }
    cout << "  After: P2Y = " << player2Y << endl;
    
    return 0;
}
