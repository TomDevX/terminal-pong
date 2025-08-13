# 🏓 Enhanced Pong Game

A stable, feature-rich Pong game implementation in C++ with dynamic speed and enhanced gameplay.

## 🎮 Game Modes

### 1. 👥 Human vs Human 
- Two players on same keyboard
- Player 1: W/S keys, Player 2: I/K keys
- Dynamic speed increases with paddle hits

### 2. 🧠 Human vs Bot
- Play against intelligent AI
- Smart AI predicts ball trajectory  
- Player controls: W/S keys

### 3. 🤖 Bot vs Bot (Demo)
- Watch AI vs AI gameplay
- Smart Bot vs Patrol Bot
- Controls: Q to quit only

## 🚀 How to Run

**Quick start:**
```bash
./run_game.sh
```
Choose from 4 options:
1. Human vs Human
2. Human vs Bot  
3. Bot vs Bot Demo
4. Exit

**Manual compilation:**
```bash
# Human vs Bot:
g++ -std=c++11 -DBOT_MODE=1 pong_stable_fixed.cpp -o pong_game
./pong_game
```

## 🕹️ Controls

**Human vs Human / Human vs Bot:**
- Player 1: W (up), S (down)
- Player 2: I (up), K (down) 
- D: Toggle debug mode
- Q: Quit game

**Bot vs Bot Demo:**
- Q: Quit game only

## ✨ Key Features

### 🚀 **Dynamic Speed System**
- Speed increases every 3 paddle hits
- Real-time speed display
- Hit counter tracking
- Speed preserved across rounds

### 🎯 **Enhanced Gameplay**
- Fixed ball reflection physics
- Stable display (no screen flickering)
- Smart AI with ball prediction
- Multiple AI behaviors (Smart + Patrol)

### 🔧 **Technical Excellence**
- Non-blocking input handling
- ANSI escape sequences for smooth display
- Cursor positioning instead of screen clearing
- Cross-platform compatibility (macOS/Linux)

## 🎯 Recent Improvements

✅ **Simplified game modes** - Only 3 core modes  
✅ **Dynamic speed system** - Speed increases with hits  
✅ **Bot vs Bot cleanup** - Removed unnecessary controls  
✅ **Enhanced display** - Real-time speed and hit counters  
✅ **Fixed ball physics** - Proper reflection logic

## 🎯 Enhanced Features

### Core Gameplay:
- ✅ **Realistic ball physics** with proper collision detection
- ✅ **Fixed reflection logic** - No more weird bouncing
- ✅ **Stable display** - No screen flickering or disappearing
- ✅ **Multiple control schemes** - Fallback options for compatibility
- ✅ **Debug mode** - Real-time game state information
- ✅ **AI opponents** - Smart and Patrol AI with different behaviors

### Technical Improvements:
- 🔧 **Non-blocking input** - Smooth real-time controls
- 🔧 **Cursor positioning** - Prevents terminal clearing issues
- 🔧 **Cross-platform compatibility** - Works on macOS/Linux
- 🔧 **Multiple build modes** - Compile-time flags for different game modes
- � **Comprehensive error handling** - Graceful fallbacks and recovery

### User Experience:
- 🎮 **Multiple game versions** - From simple to advanced
- 🎮 **Easy launcher script** - One-click game selection  
- 🎮 **Visual feedback** - Debug output and status information
- 🎮 **Flexible controls** - Multiple input methods
- 🎮 **Progressive difficulty** - AI adapts to gameplay

## 🛠️ Technical Details

### Compilation Modes:
- `-DBOT_MODE=0` - Human vs Human
- `-DBOT_MODE=1` - Human vs Bot
- `-DBOT_MODE=2` - Bot vs Bot (Demo)

### Architecture:
- **Input handling:** Non-blocking keyboard input with termios
- **Display:** ANSI escape sequences for positioning and colors
- **AI:** Multiple AI algorithms with different strategies
- **Physics:** Improved collision detection with direction checking

## 🛠️ Requirements

- C++ compiler (g++, clang++)
- C++11 standard support
- macOS/Linux terminal with ANSI support
- termios library (standard on Unix systems)

## � Troubleshooting

### If controls don't work:
1. Try the **Ultra Simple version** (`./quick_pong`) - uses number keys
2. Check terminal compatibility - some terminals may not support non-blocking input
3. Use the **debug version** to see if keys are being detected

### If screen disappears:
1. Use the **Stable version** (option 4 in launcher) - fixed this issue
2. Try resizing your terminal window
3. Check if your terminal supports ANSI escape sequences

### If compilation fails:
1. Ensure you have g++ installed: `g++ --version`
2. Use the full compilation command with flags
3. Check that all source files are present

## �📝 Game Rules

1. **Objective:** Use your paddle to hit the ball back and forth
2. **Scoring:** Don't let the ball pass your paddle - opponent scores
3. **Win condition:** First player to score 5 points wins
4. **Physics:** Ball bounces off top and bottom walls
5. **Reset:** Ball resets to center after each score
6. **AI:** Bots have different strategies - Smart AI predicts, Patrol AI moves in patterns

## 🛠️ Requirements

- C++ compiler (g++, clang++)
- C++11 standard support  
- macOS/Linux terminal with ANSI support

## 📝 Game Rules

1. **Objective:** Hit the ball with your paddle, don't let it pass
2. **Scoring:** First player to 5 points wins
3. **Speed:** Game gets faster every 3 paddle hits
4. **Physics:** Ball bounces off top/bottom walls
5. **AI:** Smart Bot predicts ball, Patrol Bot uses patterns

## 🎉 Quick Start

```bash
cd "/Users/tomimac/Downloads/terminal pong"
./run_game.sh
```

**Want to watch AI battle?** Choose option 3 for Bot vs Bot demo!  
**Want a challenge?** Choose option 2 for Human vs Bot!

Enjoy the enhanced Pong experience! 🏓  
*Made by TomDev using GitHub Copilot ❤️*

---
*Last updated: August 13, 2025 - Added dynamic speed system and simplified game modes*
