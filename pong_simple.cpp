#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

// Game variables
bool gameOver;
const int width = 40;
const int height = 20;
int ballX, ballY;
int ballDirX, ballDirY;
int player1Y, player2Y;
int player1Score, player2Score;

// Initialize game
void Setup() {
    gameOver = false;
    ballX = width / 2;
    ballY = height / 2;
    ballDirX = 1;
    ballDirY = 1;
    player1Y = height / 2 - 2;
    player2Y = height / 2 - 2;
    player1Score = 0;
    player2Score = 0;
    srand(time(0));
}

// Draw game field
void Draw() {
    system("clear"); // Clear screen
    
    // Top border
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << "#"; // Left border
            
            // Ball
            if (i == ballY && j == ballX)
                cout << "O";
            // Player 1 paddle (left side)
            else if (j == 1 && i >= player1Y && i < player1Y + 4)
                cout << "|";
            // Player 2 paddle (right side)
            else if (j == width - 2 && i >= player2Y && i < player2Y + 4)
                cout << "|";
            else
                cout << " ";
            
            if (j == width - 1) cout << "#"; // Right border
        }
        cout << endl;
    }
    
    // Bottom border
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    
    // Score display
    cout << "Player 1: " << player1Score << "   Player 2: " << player2Score << endl;
    cout << "This is an automatic demo. First to 5 points wins!" << endl;
}

// Simple AI for both paddles (automatic movement)
void AutoPlay() {
    // Player 1 AI (left paddle)
    if (ballY < player1Y + 2 && player1Y > 0)
        player1Y--;
    else if (ballY > player1Y + 2 && player1Y + 4 < height)
        player1Y++;
    
    // Player 2 AI (right paddle) - slightly slower reaction
    if (ballX > width * 2/3) { // Only react when ball is close
        if (ballY < player2Y + 2 && player2Y > 0)
            player2Y--;
        else if (ballY > player2Y + 2 && player2Y + 4 < height)
            player2Y++;
    }
}

// Game logic
void Logic() {
    // Ball movement
    ballX += ballDirX;
    ballY += ballDirY;
    
    // Ball collision with top and bottom walls
    if (ballY <= 0 || ballY >= height - 1)
        ballDirY = -ballDirY;
    
    // Ball collision with paddles
    if (ballX == 2 && ballY >= player1Y && ballY < player1Y + 4)
        ballDirX = -ballDirX;
    
    if (ballX == width - 3 && ballY >= player2Y && ballY < player2Y + 4)
        ballDirX = -ballDirX;
    
    // Ball out of bounds (scoring)
    if (ballX <= 0) {
        player2Score++;
        ballX = width / 2;
        ballY = height / 2;
        ballDirX = 1;
        ballDirY = (rand() % 2 == 0) ? 1 : -1;
    }
    
    if (ballX >= width - 1) {
        player1Score++;
        ballX = width / 2;
        ballY = height / 2;
        ballDirX = -1;
        ballDirY = (rand() % 2 == 0) ? 1 : -1;
    }
    
    // Check for game end (first to 5 points wins)
    if (player1Score >= 5 || player2Score >= 5) {
        system("clear");
        cout << "Game Over!" << endl;
        cout << "Final Score - Player 1: " << player1Score << "   Player 2: " << player2Score << endl;
        if (player1Score > player2Score)
            cout << "Player 1 Wins!" << endl;
        else
            cout << "Player 2 Wins!" << endl;
        cout << "Press Enter to exit..." << endl;
        cin.get();
        gameOver = true;
    }
}

int main() {
    cout << "Starting Pong Game..." << endl;
    cout << "This is an automatic demo version. Press Enter to start!" << endl;
    cin.get();
    
    Setup();
    
    while (!gameOver) {
        Draw();
        AutoPlay();
        Logic();
        this_thread::sleep_for(chrono::milliseconds(200)); // Game speed control
    }
    
    return 0;
}
