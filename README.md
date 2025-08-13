# 🏓 Enhanced Pong Game Collection

A collection of classic Pong game implementations in C++ with multiple versions and enhanced features.

## 🎮 Game Versions

### 1. **Enhanced Pong** (`test.cpp`) ⭐ NEW!
- **Faster ball movement** with adjustable speed controls
- **True two-player support** with multiple control schemes
- Enhanced physics with paddle spin effects
- Real-time non-blocking input
- Multiple game modes (2P, Player vs AI, AI Demo)
- Improved AI with ball prediction
- Visual enhancements with Unicode characters
- Speed increases after each point

### 2. **Auto Demo** (`pong_simple.cpp`)
- Automatic gameplay demonstration
- AI vs AI gameplay
- Watch the mechanics in action

### 3. **Interactive** (`pong_interactive.cpp`)
- Turn-based player controls
- Player vs AI
- Easy to control and learn

## 🚀 How to Run

### Method 1: Using the launcher script (Recommended)
```bash
chmod +x run_game.sh
./run_game.sh
```

### Method 2: Compile and run directly
```bash
# Enhanced Pong (Recommended):
g++ -std=c++11 test.cpp -o enhanced_pong
./enhanced_pong

# Auto Demo:
g++ -std=c++11 pong_simple.cpp -o pong_simple
./pong_simple

# Interactive:
g++ -std=c++11 pong_interactive.cpp -o pong_interactive
./pong_interactive
```

## 🕹️ Controls

### Enhanced Pong (Real-time):
- **Player 1 (Left Paddle):** W (up), S (down)
- **Player 2 (Right Paddle):** I/K or ↑/↓ arrows
- **Speed Control:** + (faster), - (slower)
- **Game Modes:** 1 (2P), 2 (vs AI), 3 (AI Demo)
- **Q or ESC:** Quit game

## 🎯 Enhanced Features

### Enhanced Pong Game:
- ⚡ **Faster ball movement** with real-time speed adjustment
- 👥 **True two-player support** with multiple control options
- 🎮 **Multiple game modes**: 2-Player, Player vs AI, AI Demo
- 🎯 **Enhanced physics**: Paddle spin effects, better collision detection
- 🤖 **Improved AI**: Ball prediction and adjustable difficulty
- 🎨 **Visual improvements**: Unicode characters, better layout
- 📈 **Progressive difficulty**: Ball speed increases with each point
- ⌨️ **Real-time controls**: Non-blocking input for smooth gameplay

### All Versions:
- ✅ Ball physics with wall bouncing
- ✅ Paddle collision detection
- ✅ Score tracking (first to 5-7 points wins)
- ✅ Game over screen
- ✅ Visual game field with borders
- ✅ Cross-platform compatible (macOS/Linux)

## 🛠️ Requirements

- C++ compiler (g++)
- C++11 support
- macOS/Linux terminal

## 📝 Game Rules

1. Use your paddle to hit the ball
2. Don't let the ball pass your paddle
3. First player to score 5 points wins
4. Ball bounces off top and bottom walls
5. Ball resets to center after each score

Enjoy playing Pong! 🏓
**Made by TomDev using Github Copilot ❤️!**
