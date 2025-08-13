# 🏓 Terminal Pong Game

A modern, stable Pong game implementation in C++ with dynamic speed system and multiple AI modes. Play in your terminal with smooth gameplay and no freeze issues!

![Game Demo](https://img.shields.io/badge/Platform-macOS%20%7C%20Linux-blue)
![Language](https://img.shields.io/badge/Language-C%2B%2B11-orange)
![Status](https://img.shields.io/badge/Status-Stable-green)

## 🎮 Game Modes

### 1. 🧠 Human vs Bot
- Challenge an intelligent AI opponent
- Smart AI that follows and predicts ball movement
- Perfect for single-player practice

### 2. 👥 Human vs Human 
- Classic two-player mode on same keyboard
- Player 1: W/S keys, Player 2: I/K keys
- Great for local multiplayer fun

### 3. 🤖 Bot vs Bot (Demo)
- Watch AI battle: Smart Bot vs Patrol Bot
- Different AI strategies in action
- Just sit back and enjoy the show!

## 🚀 Quick Start

```bash
# Clone the repository
git clone https://github.com/TomDevX/terminal-pong.git
cd terminal-pong

# Run the game launcher
./run_game.sh
```

Choose your preferred game mode from the menu and start playing!

## 🎯 Manual Compilation

```bash
# Human vs Bot (default)
g++ -std=c++11 -DBOT_MODE=1 pong_stable_fixed.cpp -o pong_game

# Human vs Human  
g++ -std=c++11 -DBOT_MODE=0 pong_stable_fixed.cpp -o pong_game

# Bot vs Bot Demo
g++ -std=c++11 -DBOT_MODE=2 pong_stable_fixed.cpp -o pong_game

# Run the compiled game
./pong_game
```

## 🕹️ Controls

| Mode | Player 1 | Player 2 | Quit |
|------|----------|----------|------|
| Human vs Human | W/S | I/K | Q |
| Human vs Bot | W/S | AI | Q |
| Bot vs Bot | AI | AI | Q |

## ✨ Key Features

### 🚀 **Dynamic Speed System**
- Speed increases every 3 paddle hits
- Real-time speed display (1x → 5x)
- Visual hit counter tracking
- Speed resets after each score

### 🎯 **Enhanced Gameplay**
- Stable display with no screen flickering
- Smooth ball physics with proper collision detection
- Smart AI with ball prediction
- Patrol AI with movement patterns
- No freeze issues during gameplay

### 🔧 **Technical Excellence**
- Non-blocking input handling
- ANSI escape sequences for smooth display
- Cross-platform compatibility (macOS/Linux)
- Optimized game loop for stability

## 🛠️ Requirements

- C++ compiler with C++11 support (g++, clang++)
- macOS or Linux terminal with ANSI support
- Standard Unix libraries (termios, unistd, fcntl)

## 📝 Game Rules

1. **Objective:** Use your paddle to hit the ball and prevent it from passing
2. **Scoring:** First player to reach 5 points wins
3. **Speed System:** Game gets faster every 3 paddle hits (max 5x speed)
4. **Physics:** Ball bounces off top and bottom walls
5. **Reset:** Ball and speed reset to center after each score

## 🎉 Features Highlights

- ✅ **Freeze-Free Gameplay** - Completely stable, no mid-game freezes
- ✅ **Real Speed Changes** - Noticeable speed increases you can actually feel
- ✅ **Smart AI** - Intelligent bot that predicts ball trajectory
- ✅ **Multiple Modes** - Single player, multiplayer, and demo modes
- ✅ **Easy Setup** - One-click launcher with menu selection
- ✅ **Clean Display** - Smooth terminal graphics with emojis

## 🐛 Troubleshooting

### Controls not working?
- Ensure your terminal supports non-blocking input
- Try running with different terminal applications
- Check that termios library is available

### Display issues?
- Verify your terminal supports ANSI escape sequences
- Try resizing the terminal window
- Ensure minimum terminal size (40x20 characters)

## 🏆 Game Stats

- **Ball Speed Levels:** 5 (140ms → 35ms delay)
- **Paddle Size:** 4 characters
- **Game Field:** 40x18 characters
- **Win Score:** 5 points
- **Speed Increase:** Every 3 hits

## 📋 Project Structure

```
terminal-pong/
├── pong_stable_fixed.cpp    # Main game file
├── run_game.sh             # Game launcher script  
├── README.md               # This file
└── Other files...          # Development versions
```

## 🎥 Demo

```
🧠 HUMAN vs BOT (Frame: 45)
Score: P1=2 P2=1 | Speed: 3x | Hits: 7
Controls: W/S (You), Q=quit
==========================================
|                 |                      |
|  #              |                      |
|  #              |                      |
|  #              |                      |
|  #              |                      |
|                 |                      |
|                 |              #       |
|                 |              #       |
|                 |       O      #       |
|                 |              #       |
|                 |                      |
|                 |                      |
|                 |                      |
|                 |                      |
|                 |                      |
|                 |                      |
|                 |                      |
|                 |                      |
==========================================
```

**Made with ❤️ by TomDevX using GitHub Copilot**

*Last updated: August 13, 2025 - Stable release with dynamic speed system*