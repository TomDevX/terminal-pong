#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

// Game variables
bool gameOver;
const int width = 40;
const int height = 20;
int ballX, ballY;
int ballDirX, ballDirY;
int player1Y, player2Y;
int player1Score, player2Score;

// Function to check if key is pressed (non-blocking)
int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

// Initialize game
void Setup() {
    gameOver = false;
    ballX = width / 2;
    ballY = height / 2;
    ballDirX = 1;
    ballDirY = 1;
    player1Y = height / 2 - 3;
    player2Y = height / 2 - 3;
    player1Score = 0;
    player2Score = 0;
    srand(time(0));
}

// Draw game field
void Draw() {
    system("clear"); // Clear screen for macOS/Linux
    
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
    cout << "Controls: Player 1 (A/Z), Player 2 (K/M), Q to quit" << endl;
}

// Handle input
void Input() {
    if (kbhit()) {
        char key = getchar();
        switch (key) {
            case 'a':
            case 'A':
                if (player1Y > 0) player1Y--;
                break;
            case 'z':
            case 'Z':
                if (player1Y + 4 < height) player1Y++;
                break;
            case 'k':
            case 'K':
                if (player2Y > 0) player2Y--;
                break;
            case 'm':
            case 'M':
                if (player2Y + 4 < height) player2Y++;
                break;
            case 'q':
            case 'Q':
                gameOver = true;
                break;
        }
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
    Setup();
    
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        this_thread::sleep_for(chrono::milliseconds(100)); // Game speed control
    }
    
    return 0;
}