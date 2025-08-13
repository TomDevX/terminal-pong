/**
 * STABLE PONG - No screen disappearing
 * Fixed screen clearing and stable display
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sstream>

using namespace std;

// Compile-time configuration
#ifndef BOT_MODE
#define BOT_MODE 0  // 0 = human vs human, 1 = human vs bot, 2 = bot vs bot
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

// AI variables
int ai2Direction = 1;
bool debugMode = true;

// Input handling
struct termios oldTermios;
bool terminalSetup = false;

void setupTerminal() {
    if (!terminalSetup) {
        tcgetattr(STDIN_FILENO, &oldTermios);
        struct termios newTermios = oldTermios;
        newTermios.c_lflag &= ~(ICANON | ECHO);
        newTermios.c_cc[VMIN] = 0;
        newTermios.c_cc[VTIME] = 0;
        tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);
        fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
        terminalSetup = true;
    }
}

void restoreTerminal() {
    if (terminalSetup) {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);
        terminalSetup = false;
    }
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
    frameCount = 0;
    srand(time(0));
}

void Draw() {
    // Build everything in a string buffer first
    stringstream screen;
    
    // Title and info - fixed position
    if (BOT_MODE == 0) {
        screen << "🏓 HUMAN vs HUMAN 🏓 (Frame: " << frameCount << ")\n";
    } else if (BOT_MODE == 1) {
        screen << "🧠 HUMAN vs BOT 🧠 (Frame: " << frameCount << ")\n";
    } else {
        screen << "🤖 BOT vs BOT 🤖 (Frame: " << frameCount << ")\n";
    }
    
    screen << "Score: P1=" << player1Score << " P2=" << player2Score << " | Controls: W/S, I/K, Q=quit\n";
    screen << "Ball at (" << ballX << "," << ballY << ") Dir:(" << ballDirX << "," << ballDirY << ")\n";
    
    // Game board border
    for (int i = 0; i < width + 2; i++) screen << "=";
    screen << "\n";
    
    // Game area
    for (int i = 0; i < height; i++) {
        screen << "|"; // Left border
        
        for (int j = 0; j < width; j++) {
            if (i == ballY && j == ballX) {
                screen << "O"; // Ball
            } else if (j == 2 && i >= player1Y && i < player1Y + paddleSize) {
                screen << "#"; // Player 1 paddle
            } else if (j == width - 3 && i >= player2Y && i < player2Y + paddleSize) {
                screen << "#"; // Player 2 paddle
            } else if (j == width / 2) {
                screen << "|"; // Center line
            } else {
                screen << " ";
            }
        }
        
        screen << "|\n"; // Right border
    }
    
    // Bottom border
    for (int i = 0; i < width + 2; i++) screen << "=";
    screen << "\n";
    
    // Status and debug info
    screen << "Status: ";
    if (debugMode) {
        screen << "DEBUG ON - P1Y:" << player1Y << " P2Y:" << player2Y;
    } else {
        screen << "Game running normally";
    }
    screen << "\n";
    
    screen << "Commands: W=P1↑ S=P1↓ I=P2↑ K=P2↓ Q=Quit D=Debug\n";
    screen << "Press keys to move! Game is responsive.\n";
    
    // Use cursor positioning instead of clear
    cout << "\033[H"; // Move cursor to top-left
    cout << screen.str();
    cout.flush();
    
    frameCount++;
}

// Smart AI for bot mode
void UpdateSmartAI(int &paddleY, bool isPlayer2) {
    int targetY = ballY - paddleSize / 2;
    bool ballComing = (isPlayer2 && ballDirX > 0) || (!isPlayer2 && ballDirX < 0);
    
    if (ballComing) {
        if (targetY > paddleY && paddleY + paddleSize < height - 1) {
            paddleY++;
        } else if (targetY < paddleY && paddleY > 0) {
            paddleY--;
        }
    }
}

// Patrol AI
void UpdatePatrolAI(int &paddleY, int &direction) {
    paddleY += direction;
    if (paddleY <= 0) {
        paddleY = 0;
        direction = 1;
    } else if (paddleY + paddleSize >= height) {
        paddleY = height - paddleSize;
        direction = -1;
    }
}

void Input() {
    char key = getKey();
    
    if (key != 0) {
        if (debugMode) {
            cout << "\033[" << (height + 8) << ";1H"; // Move to bottom
            cout << "Key: " << key << " (ASCII: " << (int)key << ")     ";
            cout.flush();
        }
        
        switch (key) {
            case 'w':
            case 'W':
                if (BOT_MODE != 2 && player1Y > 0) {
                    player1Y--;
                    if (debugMode) cout << " P1↑";
                }
                break;
            case 's':
            case 'S':
                if (BOT_MODE != 2 && player1Y + paddleSize < height) {
                    player1Y++;
                    if (debugMode) cout << " P1↓";
                }
                break;
                
            case 'i':
            case 'I':
                if (BOT_MODE == 0 && player2Y > 0) {
                    player2Y--;
                    if (debugMode) cout << " P2↑";
                }
                break;
            case 'k':
            case 'K':
                if (BOT_MODE == 0 && player2Y + paddleSize < height) {
                    player2Y++;
                    if (debugMode) cout << " P2↓";
                }
                break;
                
            case 'd':
            case 'D':
                debugMode = !debugMode;
                break;
                
            case 'q':
            case 'Q':
                gameOver = true;
                break;
        }
        
        if (debugMode) {
            cout.flush();
        }
    }
}

void Logic() {
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
    
    // AI updates
    if (BOT_MODE == 1) {
        UpdateSmartAI(player2Y, true);
    } else if (BOT_MODE == 2) {
        UpdateSmartAI(player1Y, false);
        UpdatePatrolAI(player2Y, ai2Direction);
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
    if (player1Score >= 5 || player2Score >= 5) {
        cout << "\033[2J\033[H"; // Clear screen once at end
        cout << "🏆 GAME OVER! 🏆" << endl;
        cout << "Final Score: Player 1: " << player1Score << " - Player 2: " << player2Score << endl;
        
        if (BOT_MODE == 0) {
            cout << (player1Score > player2Score ? "🎉 Player 1 Wins!" : "🎉 Player 2 Wins!") << endl;
        } else if (BOT_MODE == 1) {
            cout << (player1Score > player2Score ? "🎉 You Win!" : "🤖 Bot Wins!") << endl;
        } else {
            cout << (player1Score > player2Score ? "🤖 Smart Bot Wins!" : "🔄 Patrol Bot Wins!") << endl;
        }
        
        cout << "Thanks for playing! Press Enter to exit..." << endl;
        restoreTerminal();
        cin.get();
        gameOver = true;
    }
}

void ShowInstructions() {
    cout << "\033[2J\033[H"; // Clear once at start
    
    if (BOT_MODE == 0) {
        cout << "👥 STABLE HUMAN vs HUMAN" << endl;
        cout << "Player 1: W (up) / S (down)" << endl;
        cout << "Player 2: I (up) / K (down)" << endl;
    } else if (BOT_MODE == 1) {
        cout << "🧠 STABLE HUMAN vs BOT" << endl;
        cout << "You: W (up) / S (down)" << endl;
        cout << "Bot: Auto-follows ball" << endl;
    } else {
        cout << "🤖 STABLE BOT vs BOT DEMO" << endl;
        cout << "Watch: Smart Bot vs Patrol Bot" << endl;
    }
    
    cout << endl;
    cout << "🔧 STABILITY FEATURES:" << endl;
    cout << "• No screen clearing during game" << endl;
    cout << "• Debug mode shows key presses (D to toggle)" << endl;
    cout << "• Frame counter shows game is running" << endl;
    cout << "• Cursor positioning instead of clear" << endl;
    cout << endl;
    cout << "Additional controls:" << endl;
    cout << "D = Toggle debug mode" << endl;
    cout << "Q = Quit game" << endl;
    cout << endl;
    cout << "First to 5 points wins!" << endl;
    cout << "Press Enter to start..." << endl;
    cin.get();
}

int main() {
    ShowInstructions();
    
    setupTerminal();
    Setup();
    
    // Clear screen once and prepare
    cout << "\033[2J\033[H";
    cout << "Starting stable game..." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        this_thread::sleep_for(chrono::milliseconds(150)); // Stable timing
    }
    
    restoreTerminal();
    return 0;
}
