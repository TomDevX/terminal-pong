#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <chrono>
#include <thread>

using namespace std;

#ifndef BOT_MODE
#define BOT_MODE 0
#endif

bool gameOver;
const int width = 20;
const int height = 10;
int ballX, ballY, ballDirX, ballDirY;
int player1Y, player2Y;
int player1Score, player2Score;
const int paddleSize = 3;
int gameSpeed = 100;
int ballHitCount = 0;
int ai2Direction = 1;
bool debugMode = false;
int frameCount = 0;

struct termios orig_termios;

void setupTerminal() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios new_termios = orig_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
}

void restoreTerminal() {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

char getKey() {
    char ch = 0;
    read(STDIN_FILENO, &ch, 1);
    return ch;
}

void Setup() {
    gameOver = false;
    ballX = width / 2;
    ballY = height / 2;
    ballDirX = 1;
    ballDirY = 1;
    player1Y = height / 2 - paddleSize / 2;
    player2Y = height / 2 - paddleSize / 2;
    player1Score = 0;
    player2Score = 0;
    frameCount = 0;
}

void Draw() {
    frameCount++;
    cout << "\033[H";  // Move cursor to top
    cout << "Frame: " << frameCount << " Speed: " << gameSpeed << "ms" << endl;
    cout << "Score: " << player1Score << " - " << player2Score << endl;
    cout << "Ball: (" << ballX << "," << ballY << ")" << endl;
    cout << "DEBUG: Draw() working fine" << endl;
}

void Input() {
    char key = getKey();
    if (key != 0) {
        cout << "\033[" << (height + 5) << ";1H";  // Move to bottom
        cout << "Key pressed: " << key << " (ASCII: " << (int)key << ")" << endl;
        
        if (key == 'q' || key == 'Q') {
            gameOver = true;
        }
        if (key == 'w' || key == 'W') {
            if (player1Y > 0) player1Y--;
        }
        if (key == 's' || key == 'S') {
            if (player1Y < height - paddleSize) player1Y++;
        }
    }
}

void Logic() {
    ballX += ballDirX;
    ballY += ballDirY;
    
    if (ballY <= 0 || ballY >= height - 1) {
        ballDirY = -ballDirY;
    }
    
    if (ballX <= 0) {
        ballX = width / 2;
        ballY = height / 2;
        ballDirX = 1;
    }
    
    if (ballX >= width - 1) {
        ballX = width / 2;
        ballY = height / 2;
        ballDirX = -1;
    }
}

int main() {
    cout << "DEBUG PONG - Starting..." << endl;
    
    setupTerminal();
    Setup();
    
    cout << "\033[2J\033[H";
    cout << "DEBUG PONG MODE" << endl;
    cout << "Press W/S to move, Q to quit" << endl;
    
    int loopCount = 0;
    while (!gameOver && loopCount < 1000) {  // Safety limit
        loopCount++;
        cout << "\033[" << (height + 6) << ";1H";
        cout << "Loop: " << loopCount << endl;
        
        Draw();
        Input();
        Logic();
        
        this_thread::sleep_for(chrono::milliseconds(gameSpeed));
    }
    
    cout << "\033[2J\033[H";
    cout << "Game ended. Total loops: " << loopCount << endl;
    
    restoreTerminal();
    return 0;
}
