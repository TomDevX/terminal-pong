/**
 * Enhanced Control Pong Game - Clear Controls and Instructions
 * Features: Clear control instructions, arrow key support, better feedback
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
const float baseSpeed = 1.0f;
float currentSpeed = baseSpeed;

// Game modes
enum GameMode { TWO_PLAYER, PLAYER_VS_AI, AI_DEMO };
GameMode gameMode = TWO_PLAYER;

// Control state tracking
bool showControls = true;
int frameCount = 0;

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
    frameCount = 0;
    srand(time(0));
}

// Enhanced draw function with clear controls
void Draw() {
    stringstream buffer;
    
    // Title
    buffer << "🏓 PONG GAME 🏓\n";
    
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
    
    // Control instructions - always visible
    buffer << "\n🎮 CONTROLS:\n";
    buffer << "┌─────────────────────────────────────────────────────┐\n";
    
    if (gameMode == TWO_PLAYER) {
        buffer << "│ PLAYER 1: [W] up ↑  [S] down ↓                     │\n";
        buffer << "│ PLAYER 2: [I] up ↑  [K] down ↓                     │\n";
    } else if (gameMode == PLAYER_VS_AI) {
        buffer << "│ PLAYER: [W] up ↑  [S] down ↓  vs  🤖 AI            │\n";
    } else {
        buffer << "│ 🤖 AI DEMO - Watch AI play against AI              │\n";
    }
    
    buffer << "│ SPEED: [+] faster  [-] slower                       │\n";
    buffer << "│ MODE: [1] 2 players  [2] vs AI  [3] AI demo         │\n";
    buffer << "│ QUIT: [Q] to quit game                              │\n";
    buffer << "└─────────────────────────────────────────────────────┘\n";
    
    // Current action feedback
    if (frameCount % 60 < 30) {  // Blinking effect
        buffer << "💡 Press keys now to control!\n";
    } else {
        buffer << "   \n";
    }
    
    // Clear screen and output buffer
    cout << "\033[H" << buffer.str() << flush;
    frameCount++;
}

// Enhanced AI
void UpdateAI(int playerY, bool isPlayer2) {
    float targetY = ballY - paddleSize / 2.0f;
    float aiSpeed = 0.7f;
    
    if ((isPlayer2 && ballSpeedX > 0) || (!isPlayer2 && ballSpeedX < 0)) {
        float predictedY = ballY + ballSpeedY * (abs(ballX - (isPlayer2 ? width - 2 : 1)) / abs(ballSpeedX));
        targetY = predictedY - paddleSize / 2.0f;
    }
    
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

// Enhanced input with better feedback
void Input() {
    char key = getKeyPress();
    
    if (key == 0) return;
    
    switch (key) {
        // Player 1 controls - WASD
        case 'w':
        case 'W':
            if (player1Y > 0) {
                player1Y--;
                cout << "\a" << flush;  // Beep feedback
            }
            break;
        case 's':
        case 'S':
            if (player1Y + paddleSize < height) {
                player1Y++;
                cout << "\a" << flush;  // Beep feedback
            }
            break;
            
        // Player 2 controls - IK
        case 'i':
        case 'I':
            if (gameMode == TWO_PLAYER && player2Y > 0) {
                player2Y--;
                cout << "\a" << flush;  // Beep feedback
            }
            break;
        case 'k':
        case 'K':
            if (gameMode == TWO_PLAYER && player2Y + paddleSize < height) {
                player2Y++;
                cout << "\a" << flush;  // Beep feedback
            }
            break;
            
        // Arrow keys support (escape sequences)
        case '\033': // ESC sequence
            {
                char seq1 = getKeyPress();
                char seq2 = getKeyPress();
                if (seq1 == '[') {
                    switch (seq2) {
                        case 'A': // Up arrow
                            if (gameMode == TWO_PLAYER && player2Y > 0) {
                                player2Y--;
                                cout << "\a" << flush;
                            }
                            break;
                        case 'B': // Down arrow
                            if (gameMode == TWO_PLAYER && player2Y + paddleSize < height) {
                                player2Y++;
                                cout << "\a" << flush;
                            }
                            break;
                    }
                }
            }
            break;
            
        // Speed controls
        case '+':
        case '=':
            currentSpeed = min(currentSpeed + 0.2f, 3.0f);
            break;
        case '-':
        case '_':
            currentSpeed = max(currentSpeed - 0.2f, 0.3f);
            break;
            
        // Game mode switching
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
        
        // Space bar to pause/resume
        case ' ':
            cout << "\033[H" << "⏸️  GAME PAUSED - Nhấn SPACE để tiếp tục..." << flush;
            while (true) {
                char pauseKey = getKeyPress();
                if (pauseKey == ' ') break;
                if (pauseKey == 'q' || pauseKey == 'Q') {
                    gameOver = true;
                    break;
                }
                this_thread::sleep_for(chrono::milliseconds(50));
            }
            break;
        
        default:
            break;
    }
}

// Game logic
void Logic() {
    ballX += ballSpeedX;
    ballY += ballSpeedY;
    
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
    
    // Scoring
    if (ballX <= 0) {
        player2Score++;
        ballX = width / 2.0f;
        ballY = height / 2.0f;
        ballSpeedX = currentSpeed;
        ballSpeedY = (rand() % 2 == 0) ? currentSpeed * 0.7f : -currentSpeed * 0.7f;
    }
    
    if (ballX >= width - 1) {
        player1Score++;
        ballX = width / 2.0f;
        ballY = height / 2.0f;
        ballSpeedX = -currentSpeed;
        ballSpeedY = (rand() % 2 == 0) ? currentSpeed * 0.7f : -currentSpeed * 0.7f;
    }
    
    // AI updates
    if (gameMode == PLAYER_VS_AI || gameMode == AI_DEMO) {
        UpdateAI(player2Y, true);
    }
    if (gameMode == AI_DEMO) {
        UpdateAI(player1Y, false);
    }
    
    // Check for game end
    if (player1Score >= 5 || player2Score >= 5) {
        cout << "\033[2J\033[H" << flush;
        cout << "🏆 GAME OVER! 🏆" << endl;
        cout << "═══════════════════════════════════" << endl;
        cout << "Final Score: Player 1: " << player1Score << " - Player 2: " << player2Score << endl;
        if (player1Score > player2Score)
            cout << "🎉 Player 1 Wins! 🎉" << endl;
        else
            cout << "🎉 Player 2 Wins! 🎉" << endl;
        cout << "═══════════════════════════════════" << endl;
        cout << "Thanks for playing Enhanced Control Pong!" << endl;
        cout << "Press Enter to exit..." << endl;
        
        restoreTerminal();
        cin.get();
        gameOver = true;
    }
}

void ShowMenu() {
    cout << "\033[2J\033[H" << flush;
    cout << "🏓 ENHANCED CONTROL PONG GAME 🏓" << endl;
    cout << "═══════════════════════════════════════" << endl;
    cout << "🎮 Features:" << endl;
    cout << "• Clear controls with WASD + IK keys" << endl;
    cout << "• Arrow key support" << endl;
    cout << "• Audio feedback when pressing keys" << endl;
    cout << "• Continuous instructions display" << endl;
    cout << "• Pause mode with SPACE key" << endl;
    cout << endl;
    cout << "🎯 Game Modes:" << endl;
    cout << "1. Two Players (W/S vs I/K)" << endl;
    cout << "2. Player vs AI (W/S vs AI)" << endl;
    cout << "3. AI Demo" << endl;
    cout << endl;
    cout << "Choose mode (1-3) or Enter for Two Players: ";
    
    string input;
    getline(cin, input);
    
    if (input == "2") gameMode = PLAYER_VS_AI;
    else if (input == "3") gameMode = AI_DEMO;
    else gameMode = TWO_PLAYER;
    
    cout << endl << "🚀 Starting in 3 seconds..." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "3..." << flush;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "2..." << flush;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "1..." << flush;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "PLAY!" << endl;
    this_thread::sleep_for(chrono::milliseconds(500));
}

int main() {
    ShowMenu();
    cin.ignore(10000, '\n');
    
    setupTerminal();
    Setup();
    
    cout << "\033[2J\033[H" << flush;
    
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        this_thread::sleep_for(chrono::milliseconds(120)); // Stable timing
    }
    
    restoreTerminal();
    return 0;
}
