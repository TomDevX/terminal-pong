/**
 * SIMPLE CONTROLS PONG - Simplest Controls
 * Only uses 4 keys: W, S, I, K
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

bool gameOver = false;
const int width = 40;  
const int height = 20; 
int ballX, ballY;    
int ballDirX = 1, ballDirY = 1; 
int player1Y, player2Y;
int player1Score = 0, player2Score = 0;
const int paddleSize = 4; 

struct termios oldTermios;

void setupTerminal() {
    tcgetattr(STDIN_FILENO, &oldTermios);
    struct termios newTermios = oldTermios;
    newTermios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
}

void restoreTerminal() {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);
}

char getKey() {
    char ch;
    ssize_t result = read(STDIN_FILENO, &ch, 1);
    return (result == 1) ? ch : 0;
}

void Setup() {
    ballX = width / 2;
    ballY = height / 2;
    player1Y = height / 2 - paddleSize / 2;
    player2Y = height / 2 - paddleSize / 2;
    srand(time(0));
}

void Draw() {
    system("clear");
    
    // Title and instructions
    cout << "🏓 SIMPLE PONG - EASY CONTROLS 🏓\n\n";
    
    // Game board
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1) {
                cout << "═"; // Top/bottom border
            } else if (j == 0 || j == width - 1) {
                cout << "║"; // Side borders
            } else if (i == ballY && j == ballX) {
                cout << "●"; // Ball
            } else if (j == 2 && i >= player1Y && i < player1Y + paddleSize) {
                cout << "█"; // Player 1 paddle
            } else if (j == width - 3 && i >= player2Y && i < player2Y + paddleSize) {
                cout << "█"; // Player 2 paddle
            } else if (j == width / 2) {
                cout << "┊"; // Center line
            } else {
                cout << " ";
            }
        }
        cout << "\n";
    }
    
    // Score
    cout << "\n📊 SCORE: Player 1: " << player1Score << " | Player 2: " << player2Score << "\n\n";
    
    // Controls - ALWAYS VISIBLE and CLEAR
    cout << "🎮 CONTROLS (Press gently, don't hold keys):\n";
    cout << "┌─────────────────────────────────────┐\n";
    cout << "│  PLAYER 1 (Left):                  │\n";
    cout << "│    W = Up ↑                        │\n";
    cout << "│    S = Down ↓                      │\n";
    cout << "│                                    │\n";
    cout << "│  PLAYER 2 (Right):                │\n";
    cout << "│    I = Up ↑                        │\n";
    cout << "│    K = Down ↓                      │\n";
    cout << "│                                    │\n";
    cout << "│  Q = Quit game                     │\n";
    cout << "└─────────────────────────────────────┘\n";
    cout << "💡 TRY PRESSING THE KEYS NOW!\n";
}

void Input() {
    char key = getKey();
    
    switch (key) {
        case 'w':
        case 'W':
            if (player1Y > 1) player1Y--;
            cout << "🔊 Player 1 up!" << endl;
            break;
        case 's': 
        case 'S':
            if (player1Y + paddleSize < height - 1) player1Y++;
            cout << "🔊 Player 1 down!" << endl;
            break;
        case 'i':
        case 'I':
            if (player2Y > 1) player2Y--;
            cout << "🔊 Player 2 up!" << endl;
            break;
        case 'k':
        case 'K':
            if (player2Y + paddleSize < height - 1) player2Y++;
            cout << "🔊 Player 2 down!" << endl;
            break;
        case 'q':
        case 'Q':
            cout << "👋 Thanks for playing!" << endl;
            gameOver = true;
            break;
    }
}

void Logic() {
    // Ball movement
    ballX += ballDirX;
    ballY += ballDirY;
    
    // Ball collision with walls
    if (ballY <= 1 || ballY >= height - 2) {
        ballDirY = -ballDirY;
    }
    
    // Ball collision with paddles
    if (ballX == 3 && ballY >= player1Y && ballY < player1Y + paddleSize) {
        ballDirX = 1;
    }
    if (ballX == width - 4 && ballY >= player2Y && ballY < player2Y + paddleSize) {
        ballDirX = -1;
    }
    
    // Scoring
    if (ballX <= 1) {
        player2Score++;
        ballX = width / 2;
        ballY = height / 2;
        ballDirX = 1;
        cout << "🎉 Player 2 scored!" << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    
    if (ballX >= width - 2) {
        player1Score++;
        ballX = width / 2;
        ballY = height / 2;
        ballDirX = -1;
        cout << "🎉 Player 1 scored!" << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    
    // Win condition
    if (player1Score >= 3 || player2Score >= 3) {
        system("clear");
        cout << "🏆 GAME OVER! 🏆\n\n";
        cout << "Final Score: Player 1: " << player1Score << " - Player 2: " << player2Score << "\n";
        if (player1Score > player2Score) {
            cout << "🎉 Player 1 WINS! 🎉\n";
        } else {
            cout << "🎉 Player 2 WINS! 🎉\n";
        }
        cout << "\nPress Enter to exit...";
        restoreTerminal();
        cin.get();
        gameOver = true;
    }
}

void ShowInstructions() {
    system("clear");
    cout << "🏓 SIMPLE PONG - INSTRUCTIONS 🏓\n\n";
    cout << "🎯 GOAL: Get the ball past your opponent's paddle to score\n\n";
    cout << "🎮 CONTROLS:\n";
    cout << "   Player 1 (left side):  W = up, S = down\n";
    cout << "   Player 2 (right side): I = up, K = down\n";
    cout << "   Q = Quit game\n\n";
    cout << "📝 NOTES:\n";
    cout << "   • Press keys gently, don't hold them down\n";
    cout << "   • First player to reach 3 points wins\n";
    cout << "   • Instructions will be shown continuously\n\n";
    cout << "✅ Ready? Press Enter to start!";
    cin.get();
}

int main() {
    ShowInstructions();
    
    setupTerminal();
    Setup();
    
    cout << "Starting game in 3 seconds...\n";
    this_thread::sleep_for(chrono::seconds(1));
    cout << "3..."; cout.flush();
    this_thread::sleep_for(chrono::seconds(1));
    cout << "2..."; cout.flush();
    this_thread::sleep_for(chrono::seconds(1));
    cout << "1..."; cout.flush();
    this_thread::sleep_for(chrono::seconds(1));
    cout << "PLAY!\n";
    
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        this_thread::sleep_for(chrono::milliseconds(200)); // Slower for easier control
    }
    
    restoreTerminal();
    return 0;
}
