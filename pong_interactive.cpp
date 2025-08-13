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
    cout << "Controls: w/s (Player 1), up/down arrows (Player 2)" << endl;
    cout << "Enter your move and press Enter (w/s/i/k/q): ";
}

// Handle input (turn-based for simplicity)
void Input() {
    char move;
    cin >> move;
    
    switch (move) {
        case 'w':
        case 'W':
            if (player1Y > 0) player1Y--;
            break;
        case 's':
        case 'S':
            if (player1Y + 4 < height) player1Y++;
            break;
        case 'i':
        case 'I':
            if (player2Y > 0) player2Y--;
            break;
        case 'k':
        case 'K':
            if (player2Y + 4 < height) player2Y++;
            break;
        case 'q':
        case 'Q':
            gameOver = true;
            break;
        default:
            // No movement for invalid input
            break;
    }
}

// Simple AI for Player 2 if no input
void Player2AI() {
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
        cout << "Thanks for playing!" << endl;
        gameOver = true;
    }
}

int main() {
    cout << "Welcome to Pong!" << endl;
    cout << "Controls:" << endl;
    cout << "  Player 1 (left): w (up), s (down)" << endl;
    cout << "  Player 2 (right): i (up), k (down)" << endl;
    cout << "  q: quit game" << endl;
    cout << "  Press Enter after each move" << endl;
    cout << "First to 5 points wins!" << endl;
    cout << "Press Enter to start..." << endl;
    cin.get();
    
    Setup();
    
    while (!gameOver) {
        Draw();
        Input();
        if (!gameOver) {
            Player2AI(); // AI assistance for Player 2
            Logic();
        }
    }
    
    return 0;
}
