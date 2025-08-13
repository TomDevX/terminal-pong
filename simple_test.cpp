#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <thread>
#include <chrono>

using namespace std;

struct termios oldTermios;
bool gameOver = false;
int player1Y = 7;
int player2Y = 7;
const int paddleSize = 4;
const int height = 18;

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

void drawSimple() {
    cout << "\033[H"; // Move to top
    cout << "🔧 SIMPLE INPUT TEST" << endl;
    cout << "Player 1 Y: " << player1Y << " | Player 2 Y: " << player2Y << endl;
    cout << "Controls: W/S (Player 1), I/K (Player 2), Q (Quit)" << endl;
    cout << "Press keys to see if they register..." << endl;
    cout << endl;
    
    // Simple paddle display
    for (int i = 0; i < height; i++) {
        cout << "|";
        if (i >= player1Y && i < player1Y + paddleSize) {
            cout << "#";
        } else {
            cout << " ";
        }
        cout << "                                  ";
        if (i >= player2Y && i < player2Y + paddleSize) {
            cout << "#";
        } else {
            cout << " ";
        }
        cout << "|" << endl;
    }
    cout << endl;
}

void handleInput() {
    char key = getKey();
    if (key != 0) {
        cout << "\033[" << (height + 10) << ";1H"; // Move to bottom
        cout << "KEY DETECTED: '" << key << "' -> ";
        
        switch (key) {
            case 'w':
            case 'W':
                if (player1Y > 0) {
                    player1Y--;
                    cout << "Player 1 UP (new Y: " << player1Y << ")";
                } else {
                    cout << "Player 1 at TOP";
                }
                break;
            case 's':
            case 'S':
                if (player1Y + paddleSize < height) {
                    player1Y++;
                    cout << "Player 1 DOWN (new Y: " << player1Y << ")";
                } else {
                    cout << "Player 1 at BOTTOM";
                }
                break;
            case 'i':
            case 'I':
                if (player2Y > 0) {
                    player2Y--;
                    cout << "Player 2 UP (new Y: " << player2Y << ")";
                } else {
                    cout << "Player 2 at TOP";
                }
                break;
            case 'k':
            case 'K':
                if (player2Y + paddleSize < height) {
                    player2Y++;
                    cout << "Player 2 DOWN (new Y: " << player2Y << ")";
                } else {
                    cout << "Player 2 at BOTTOM";
                }
                break;
            case 'q':
            case 'Q':
                cout << "QUIT";
                gameOver = true;
                break;
            default:
                cout << "Unknown key (ASCII: " << (int)key << ")";
                break;
        }
        cout << "                    " << endl; // Clear rest of line
        cout.flush();
    }
}

int main() {
    cout << "\033[2J\033[H"; // Clear screen
    cout << "Starting simple input test..." << endl;
    
    setupTerminal();
    
    while (!gameOver) {
        drawSimple();
        handleInput();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    
    restoreTerminal();
    cout << "\033[2J\033[H"; // Clear screen
    cout << "Test completed!" << endl;
    return 0;
}
