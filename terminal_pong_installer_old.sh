#!/bin/bash

# 🏓 Terminal Pong Game - One-Click Installer & Runner
# Download this file and run: chmod +x terminal_pong_installer.sh && ./terminal_pong_installer.sh

echo "🏓 Terminal Pong Game Installer"
echo "================================="

# Check if g++ is available
if ! command -v g++ &> /dev/null; then
    echo "❌ g++ compiler not found!"
    echo "Please install g++ first:"
    echo "  macOS: xcode-select --install"
    echo "  Ubuntu/Debian: sudo apt install g++"
    echo "  CentOS/RHEL: sudo yum install gcc-c++"
    exit 1
fi

echo "✅ Compiler found: $(g++ --version | head -n 1)"

# Create temporary directory
TEMP_DIR="/tmp/terminal_pong_$$"
mkdir -p "$TEMP_DIR"
cd "$TEMP_DIR"

echo "📁 Creating game files..."

# Extract the game source code (embedded below)
cat << 'EOF_GAME_SOURCE' > pong_game.cpp
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
#define BOT_MODE 1  // 0=human vs human, 1=human vs bot, 2=bot vs bot
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
int ballSpeed = 1;     
int hitCount = 0;      
int ai2Direction = 1;  

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
    ballSpeed = 1;
    hitCount = 0;
    srand(time(0));
}

void Draw() {
    cout << "\033[H"; 
    
    if (BOT_MODE == 0) {
        cout << "👥 HUMAN vs HUMAN";
    } else if (BOT_MODE == 1) {
        cout << "🧠 HUMAN vs BOT";
    } else {
        cout << "🤖 BOT vs BOT";
    }
    
    cout << " (Frame: " << frameCount << ")" << endl;
    cout << "Score: P1=" << player1Score << " P2=" << player2Score << " | Speed: " << ballSpeed << "x | Hits: " << hitCount << endl;
    
    if (BOT_MODE == 0) {
        cout << "Controls: W/S (P1), I/K (P2), Q=quit" << endl;
    } else if (BOT_MODE == 1) {
        cout << "Controls: W/S (You), Q=quit" << endl;
    } else {
        cout << "Controls: Q=quit (watch bots)" << endl;
    }
    
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
    if (key == 'q' || key == 'Q') {
        gameOver = true;
    }
    if (key == 'w' || key == 'W') {
        if (BOT_MODE != 2 && player1Y > 0) player1Y--;
    }
    if (key == 's' || key == 'S') {
        if (BOT_MODE != 2 && player1Y + paddleSize < height) player1Y++;
    }
    if (key == 'i' || key == 'I') {
        if (BOT_MODE == 0 && player2Y > 0) player2Y--;
    }
    if (key == 'k' || key == 'K') {
        if (BOT_MODE == 0 && player2Y + paddleSize < height) player2Y++;
    }
}

void UpdateSmartBot(int &paddleY) {
    if (ballY < paddleY + paddleSize / 2 && paddleY > 0) {
        paddleY--;
    } else if (ballY > paddleY + paddleSize / 2 && paddleY + paddleSize < height) {
        paddleY++;
    }
}

void UpdatePatrolBot(int &paddleY, int &direction) {
    paddleY += direction;
    if (paddleY <= 0) {
        paddleY = 0;
        direction = 1;
    } else if (paddleY + paddleSize >= height) {
        paddleY = height - paddleSize;
        direction = -1;
    }
}

void Logic() {
    frameCount++;
    
    ballX += ballDirX;
    ballY += ballDirY;
    
    if (ballY <= 0 || ballY >= height - 1) {
        ballDirY = -ballDirY;
        ballY = (ballY <= 0) ? 0 : height - 1;
    }
    
    if (ballX == 3 && ballY >= player1Y && ballY < player1Y + paddleSize && ballDirX < 0) {
        ballDirX = 1;
        hitCount++;
        if (hitCount % 3 == 0 && ballSpeed < 5) {
            ballSpeed++;
        }
    }
    if (ballX == width - 4 && ballY >= player2Y && ballY < player2Y + paddleSize && ballDirX > 0) {
        ballDirX = -1;
        hitCount++;
        if (hitCount % 3 == 0 && ballSpeed < 5) {
            ballSpeed++;
        }
    }
    
    if (BOT_MODE == 1) {
        UpdateSmartBot(player2Y);
    } else if (BOT_MODE == 2) {
        UpdateSmartBot(player1Y);
        UpdatePatrolBot(player2Y, ai2Direction);
    }
    
    if (ballX <= 0) {
        player2Score++;
        ballX = width / 2;
        ballY = height / 2;
        ballDirX = 1;
        ballSpeed = 1;
        hitCount = 0;
    }
    
    if (ballX >= width - 1) {
        player1Score++;
        ballX = width / 2;
        ballY = height / 2;
        ballDirX = -1;
        ballSpeed = 1;
        hitCount = 0;
    }
    
    if (player1Score >= 5 || player2Score >= 5) {
        cout << "\033[2J\033[H";
        cout << "🏆 GAME OVER!" << endl;
        cout << "Final Score: " << player1Score << " - " << player2Score << endl;
        
        if (BOT_MODE == 0) {
            cout << (player1Score > player2Score ? "🎉 Player 1 Wins!" : "🎉 Player 2 Wins!") << endl;
        } else if (BOT_MODE == 1) {
            cout << (player1Score > player2Score ? "🎉 You Win!" : "🤖 Bot Wins!") << endl;
        } else {
            cout << (player1Score > player2Score ? "🧠 Smart Bot Wins!" : "🤖 Patrol Bot Wins!") << endl;
        }
        gameOver = true;
    }
}

