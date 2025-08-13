/**
 * Enhanced Pong Game - Two Player with Fast Ball
 * Features: Faster ball movement, real two-player controls, improved physics
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

using namespace std;

// Game variables
bool gameOver;
const int width = 50;  // Wider field
const int height = 25; // Taller field
float ballX, ballY;    // Float for smoother movement
float ballSpeedX, ballSpeedY; // Adjustable speed
int player1Y, player2Y;
int player1Score, player2Score;
const int paddleSize = 5; // Larger paddles
const float baseSpeed = 1.5f; // Base ball speed
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

// Draw game field
void Draw() {
    // Use ANSI escape sequences instead of system("clear") for better stability
    cout << "\033[2J\033[H" << flush;
    
    // Top border
    for (int i = 0; i < width + 2; i++)
        cout << "═";
    cout << endl;
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << "║"; // Left border
            
            // Ball
            if (i == (int)ballY && j == (int)ballX)
                cout << "●";
            // Player 1 paddle (left side)
            else if (j == 1 && i >= player1Y && i < player1Y + paddleSize)
                cout << "█";
            // Player 2 paddle (right side)
            else if (j == width - 2 && i >= player2Y && i < player2Y + paddleSize)
                cout << "█";
            // Center line
            else if (j == width / 2 && i % 2 == 0)
                cout << "┊";
            else
                cout << " ";
            
            if (j == width - 1) cout << "║"; // Right border
        }
        cout << endl;
    }
    
    // Bottom border
    for (int i = 0; i < width + 2; i++)
        cout << "═";
    cout << endl;
    
    // Game info
    cout << "┌─────────────────────────────────────────────────────┐" << endl;
    cout << "│ Player 1: " << player1Score << " │ Speed: " << currentSpeed << " │ Player 2: " << player2Score << " │" << endl;
    cout << "└─────────────────────────────────────────────────────┘" << endl;
    
    // Controls
    if (gameMode == TWO_PLAYER) {
        cout << "Controls: Player 1 [W/S], Player 2 [↑/↓] or [I/K], [Q]uit, [+/-] Speed" << endl;
    } else if (gameMode == PLAYER_VS_AI) {
        cout << "Controls: Player 1 [W/S] vs AI, [Q]uit, [+/-] Speed" << endl;
    } else {
        cout << "AI Demo Mode - [Q]uit, [+/-] Speed" << endl;
    }
}

// Enhanced AI with difficulty levels
void UpdateAI(int playerY, bool isPlayer2) {
    float targetY = ballY - paddleSize / 2.0f;
    float aiSpeed = (gameMode == AI_DEMO) ? 0.8f : 0.6f; // AI speed
    
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
    
    // Ignore if no key pressed
    if (key == 0) return;
    
    switch (key) {
        // Player 1 controls
        case 'w':
        case 'W':
            if (player1Y > 0) player1Y--;
            break;
        case 's':
        case 'S':
            if (player1Y + paddleSize < height) player1Y++;
            break;
            
        // Player 2 controls (multiple options)
        case 'i':
        case 'I':
            if (gameMode == TWO_PLAYER && player2Y > 0) player2Y--;
            break;
        case 'k':
        case 'K':
            if (gameMode == TWO_PLAYER && player2Y + paddleSize < height) player2Y++;
            break;
            
        // Speed controls
        case '+':
        case '=':
            currentSpeed = min(currentSpeed + 0.2f, 3.0f);
            break;
        case '-':
        case '_':
            currentSpeed = max(currentSpeed - 0.2f, 0.5f);
            break;
            
        // Game mode switch
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
        
        // Ignore other keys
        default:
            break;
    }
}

// Enhanced game logic
void Logic() {
    // Ball movement with speed scaling
    ballX += ballSpeedX;
    ballY += ballSpeedY;
    
    // Ball collision with top and bottom walls
    if (ballY <= 0 || ballY >= height - 1) {
        ballSpeedY = -ballSpeedY;
        ballY = max(0.0f, min((float)(height - 1), ballY));
    }
    
    // Enhanced paddle collision
    // Left paddle collision
    if (ballX <= 2 && ballX >= 1 && ballY >= player1Y - 1 && ballY <= player1Y + paddleSize) {
        ballSpeedX = abs(ballSpeedX); // Always bounce right
        
        // Add spin based on where ball hits paddle
        float hitPos = (ballY - player1Y) / (float)paddleSize - 0.5f;
        ballSpeedY += hitPos * currentSpeed * 0.5f;
        ballSpeedY = max(-currentSpeed * 1.2f, min(currentSpeed * 1.2f, ballSpeedY));
        
        ballX = 2; // Prevent ball from getting stuck
    }
    
    // Right paddle collision
    if (ballX >= width - 3 && ballX <= width - 2 && ballY >= player2Y - 1 && ballY <= player2Y + paddleSize) {
        ballSpeedX = -abs(ballSpeedX); // Always bounce left
        
        // Add spin
        float hitPos = (ballY - player2Y) / (float)paddleSize - 0.5f;
        ballSpeedY += hitPos * currentSpeed * 0.5f;
        ballSpeedY = max(-currentSpeed * 1.2f, min(currentSpeed * 1.2f, ballSpeedY));
        
        ballX = width - 3; // Prevent ball from getting stuck
    }
    
    // Ball out of bounds (scoring)
    if (ballX <= 0) {
        player2Score++;
        ballX = width / 2.0f;
        ballY = height / 2.0f;
        ballSpeedX = currentSpeed;
        ballSpeedY = (rand() % 2 == 0) ? currentSpeed * 0.7f : -currentSpeed * 0.7f;
        currentSpeed = min(currentSpeed + 0.1f, 3.0f); // Increase speed after each point
    }
    
    if (ballX >= width - 1) {
        player1Score++;
        ballX = width / 2.0f;
        ballY = height / 2.0f;
        ballSpeedX = -currentSpeed;
        ballSpeedY = (rand() % 2 == 0) ? currentSpeed * 0.7f : -currentSpeed * 0.7f;
        currentSpeed = min(currentSpeed + 0.1f, 3.0f); // Increase speed after each point
    }
    
    // AI updates based on game mode
    if (gameMode == PLAYER_VS_AI || gameMode == AI_DEMO) {
        UpdateAI(player2Y, true);
    }
    if (gameMode == AI_DEMO) {
        UpdateAI(player1Y, false);
    }
    
    // Check for game end (first to 7 points wins)
    if (player1Score >= 7 || player2Score >= 7) {
        cout << "\033[2J\033[H" << flush; // Use ANSI instead of system("clear")
        cout << "🏆 GAME OVER! 🏆" << endl;
        cout << "═══════════════════════════════════" << endl;
        cout << "Final Score: Player 1: " << player1Score << " - Player 2: " << player2Score << endl;
        if (player1Score > player2Score)
            cout << "🎉 Player 1 Wins! 🎉" << endl;
        else
            cout << "🎉 Player 2 Wins! 🎉" << endl;
        cout << "═══════════════════════════════════" << endl;
        cout << "Thanks for playing Enhanced Pong!" << endl;
        cout << "Press any key to exit..." << endl;
        
        // Wait for any key
        restoreTerminal();
        cin.get();
        gameOver = true;
    }
}

// Main menu
void ShowMenu() {
    cout << "\033[2J\033[H" << flush; // Use ANSI instead of system("clear")
    cout << "🏓 ENHANCED PONG GAME 🏓" << endl;
    cout << "═══════════════════════════════════" << endl;
    cout << "Features:" << endl;
    cout << "• Faster ball movement with speed control" << endl;
    cout << "• True two-player support" << endl;
    cout << "• Enhanced physics and paddle spin" << endl;
    cout << "• Multiple game modes" << endl;
    cout << "• Improved AI with prediction" << endl;
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
    this_thread::sleep_for(chrono::milliseconds(500)); // Pause before game starts
}

int main() {
    ShowMenu();
    
    // Clear any remaining input before starting game
    cin.ignore(10000, '\n');
    
    setupTerminal();
    Setup();
    
    // Clear screen and start game using ANSI
    cout << "\033[2J\033[H" << flush;
    
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        this_thread::sleep_for(chrono::milliseconds(80)); // Slower, more stable game loop
    }
    
    restoreTerminal();
    return 0;
}