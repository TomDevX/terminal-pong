#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

// Simple test version without complex terminal handling
bool gameOver = false;
const int width = 40;
const int height = 20;
int ballX, ballY;
int ballDirX = 1, ballDirY = 1;
int player1Y, player2Y;
int player1Score = 0, player2Score = 0;

void Setup() {
    ballX = width / 2;
    ballY = height / 2;
    player1Y = height / 2 - 2;
    player2Y = height / 2 - 2;
    srand(time(0));
}

void Draw() {
    system("clear");
    
    // Top border
    for (int i = 0; i < width + 2; i++) cout << "=";
    cout << endl;
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << "|";
            
            if (i == ballY && j == ballX)
                cout << "O";
            else if (j == 1 && i >= player1Y && i < player1Y + 4)
                cout << "#";
            else if (j == width - 2 && i >= player2Y && i < player2Y + 4)
                cout << "#";
            else
                cout << " ";
            
            if (j == width - 1) cout << "|";
        }
        cout << endl;
    }
    
    for (int i = 0; i < width + 2; i++) cout << "=";
    cout << endl;
    
    cout << "Player 1: " << player1Score << " | Player 2: " << player2Score << endl;
    cout << "Controls: W/S (P1), I/K (P2), Q (quit)" << endl;
    cout << "Enter command: ";
}

void Logic() {
    ballX += ballDirX;
    ballY += ballDirY;
    
    if (ballY <= 0 || ballY >= height - 1)
        ballDirY = -ballDirY;
    
    if (ballX == 2 && ballY >= player1Y && ballY < player1Y + 4)
        ballDirX = -ballDirX;
    
    if (ballX == width - 3 && ballY >= player2Y && ballY < player2Y + 4)
        ballDirX = -ballDirX;
    
    if (ballX <= 0) {
        player2Score++;
        ballX = width / 2;
        ballY = height / 2;
        ballDirX = 1;
    }
    
    if (ballX >= width - 1) {
        player1Score++;
        ballX = width / 2;
        ballY = height / 2;
        ballDirX = -1;
    }
    
    if (player1Score >= 5 || player2Score >= 5) {
        cout << "\nGame Over!" << endl;
        cout << "Final Score: Player 1: " << player1Score << " - Player 2: " << player2Score << endl;
        gameOver = true;
    }
}

int main() {
    cout << "=== SIMPLE PONG TEST ===" << endl;
    cout << "This version uses simple input to test functionality" << endl;
    cout << "Press Enter to start..." << endl;
    cin.get();
    
    Setup();
    
    while (!gameOver) {
        Draw();
        
        char move;
        cin >> move;
        
        switch (move) {
            case 'w': if (player1Y > 0) player1Y--; break;
            case 's': if (player1Y + 4 < height) player1Y++; break;
            case 'i': if (player2Y > 0) player2Y--; break;
            case 'k': if (player2Y + 4 < height) player2Y++; break;
            case 'q': gameOver = true; break;
        }
        
        if (!gameOver) Logic();
    }
    
    cout << "Thanks for testing!" << endl;
    return 0;
}
