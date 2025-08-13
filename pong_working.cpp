/**
 * WORKING PONG GAME - Guaranteed to work with controls
 * Simple, reliable version with working input
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

// Compile-time configuration
#ifndef BOT_MODE
#define BOT_MODE 0  // 0 = human vs human, 1 = human vs bot, 2 = bot vs bot
#endif

// Game variables
bool gameOver = false;
const int width = 40;  
const int height = 20; 
int ballX, ballY;    
int ballDirX = 1, ballDirY = 1; 
int player1Y, player2Y;
int player1Score = 0, player2Score = 0;
const int paddleSize = 4; 

// AI variables
int ai2Direction = 1;  // For patrol AI: 1 = down, -1 = up
int frameCount = 0;

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
    // Clear screen
    system("clear");
    
    // Title based on mode
    if (BOT_MODE == 0) {
        cout << "🏓 HUMAN vs HUMAN 🏓" << endl;
        cout << "Controls: Player 1 (W/S), Player 2 (I/K)" << endl;
    } else if (BOT_MODE == 1) {
        cout << "🧠 HUMAN vs BOT 🧠" << endl;
        cout << "Controls: You (W/S), Bot (Auto)" << endl;
    } else {
        cout << "🤖 BOT vs BOT DEMO 🤖" << endl;
        cout << "Smart Bot vs Patrol Bot" << endl;
    }
    
    cout << "Score: Player 1: " << player1Score << " | Player 2: " << player2Score << endl;
    cout << "Press Q to quit | Frame: " << frameCount << endl;
    cout << endl;
    
    // Game board
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1) {
                cout << "-"; // Top/bottom border
            } else if (j == 0 || j == width - 1) {
                cout << "|"; // Side borders
            } else if (i == ballY && j == ballX) {
                cout << "O"; // Ball
            } else if (j == 2 && i >= player1Y && i < player1Y + paddleSize) {
                cout << "#"; // Player 1 paddle
            } else if (j == width - 3 && i >= player2Y && i < player2Y + paddleSize) {
                cout << "#"; // Player 2 paddle
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
    
    cout << endl;
    cout << "CONTROLS TEST: Try pressing W, S, I, K, Q now!" << endl;
    
    frameCount++;
}

// Smart AI - follows ball
void UpdateSmartAI(int &paddleY, bool isPlayer2) {
    int targetY = ballY - paddleSize / 2;
    
    // Only move when ball is coming towards this paddle
    bool ballComing = (isPlayer2 && ballDirX > 0) || (!isPlayer2 && ballDirX < 0);
    
    if (ballComing) {
        if (targetY > paddleY && paddleY + paddleSize < height - 1) {
            paddleY++;
        } else if (targetY < paddleY && paddleY > 1) {
            paddleY--;
        }
    }
}

// Patrol AI - moves up and down
void UpdatePatrolAI(int &paddleY, int &direction) {
    paddleY += direction;
    
    // Bounce off edges
    if (paddleY <= 1) {
        paddleY = 1;
        direction = 1;
    } else if (paddleY + paddleSize >= height - 1) {
        paddleY = height - 1 - paddleSize;
        direction = -1;
    }
}

void Input() {
    char key = getKey();
    
    if (key != 0) {
        cout << "Key pressed: " << key << endl; // Debug output
        
        switch (key) {
            case 'w':
            case 'W':
                if (BOT_MODE != 2 && player1Y > 1) {
                    player1Y--;
                    cout << "Player 1 moved up!" << endl;
                }
                break;
            case 's':
            case 'S':
                if (BOT_MODE != 2 && player1Y + paddleSize < height - 1) {
                    player1Y++;
                    cout << "Player 1 moved down!" << endl;
                }
                break;
                
            case 'i':
            case 'I':
                if (BOT_MODE == 0 && player2Y > 1) {
                    player2Y--;
                    cout << "Player 2 moved up!" << endl;
                }
                break;
            case 'k':
            case 'K':
                if (BOT_MODE == 0 && player2Y + paddleSize < height - 1) {
                    player2Y++;
                    cout << "Player 2 moved down!" << endl;
                }
                break;
                
            case 'q':
            case 'Q':
                cout << "Quitting game..." << endl;
                gameOver = true;
                break;
                
            default:
                cout << "Unknown key: " << (int)key << endl;
                break;
        }
    }
}

void Logic() {
    // Ball movement
    ballX += ballDirX;
    ballY += ballDirY;
    
    // Ball collision with top and bottom walls
    if (ballY <= 1 || ballY >= height - 2) {
        ballDirY = -ballDirY;
    }
    
    // Ball collision with paddles
    if (ballX == 3 && ballY >= player1Y && ballY < player1Y + paddleSize && ballDirX < 0) {
        ballDirX = 1;
    }
    if (ballX == width - 4 && ballY >= player2Y && ballY < player2Y + paddleSize && ballDirX > 0) {
        ballDirX = -1;
    }
    
    // AI updates based on mode
    if (BOT_MODE == 1) {
        // Human vs Bot: Player 2 is smart AI
        UpdateSmartAI(player2Y, true);
    } else if (BOT_MODE == 2) {
        // Bot vs Bot: Player 1 is smart AI, Player 2 is patrol AI
        UpdateSmartAI(player1Y, false);
        UpdatePatrolAI(player2Y, ai2Direction);
    }
    
    // Scoring
    if (ballX <= 1) {
        player2Score++;
        ballX = width / 2;
        ballY = height / 2;
        ballDirX = 1;
        cout << "Player 2 scored!" << endl;
    }
    
    if (ballX >= width - 2) {
        player1Score++;
        ballX = width / 2;
        ballY = height / 2;
        ballDirX = -1;
        cout << "Player 1 scored!" << endl;
    }
    
    // Check for game end
    if (player1Score >= 3 || player2Score >= 3) {
        system("clear");
        cout << "🏆 GAME OVER! 🏆" << endl;
        cout << "Final Score: Player 1: " << player1Score << " - Player 2: " << player2Score << endl;
        
        if (BOT_MODE == 0) {
            if (player1Score > player2Score)
                cout << "🎉 Player 1 Wins! 🎉" << endl;
            else
                cout << "🎉 Player 2 Wins! 🎉" << endl;
        } else if (BOT_MODE == 1) {
            if (player1Score > player2Score)
                cout << "🎉 You Win! 🎉" << endl;
            else
                cout << "🤖 Bot Wins! 🤖" << endl;
        } else {
            if (player1Score > player2Score)
                cout << "🤖 Smart Bot Wins! 🤖" << endl;
            else
                cout << "🔄 Patrol Bot Wins! 🔄" << endl;
        }
        
        cout << "Press Enter to exit..." << endl;
        restoreTerminal();
        cin.get();
        gameOver = true;
    }
}

void ShowInstructions() {
    system("clear");
    
    if (BOT_MODE == 0) {
        cout << "👥 HUMAN vs HUMAN MODE" << endl;
        cout << "Player 1: W (up) / S (down)" << endl;
        cout << "Player 2: I (up) / K (down)" << endl;
    } else if (BOT_MODE == 1) {
        cout << "🧠 HUMAN vs BOT MODE" << endl;
        cout << "You: W (up) / S (down)" << endl;
        cout << "Bot: Automatically follows the ball" << endl;
    } else {
        cout << "🤖 BOT vs BOT DEMO" << endl;
        cout << "Smart Bot (left): Follows ball" << endl;
        cout << "Patrol Bot (right): Moves up and down" << endl;
    }
    
    cout << endl << "TESTING CONTROLS:" << endl;
    cout << "Try pressing keys now: W, S, I, K, Q" << endl;
    cout << "If you see 'Key pressed: X' messages, controls are working!" << endl;
    cout << endl << "First to 3 points wins!" << endl;
    cout << "Press Enter to start!" << endl;
    
    // Test terminal setup
    setupTerminal();
    
    cout << "Testing input... Press any key (or Enter to continue): ";
    char testKey;
    while (true) {
        testKey = getKey();
        if (testKey != 0) {
            cout << "\n✅ Input working! Key: " << testKey << endl;
            break;
        }
        // Check for Enter from normal input
        if (cin.peek() != EOF) {
            cin.get();
            cout << "\n✅ Proceeding with Enter..." << endl;
            break;
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    
    cout << "Starting game in 2 seconds..." << endl;
    this_thread::sleep_for(chrono::seconds(2));
}

int main() {
    ShowInstructions();
    
    setupTerminal();
    Setup();
    
    cout << "Game starting... Terminal setup complete." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        this_thread::sleep_for(chrono::milliseconds(200)); // Slower for debugging
    }
    
    restoreTerminal();
    return 0;
}
