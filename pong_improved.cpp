/**
 * Improved Pong Game - Better AI Behavior
 * Features: Smart AI + Patrol AI modes, simplified menu
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
#include <string>

using namespace std;

// Compile-time configuration
#ifndef BOT_MODE
#define BOT_MODE 0  // 0 = human vs human, 1 = human vs bot, 2 = bot vs bot
#endif

// Game variables
bool gameOver = false;
const int width = 50;  
const int height = 25; 
float ballX, ballY;    
float ballSpeedX, ballSpeedY; 
int player1Y, player2Y;
int player1Score = 0, player2Score = 0;
const int paddleSize = 5; 
const float baseSpeed = 1.2f;
float currentSpeed = baseSpeed;

// AI variables
int ai1Direction = 1;  // For patrol AI: 1 = down, -1 = up
int ai2Direction = 1;
float ai1Speed = 0.8f;
float ai2Speed = 0.8f;

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

char getKey() {
    char ch;
    ssize_t result = read(STDIN_FILENO, &ch, 1);
    return (result == 1) ? ch : 0;
}

void Setup() {
    ballX = width / 2.0f;
    ballY = height / 2.0f;
    ballSpeedX = (rand() % 2 == 0) ? currentSpeed : -currentSpeed;
    ballSpeedY = (rand() % 2 == 0) ? currentSpeed * 0.7f : -currentSpeed * 0.7f;
    player1Y = height / 2 - paddleSize / 2;
    player2Y = height / 2 - paddleSize / 2;
    srand(time(0));
}

void Draw() {
    stringstream buffer;
    
    // Title based on mode
    if (BOT_MODE == 0) {
        buffer << "🏓 HUMAN vs HUMAN 🏓\n";
    } else if (BOT_MODE == 1) {
        buffer << "🧠 HUMAN vs BOT 🧠\n";
    } else {
        buffer << "🤖 BOT vs BOT DEMO 🤖\n";
    }
    
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
    
    // Controls based on mode
    buffer << "\n🎮 CONTROLS:\n";
    buffer << "┌─────────────────────────────────────────────────────┐\n";
    
    if (BOT_MODE == 0) {
        buffer << "│ PLAYER 1: [W] up ↑  [S] down ↓                     │\n";
        buffer << "│ PLAYER 2: [I] up ↑  [K] down ↓                     │\n";
    } else if (BOT_MODE == 1) {
        buffer << "│ YOU: [W] up ↑  [S] down ↓  vs  🤖 SMART BOT        │\n";
        buffer << "│ Bot automatically follows the ball                  │\n";
    } else {
        buffer << "│ 🤖 SMART BOT vs 🔄 PATROL BOT                      │\n";
        buffer << "│ Smart: follows ball | Patrol: moves up/down        │\n";
    }
    
    buffer << "│ SPEED: [+] faster  [-] slower                       │\n";
    buffer << "│ QUIT: [Q] to quit game                              │\n";
    buffer << "└─────────────────────────────────────────────────────┘\n";
    
    buffer << "💡 First to 5 points wins!\n";
    
    // Clear screen and output
    cout << "\033[H" << buffer.str() << flush;
}

// Smart AI - follows the ball intelligently
void UpdateSmartAI(int &paddleY, bool isPlayer2) {
    float targetY = ballY - paddleSize / 2.0f;
    
    // Only move when ball is coming towards this paddle
    bool ballComingTowards = (isPlayer2 && ballSpeedX > 0) || (!isPlayer2 && ballSpeedX < 0);
    
    if (ballComingTowards) {
        // Predict where ball will be
        float distanceX = abs(ballX - (isPlayer2 ? width - 2 : 1));
        float timeToReach = distanceX / abs(ballSpeedX);
        float predictedY = ballY + ballSpeedY * timeToReach;
        
        // Handle ball bouncing off top/bottom walls
        while (predictedY < 0 || predictedY >= height) {
            if (predictedY < 0) predictedY = -predictedY;
            if (predictedY >= height) predictedY = 2 * (height - 1) - predictedY;
        }
        
        targetY = predictedY - paddleSize / 2.0f;
    }
    
    // Move towards target
    float diff = targetY - paddleY;
    float aiSpeed = 0.9f;
    
    if (abs(diff) > 1) {
        if (diff > 0 && paddleY + paddleSize < height) {
            paddleY += aiSpeed;
        } else if (diff < 0 && paddleY > 0) {
            paddleY -= aiSpeed;
        }
    }
}

// Patrol AI - moves up and down continuously
void UpdatePatrolAI(int &paddleY, int &direction, float speed) {
    paddleY += direction * speed;
    
    // Bounce off edges
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
    
    if (key == 0) return;
    
    switch (key) {
        case 'w':
        case 'W':
            if (BOT_MODE != 2 && player1Y > 0) player1Y--;
            break;
        case 's':
        case 'S':
            if (BOT_MODE != 2 && player1Y + paddleSize < height) player1Y++;
            break;
            
        case 'i':
        case 'I':
            if (BOT_MODE == 0 && player2Y > 0) player2Y--;
            break;
        case 'k':
        case 'K':
            if (BOT_MODE == 0 && player2Y + paddleSize < height) player2Y++;
            break;
            
        case '+':
        case '=':
            currentSpeed = min(currentSpeed + 0.2f, 3.0f);
            break;
        case '-':
        case '_':
            currentSpeed = max(currentSpeed - 0.2f, 0.5f);
            break;
            
        case 'q':
        case 'Q':
            gameOver = true;
            break;
    }
}

void Logic() {
    // Ball movement
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
    
    // AI updates based on mode
    if (BOT_MODE == 1) {
        // Human vs Bot: Player 2 is smart AI
        UpdateSmartAI(player2Y, true);
    } else if (BOT_MODE == 2) {
        // Bot vs Bot: Player 1 is smart AI, Player 2 is patrol AI
        UpdateSmartAI(player1Y, false);
        UpdatePatrolAI(player2Y, ai2Direction, ai2Speed);
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
    
    // Check for game end
    if (player1Score >= 5 || player2Score >= 5) {
        cout << "\033[2J\033[H" << flush;
        cout << "🏆 GAME OVER! 🏆" << endl;
        cout << "═══════════════════════════════════" << endl;
        cout << "Final Score: Player 1: " << player1Score << " - Player 2: " << player2Score << endl;
        
        if (BOT_MODE == 0) {
            if (player1Score > player2Score)
                cout << "🎉 Player 1 Wins! 🎉" << endl;
            else
                cout << "🎉 Player 2 Wins! 🎉" << endl;
        } else if (BOT_MODE == 1) {
            if (player1Score > player2Score)
                cout << "🎉 You Win! Great job! 🎉" << endl;
            else
                cout << "🤖 Bot Wins! Try again! 🤖" << endl;
        } else {
            if (player1Score > player2Score)
                cout << "🤖 Smart Bot Wins! 🤖" << endl;
            else
                cout << "🔄 Patrol Bot Wins! 🔄" << endl;
        }
        
        cout << "═══════════════════════════════════" << endl;
        cout << "Thanks for playing!" << endl;
        cout << "Press Enter to exit..." << endl;
        
        restoreTerminal();
        cin.get();
        gameOver = true;
    }
}

void ShowInstructions() {
    cout << "\033[2J\033[H" << flush;
    
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
        cout << "Smart Bot (left): Follows ball intelligently" << endl;
        cout << "Patrol Bot (right): Moves up and down continuously" << endl;
    }
    
    cout << endl << "First to 5 points wins!" << endl;
    cout << "Use +/- to change speed, Q to quit" << endl;
    cout << endl << "Press Enter to start!" << endl;
    cin.get();
}

int main() {
    ShowInstructions();
    
    setupTerminal();
    Setup();
    
    cout << "\033[2J\033[H" << flush;
    
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    
    restoreTerminal();
    return 0;
}
