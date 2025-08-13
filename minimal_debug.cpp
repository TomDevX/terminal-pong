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
#define BOT_MODE 1
#endif

// Minimal game variables
bool gameOver = false;
const int width = 30;  
const int height = 15; 
int ballX, ballY;    
int ballDirX = 1, ballDirY = 1; 
int player1Y, player2Y;
int player1Score = 0, player2Score = 0;
const int paddleSize = 3; 
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
    ballDirX = 1;
    ballDirY = 1;
    player1Y = height / 2;
    player2Y = height / 2;
    srand(time(0));
}

void Draw() {
    cout << "\033[H"; // Move cursor to top
    cout << "🏓 MINIMAL PONG (Frame: " << frameCount << ")" << endl;
    cout << "Score: " << player1Score << " - " << player2Score << " | Ball: (" << ballX << "," << ballY << ")" << endl;
    cout << "Press Q to quit, W/S to move" << endl;
    cout << "========================================" << endl;
    
    // Minimal board display
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == ballY && j == ballX) {
                cout << "O";
            } else if (j == 1 && i >= player1Y && i < player1Y + paddleSize) {
                cout << "|";
            } else if (j == width - 2 && i >= player2Y && i < player2Y + paddleSize) {
                cout << "|";
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
}

void Input() {
    char key = getKey();
    if (key == 'q' || key == 'Q') {
        gameOver = true;
    }
    if (key == 'w' || key == 'W') {
        if (player1Y > 0) player1Y--;
    }
    if (key == 's' || key == 'S') {
        if (player1Y + paddleSize < height) player1Y++;
    }
}

void UpdateBot() {
    // Simple bot for player 2
    if (ballY < player2Y + 1 && player2Y > 0) {
        player2Y--;
    } else if (ballY > player2Y + 1 && player2Y + paddleSize < height) {
        player2Y++;
    }
}

void Logic() {
    frameCount++;
    
    // Ball movement
    ballX += ballDirX;
    ballY += ballDirY;
    
    // Wall bouncing
    if (ballY <= 0 || ballY >= height - 1) {
        ballDirY = -ballDirY;
    }
    
    // Paddle collision
    if (ballX == 2 && ballY >= player1Y && ballY < player1Y + paddleSize && ballDirX < 0) {
        ballDirX = 1;
    }
    if (ballX == width - 3 && ballY >= player2Y && ballY < player2Y + paddleSize && ballDirX > 0) {
        ballDirX = -1;
    }
    
    // Bot AI
    if (BOT_MODE == 1) {
        UpdateBot();
    }
    
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
    if (player1Score >= 3 || player2Score >= 3) {
        gameOver = true;
    }
}

int main() {
    cout << "🧪 ULTRA MINIMAL PONG - Testing for freeze..." << endl;
    cout << "If this freezes, the issue is in basic game loop" << endl;
    this_thread::sleep_for(chrono::seconds(2));
    
    setupTerminal();
    Setup();
    
    int safetyCounter = 0;
    while (!gameOver && safetyCounter < 1000) { // Safety limit
        safetyCounter++;
        
        Draw();
        Input();
        Logic();
        
        // Simple fixed delay
        this_thread::sleep_for(chrono::milliseconds(200));
        
        // Debug output every 50 frames
        if (safetyCounter % 50 == 0) {
            cout << "\033[" << (height + 10) << ";1H"; // Move cursor below game
            cout << "DEBUG: Frame " << safetyCounter << " - Still running..." << endl;
        }
    }
    
    restoreTerminal();
    cout << "\033[2J\033[H"; // Clear screen
    cout << "Game ended after " << safetyCounter << " frames." << endl;
    cout << "Final score: " << player1Score << " - " << player2Score << endl;
    
    if (safetyCounter >= 1000) {
        cout << "⚠️  Reached safety limit - may have been about to freeze" << endl;
    } else {
        cout << "✅ Game ended normally" << endl;
    }
    
    return 0;
}
