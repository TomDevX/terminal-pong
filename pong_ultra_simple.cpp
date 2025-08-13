/**
 * ULTRA SIMPLE PONG - Guaranteed to work
 * Basic blocking input, very simple and reliable
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

// Game variables  
bool gameOver = false;
const int width = 30;
const int height = 15;
int ballX, ballY;
int ballDirX = 1, ballDirY = 1;
int player1Y, player2Y;
int player1Score = 0, player2Score = 0;
const int paddleSize = 3;
int moveCount = 0;

void Setup() {
    ballX = width / 2;
    ballY = height / 2;
    player1Y = height / 2;
    player2Y = height / 2;
    srand(time(0));
}

void Draw() {
    system("clear");
    
    cout << "🏓 ULTRA SIMPLE PONG 🏓" << endl;
    cout << "Score: P1=" << player1Score << " P2=" << player2Score << " Moves=" << moveCount << endl;
    cout << "Controls: 1=P1↑ 2=P1↓ 8=P2↑ 9=P2↓ 0=Quit" << endl;
    cout << endl;
    
    // Draw game
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height-1) cout << "-";
            else if (j == 0 || j == width-1) cout << "|";
            else if (i == ballY && j == ballX) cout << "*";
            else if (j == 2 && i >= player1Y && i < player1Y + paddleSize) cout << "#";
            else if (j == width-3 && i >= player2Y && i < player2Y + paddleSize) cout << "#";
            else cout << " ";
        }
        cout << endl;
    }
    
    cout << endl;
    cout << "Enter command (1,2,8,9,0): ";
}

void Input() {
    int choice;
    cin >> choice;
    
    moveCount++;
    cout << "You pressed: " << choice << endl;
    
    switch(choice) {
        case 1: // P1 up
            if (player1Y > 1) {
                player1Y--;
                cout << "Player 1 moved up!" << endl;
            }
            break;
        case 2: // P1 down  
            if (player1Y + paddleSize < height-1) {
                player1Y++;
                cout << "Player 1 moved down!" << endl;
            }
            break;
        case 8: // P2 up
            if (player2Y > 1) {
                player2Y--;
                cout << "Player 2 moved up!" << endl;
            }
            break;
        case 9: // P2 down
            if (player2Y + paddleSize < height-1) {
                player2Y++;
                cout << "Player 2 moved down!" << endl;
            }
            break;
        case 0: // Quit
            gameOver = true;
            cout << "Quitting..." << endl;
            return;
        default:
            cout << "Invalid input! Use 1,2,8,9,0" << endl;
            break;
    }
    
    // Small delay to see the move
    this_thread::sleep_for(chrono::milliseconds(500));
}

void Logic() {
    // Ball movement
    ballX += ballDirX;
    ballY += ballDirY;
    
    // Bounce off walls
    if (ballY <= 1 || ballY >= height-2) {
        ballDirY = -ballDirY;
    }
    
    // Paddle collision
    if (ballX == 3 && ballY >= player1Y && ballY < player1Y + paddleSize && ballDirX < 0) {
        ballDirX = 1;
    }
    if (ballX == width-4 && ballY >= player2Y && ballY < player2Y + paddleSize && ballDirX > 0) {
        ballDirX = -1;
    }
    
    // Scoring
    if (ballX <= 1) {
        player2Score++;
        ballX = width/2;
        ballY = height/2;
        ballDirX = 1;
        cout << "🎉 Player 2 scored!" << endl;
    }
    if (ballX >= width-2) {
        player1Score++;
        ballX = width/2;
        ballY = height/2;
        ballDirX = -1;
        cout << "🎉 Player 1 scored!" << endl;
    }
    
    // Win condition
    if (player1Score >= 3 || player2Score >= 3) {
        cout << "🏆 GAME OVER!" << endl;
        if (player1Score > player2Score) cout << "Player 1 Wins!" << endl;
        else cout << "Player 2 Wins!" << endl;
        gameOver = true;
    }
}

int main() {
    cout << "🏓 ULTRA SIMPLE PONG 🏓" << endl;
    cout << "This version uses simple number input to guarantee it works" << endl;
    cout << "Controls:" << endl;
    cout << "1 = Player 1 up" << endl;
    cout << "2 = Player 1 down" << endl; 
    cout << "8 = Player 2 up" << endl;
    cout << "9 = Player 2 down" << endl;
    cout << "0 = Quit" << endl;
    cout << endl;
    cout << "Press Enter to start...";
    cin.get();
    
    Setup();
    
    while (!gameOver) {
        Draw();
        Input();
        if (!gameOver) Logic();
    }
    
    cout << "Thanks for playing!" << endl;
    return 0;
}
