#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

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

int main() {
    cout << "🔧 INPUT TEST TOOL" << endl;
    cout << "Press keys to test input. 'q' to quit." << endl;
    cout << "This will help diagnose keyboard input issues." << endl;
    cout << endl;
    
    setupTerminal();
    
    while (true) {
        char key = getKey();
        if (key != 0) {
            cout << "Key detected: '" << key << "' (ASCII: " << (int)key << ")" << endl;
            
            if (key == 'q' || key == 'Q') {
                cout << "Quitting..." << endl;
                break;
            }
            
            switch (key) {
                case 'w': case 'W':
                    cout << "  -> Player 1 UP command" << endl;
                    break;
                case 's': case 'S':
                    cout << "  -> Player 1 DOWN command" << endl;
                    break;
                case 'i': case 'I':
                    cout << "  -> Player 2 UP command" << endl;
                    break;
                case 'k': case 'K':
                    cout << "  -> Player 2 DOWN command" << endl;
                    break;
                case 'd': case 'D':
                    cout << "  -> Debug toggle command" << endl;
                    break;
                default:
                    cout << "  -> Unknown command" << endl;
                    break;
            }
        }
        usleep(10000); // 10ms delay
    }
    
    restoreTerminal();
    return 0;
}
