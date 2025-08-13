#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

#ifndef BOT_MODE
#define BOT_MODE 1  // 1 = human vs bot
#endif

// Game variables
bool gameOver = false;
const int width = 40;  
const int height = 18; 
int ballX, ballY;    
int ballDirX = 1, ballDirY = 1; 
int player1Y, player2Y;
int player1Score = 0, player2Score = 0;
const int paddleSize = 4; 
int frameCount = 0;

// Terminal
struct termios oldTermios;

void setupTerminal() {
    tcgetattr(STDIN_FILENO, &oldTermios);
    struct termios newTermios = oldTermios;
    newTermios.c_lflag &= ~(ICANON | ECHO);
    newTermios.c_cc[VMIN] = 0;
    newTermios.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
}

void restoreTerminal() {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);
}

char getKey() {
    char ch;
    if (read(STDIN_FILENO, &ch, 1) == 1) {
        return ch;
    }
    return 0;
}

void Setup() {
    ballX = width / 2;
    ballY = height / 2;
    ballDirX = (rand() % 2 == 0) ? 1 : -1;
    ballDirY = (rand() % 2 == 0) ? 1 : -1;
    player1Y = height / 2 - paddleSize / 2;
    player2Y = height / 2 - paddleSize / 2;
    srand(time(0));
}

void Draw() {
    cout << "\033[H"; // Move to top
    cout << "🧠 SIMPLE HUMAN vs BOT (Frame: " << frameCount << ")" << endl;
    cout << "Score: P1=" << player1Score << " P2=" << player2Score << endl;
    cout << "Controls: W/S (Player 1), Q=quit" << endl;
    cout << "Ball at (" << ballX << "," << ballY << ")" << endl;
    
    // Game board
    for (int i = 0; i < width + 2; i++) cout << "=";
    cout << endl;
    
    for (int i = 0; i < height; i++) {
        cout << "|";
        
        for (int j = 0; j < width; j++) {
            if (i == ballY && j == ballX) {
                cout << "O";
            } else if (j == 2 && i >= player1Y && i < player1Y + paddleSize) {
                cout << "#";
            } else if (j == width - 3 && i >= player2Y && i < player2Y + paddleSize) {
                cout << "#";
            } else if (j == width / 2) {
                cout << "|";
            } else {
                cout << " ";
            }
        }
        
        cout << "|" << endl;
    }
    
    for (int i = 0; i < width + 2; i++) cout << "=";
    cout << endl;
}

void Input() {
    char key = getKey();
    if (key != 0) {
        cout << "[KEY: " << key << "] ";
        
        switch (key) {
            case 'w':
            case 'W':
                if (player1Y > 0) {
                    player1Y--;
                    cout << "P1↑(" << player1Y << ") ";
                }
                break;
            case 's':
            case 'S':
                if (player1Y + paddleSize < height) {
                    player1Y++;
                    cout << "P1↓(" << player1Y << ") ";
                }
                break;
            case 'q':
            case 'Q':
                cout << "QUIT ";
                gameOver = true;
                break;
        }
        cout.flush();
    }
}

void UpdateBot() {
    // Simple bot AI for player 2
    if (ballY < player2Y + paddleSize / 2 && player2Y > 0) {
        player2Y--;
    } else if (ballY > player2Y + paddleSize / 2 && player2Y + paddleSize < height) {
        player2Y++;
    }
}

void Logic() {
    frameCount++;
    
    // Ball movement
    ballX += ballDirX;
    ballY += ballDirY;
    
    // Ball collision with top and bottom walls
    if (ballY <= 0 || ballY >= height - 1) {
        ballDirY = -ballDirY;
        ballY = (ballY <= 0) ? 0 : height - 1;
    }
    
    // Ball collision with paddles
    if (ballX == 3 && ballY >= player1Y && ballY < player1Y + paddleSize && ballDirX < 0) {
        ballDirX = 1;
    }
    if (ballX == width - 4 && ballY >= player2Y && ballY < player2Y + paddleSize && ballDirX > 0) {
        ballDirX = -1;
    }
    
    // Update bot
    UpdateBot();
    
    // Scoring
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
    
    // Win condition
    if (player1Score >= 5 || player2Score >= 5) {
        cout << "\033[2J\033[H";
        cout << "🏆 GAME OVER! 🏆" << endl;
        cout << "Final Score: Player 1: " << player1Score << " - Player 2: " << player2Score << endl;
        cout << (player1Score > player2Score ? "🎉 You Win!" : "🤖 Bot Wins!") << endl;
        gameOver = true;
    }
}

int main() {
    cout << "\033[2J\033[H";
    cout << "🧠 SIMPLE HUMAN vs BOT" << endl;
    cout << "You: W (up) / S (down)" << endl;
    cout << "Bot: Auto-follows ball" << endl;
    cout << "Starting in 2 seconds..." << endl;
    this_thread::sleep_for(chrono::seconds(2));
    
    setupTerminal();
    Setup();
    
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        this_thread::sleep_for(chrono::milliseconds(150));
    }
    
    restoreTerminal();
    return 0;
}
