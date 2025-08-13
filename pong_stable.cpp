/**
 * Stable Pong Game - Fixed Disappearing Board Issue
 * Features: Stable display, double buffering, smooth rendering
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sstream>
#include <string>

using namespace std;

// Game variables
bool gameOver;
const int width = 50;  
const int height = 25; 
float ballX, ballY;    
float ballSpeedX, ballSpeedY; 
int player1Y, player2Y;
int player1Score, player2Score;
const int paddleSize = 5; 
const float baseSpeed = 1.2f; // Slightly slower for stability
float currentSpeed = baseSpeed;

// Game modes
enum GameMode { TWO_PLAYER, PLAYER_VS_AI, AI_DEMO };
GameMode gameMode = TWO_PLAYER;

// Input handling
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

char getKeyPress() {
    char ch;
    ssize_t result = read(STDIN_FILENO, &ch, 1);
    if (result == 1) {
        return ch;
    }
    return 0;
}

// Initialize game
void Setup() {
    gameOver = false;
    ballX = width / 2.0f;
    ballY = height / 2.0f;
    ballSpeedX = (rand() % 2 == 0) ? currentSpeed : -currentSpeed;
    ballSpeedY = (rand() % 2 == 0) ? currentSpeed * 0.7f : -currentSpeed * 0.7f;
    player1Y = height / 2 - paddleSize / 2;
    player2Y = height / 2 - paddleSize / 2;
    player1Score = 0;
    player2Score = 0;
    srand(time(0));
}

// Stable draw function with double buffering
void Draw() {
    // Build the entire screen in a string buffer first
    stringstream buffer;
    
    // Top border
    for (int i = 0; i < width + 2; i++)
        buffer << "═";
    buffer << "\n";
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) buffer << "║"; // Left border
            
            // Ball
            if (i == (int)ballY && j == (int)ballX)
                buffer << "●";
            // Player 1 paddle (left side)
            else if (j == 1 && i >= player1Y && i < player1Y + paddleSize)
                buffer << "█";
            // Player 2 paddle (right side)
            else if (j == width - 2 && i >= player2Y && i < player2Y + paddleSize)
                buffer << "█";
            // Center line
            else if (j == width / 2 && i % 2 == 0)
                buffer << "┊";
            else
                buffer << " ";
            
            if (j == width - 1) buffer << "║"; // Right border
        }
        buffer << "\n";
    }
    
    // Bottom border
    for (int i = 0; i < width + 2; i++)
        buffer << "═";
    buffer << "\n";
    
    // Game info
    buffer << "┌─────────────────────────────────────────────────────┐\n";
    buffer << "│ Player 1: " << player1Score << " │ Speed: " << currentSpeed << " │ Player 2: " << player2Score << " │\n";
    buffer << "└─────────────────────────────────────────────────────┘\n";
    
    // Controls
    if (gameMode == TWO_PLAYER) {
        buffer << "Controls: Player 1 [W/S], Player 2 [↑/↓] or [I/K], [Q]uit, [+/-] Speed\n";
    } else if (gameMode == PLAYER_VS_AI) {
        buffer << "Controls: Player 1 [W/S] vs AI, [Q]uit, [+/-] Speed\n";
    } else {
        buffer << "AI Demo Mode - [Q]uit, [+/-] Speed\n";
    }
    
    // Clear screen and output buffer all at once
    cout << "\033[H" << buffer.str() << flush;
}

// Enhanced AI with difficulty levels
void UpdateAI(int playerY, bool isPlayer2) {
    float targetY = ballY - paddleSize / 2.0f;
    float aiSpeed = (gameMode == AI_DEMO) ? 0.8f : 0.6f;
    
    // Add some prediction
    if ((isPlayer2 && ballSpeedX > 0) || (!isPlayer2 && ballSpeedX < 0)) {
        float predictedY = ballY + ballSpeedY * (abs(ballX - (isPlayer2 ? width - 2 : 1)) / abs(ballSpeedX));
        targetY = predictedY - paddleSize / 2.0f;
    }
    
    // Move towards target with some error
    float diff = targetY - playerY;
    if (abs(diff) > 1) {
        if (isPlayer2) {
            if (diff > 0 && player2Y + paddleSize < height)
                player2Y += aiSpeed;
            else if (diff < 0 && player2Y > 0)
                player2Y -= aiSpeed;
        } else {
            if (diff > 0 && player1Y + paddleSize < height)
                player1Y += aiSpeed;
            else if (diff < 0 && player1Y > 0)
                player1Y -= aiSpeed;
        }
    }
}

// Handle input
void Input() {
    char key = getKeyPress();
    
    if (key == 0) return;
    
    switch (key) {
        case 'w':
        case 'W':
            if (player1Y > 0) player1Y--;
            break;
        case 's':
        case 'S':
            if (player1Y + paddleSize < height) player1Y++;
            break;
            
        case 'i':
        case 'I':
            if (gameMode == TWO_PLAYER && player2Y > 0) player2Y--;
            break;
        case 'k':
        case 'K':
            if (gameMode == TWO_PLAYER && player2Y + paddleSize < height) player2Y++;
            break;
            
        case '+':
        case '=':
            currentSpeed = min(currentSpeed + 0.2f, 3.0f);
            break;
        case '-':
        case '_':
            currentSpeed = max(currentSpeed - 0.2f, 0.5f);
            break;
            
        case '1':
            gameMode = TWO_PLAYER;
            break;
        case '2':
            gameMode = PLAYER_VS_AI;
            break;
        case '3':
            gameMode = AI_DEMO;
            break;
            
        case 'q':
        case 'Q':
            gameOver = true;
            break;
        
        default:
            break;
    }
}

// Enhanced game logic
void Logic() {
    ballX += ballSpeedX;
    ballY += ballSpeedY;
    
    // Ball collision with top and bottom walls
    if (ballY <= 0 || ballY >= height - 1) {
        ballSpeedY = -ballSpeedY;
        ballY = max(0.0f, min((float)(height - 1), ballY));
    }
    
    // Left paddle collision
    if (ballX <= 2 && ballX >= 1 && ballY >= player1Y - 1 && ballY <= player1Y + paddleSize) {
        ballSpeedX = abs(ballSpeedX);
        
        float hitPos = (ballY - player1Y) / (float)paddleSize - 0.5f;
        ballSpeedY += hitPos * currentSpeed * 0.5f;
        ballSpeedY = max(-currentSpeed * 1.2f, min(currentSpeed * 1.2f, ballSpeedY));
        
        ballX = 2;
    }
    
    // Right paddle collision
    if (ballX >= width - 3 && ballX <= width - 2 && ballY >= player2Y - 1 && ballY <= player2Y + paddleSize) {
        ballSpeedX = -abs(ballSpeedX);
        
        float hitPos = (ballY - player2Y) / (float)paddleSize - 0.5f;
        ballSpeedY += hitPos * currentSpeed * 0.5f;
        ballSpeedY = max(-currentSpeed * 1.2f, min(currentSpeed * 1.2f, ballSpeedY));
        
        ballX = width - 3;
    }
    
    // Ball out of bounds (scoring)
    if (ballX <= 0) {
        player2Score++;
        ballX = width / 2.0f;
        ballY = height / 2.0f;
        ballSpeedX = currentSpeed;
        ballSpeedY = (rand() % 2 == 0) ? currentSpeed * 0.7f : -currentSpeed * 0.7f;
        currentSpeed = min(currentSpeed + 0.1f, 3.0f);
    }
    
    if (ballX >= width - 1) {
        player1Score++;
        ballX = width / 2.0f;
        ballY = height / 2.0f;
        ballSpeedX = -currentSpeed;
        ballSpeedY = (rand() % 2 == 0) ? currentSpeed * 0.7f : -currentSpeed * 0.7f;
        currentSpeed = min(currentSpeed + 0.1f, 3.0f);
    }
    
    // AI updates
    if (gameMode == PLAYER_VS_AI || gameMode == AI_DEMO) {
        UpdateAI(player2Y, true);
    }
    if (gameMode == AI_DEMO) {
        UpdateAI(player1Y, false);
    }
    
    // Check for game end
    if (player1Score >= 7 || player2Score >= 7) {
        cout << "\033[2J\033[H" << flush;
        cout << "🏆 GAME OVER! 🏆" << endl;
        cout << "═══════════════════════════════════" << endl;
        cout << "Final Score: Player 1: " << player1Score << " - Player 2: " << player2Score << endl;
        if (player1Score > player2Score)
            cout << "🎉 Player 1 Wins! 🎉" << endl;
        else
            cout << "🎉 Player 2 Wins! 🎉" << endl;
        cout << "═══════════════════════════════════" << endl;
        cout << "Thanks for playing Stable Pong!" << endl;
        cout << "Press any key to exit..." << endl;
        
        restoreTerminal();
        cin.get();
        gameOver = true;
    }
}

void ShowMenu() {
    cout << "\033[2J\033[H" << flush;
    cout << "🏓 STABLE PONG GAME 🏓" << endl;
    cout << "═══════════════════════════════════" << endl;
    cout << "Features:" << endl;
    cout << "• Fixed disappearing board issue" << endl;
    cout << "• Stable display with double buffering" << endl;
    cout << "• Smooth rendering" << endl;
    cout << "• Multiple game modes" << endl;
    cout << endl;
    cout << "Game Modes:" << endl;
    cout << "1. Two Player (Human vs Human)" << endl;
    cout << "2. Player vs AI" << endl;
    cout << "3. AI Demo" << endl;
    cout << endl;
    cout << "Choose mode (1-3) or Enter for Two Player: ";
    
    string input;
    getline(cin, input);
    
    if (input == "2") gameMode = PLAYER_VS_AI;
    else if (input == "3") gameMode = AI_DEMO;
    else gameMode = TWO_PLAYER;
    
    cout << endl << "Starting game in 3 seconds..." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "3..." << flush;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "2..." << flush;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "1..." << flush;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "GO!" << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
}

int main() {
    ShowMenu();
    cin.ignore(10000, '\n');
    
    setupTerminal();
    Setup();
    
    // Clear screen once and position cursor at home
    cout << "\033[2J\033[H" << flush;
    
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        this_thread::sleep_for(chrono::milliseconds(100)); // Stable timing
    }
    
    restoreTerminal();
    return 0;
}