void showMenu() {
    cout << "\033[2J\033[H";
    cout << "🏓 Welcome to Terminal Pong! 🏓" << endl;
    cout << "===============================" << endl;
    cout << "Choose game mode:" << endl;
    cout << "1. 🧠 Human vs Bot" << endl;
    cout << "2. 👥 Human vs Human" << endl;
    cout << "3. 🤖 Bot vs Bot (Demo)" << endl;
    cout << "4. ❌ Exit" << endl;
    cout << "===============================" << endl;
    cout << "Enter your choice (1-4): ";
}

int main() {
    showMenu();
    
    char choice;
    cin >> choice;
    
    int mode;
    string modeDesc;
    string controls;
    
    switch (choice) {
        case '1':
            mode = 1;
            modeDesc = "🧠 Starting Human vs Bot mode...";
            controls = "Controls: Use W/S to control your paddle";
            break;
        case '2':
            mode = 0;
            modeDesc = "👥 Starting Human vs Human mode...";
            controls = "Controls: Player 1 (W/S), Player 2 (I/K)";
            break;
        case '3':
            mode = 2;
            modeDesc = "🤖 Starting Bot vs Bot demo...";
            controls = "Smart Bot vs Patrol Bot - Q to quit only";
            break;
        default:
            cout << "❌ Invalid choice. Exiting." << endl;
            return 1;
    }
    
    cout << modeDesc << endl;
    
    // Compile for the specific mode
    string compileCmd = "g++ -std=c++11 -DBOT_MODE=" + to_string(mode) + " pong_game.cpp -o pong_game";
    if (system(compileCmd.c_str()) == 0) {
        cout << "✅ Ready to play!" << endl;
        cout << controls << endl;
        cout << "Features: Speed increases every 3 hits!" << endl;
        cout << "" << endl;
        system("./pong_game");
    } else {
        cout << "❌ Compilation error!" << endl;
        return 1;
    }
    
    return 0;
}
EOF_GAME_SOURCE

echo "🔨 Compiling game..."
if g++ -std=c++11 pong_game.cpp -o terminal_pong; then
    echo "✅ Compilation successful!"
    echo ""
    echo "� Welcome to Pong Game! 🏓"
    echo ""
    echo "Choose game mode:"
    echo "1. 🧠 Human vs Bot"
    echo "2. 👥 Human vs Human"
    echo "3. 🤖 Bot vs Bot"
    echo ""
    read -p "Enter your choice (1-3): " choice
    
    case $choice in
        1)
            echo "🧠 Starting Human vs Bot mode..."
            g++ -std=c++11 -DBOT_MODE=1 pong_game.cpp -o pong_game
            if [ $? -eq 0 ]; then
                echo "✅ Ready to challenge the bot!"
                echo "Controls: Use W/S to control your paddle"
                echo "Features: Speed increases every 3 hits!"
                echo ""
                ./pong_game
            else
                echo "❌ Compilation error!"
            fi
            ;;
        2)
            echo "👥 Starting Human vs Human mode..."
            g++ -std=c++11 -DBOT_MODE=0 pong_game.cpp -o pong_game
            if [ $? -eq 0 ]; then
                echo "✅ Ready to play!"
                echo "Controls: Player 1 (W/S), Player 2 (I/K)"
                echo "Features: Speed increases every 3 hits!"
                echo ""
                ./pong_game
            else
                echo "❌ Compilation error!"
            fi
            ;;
        3)
            echo "🤖 Starting Bot vs Bot demo..."
            g++ -std=c++11 -DBOT_MODE=2 pong_game.cpp -o pong_game
            if [ $? -eq 0 ]; then
                echo "✅ Watch the bots play!"
                echo "Smart Bot vs Patrol Bot"
                echo "Features: Speed increases every 3 hits!"
                echo "Controls: Q to quit only"
                echo ""
                ./pong_game
            else
                echo "❌ Compilation error!"
            fi
            ;;
        *)
            echo "❌ Invalid choice. Please run the script again."
            ;;
    esac
else
    echo "❌ Initial compilation failed!"
    exit 1
fi

# Cleanup
cd /
rm -rf "$TEMP_DIR"

echo ""
echo "🎉 Thanks for playing Terminal Pong!"
echo "💾 To install permanently, visit: https://github.com/TomDevX/terminal-pong"
