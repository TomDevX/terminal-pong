# 🏓 Enhanced Pong Game Collection

A comprehensive collection of classic Pong game implementations in C++ with multiple versions, enhanced features, and bug fixes.

## 🎮 Game Versions

### 1. **Stable Version** (`pong_stable_fixed.cpp`) ⭐ RECOMMENDED!
- **Fixed ball reflection logic** - No more weird bouncing behavior
- **No screen clearing** - Smooth gameplay without flickering
- **Debug mode** - Press D to see ball and paddle info
- **Multiple AI modes** - Smart AI and Patrol AI
- **Cursor positioning** - Prevents screen disappearing
- **Frame counter** - Shows game is running smoothly

### 2. **Working Version** (`pong_working.cpp`) 🔧 DEBUG
- **Input testing** - Shows key presses for debugging
- **Enhanced feedback** - Visual confirmation of actions
- **Debug output** - Perfect for troubleshooting
- **Fixed collision logic** - Improved ball physics

### 3. **Ultra Simple** (`pong_ultra_simple.cpp`) 🚀 FALLBACK
- **Number input controls** - Uses 1,2,8,9,0 keys
- **Guaranteed to work** - Perfect backup option
- **Blocking input** - Turn-based style gameplay
- **Simple interface** - Easy to understand

### 4. **Enhanced Controls** (`pong_enhanced_controls.cpp`) 
- **Arrow key support** - Full keyboard compatibility
- **Pause functionality** - P to pause/resume
- **Speed control** - Adjust game speed in real-time
- **Advanced features** - Multiple control schemes

### 5. **Legacy Versions**
- `test.cpp` - Original enhanced version
- `pong_simple.cpp` - Auto demo
- `pong_interactive.cpp` - Turn-based gameplay

## 🚀 How to Run

### Method 1: Using the launcher script (Recommended)
```bash
./run_game.sh
```
Choose from 6 options:
1. 👥 Human vs Human
2. 🧠 Human vs Bot  
3. 🤖 Bot vs Bot (Demo)
4. 🛡️ Stable Version (Fixed disappearing screen)
5. 🔧 Ultra Simple (If controls don't work)
6. Exit

### Method 2: Quick launch (Ultra Simple)
```bash
./quick_pong
```

### Method 3: Compile and run manually
```bash
# Stable version (Human vs Bot):
g++ -std=c++11 -DBOT_MODE=1 pong_stable_fixed.cpp -o pong_game
./pong_game

# Ultra simple version:
g++ -std=c++11 pong_ultra_simple.cpp -o quick_pong
./quick_pong
```

## 🕹️ Controls

### Stable Version (pong_stable_fixed.cpp):
- **Player 1 (Left Paddle):** W (up), S (down)
- **Player 2 (Right Paddle):** I (up), K (down)
- **Debug Mode:** D (toggle debug information)
- **Quit:** Q

### Ultra Simple Version (pong_ultra_simple.cpp):
- **Player 1:** 1 (up), 2 (down)
- **Player 2:** 8 (up), 9 (down)  
- **Quit:** 0

### Working Version (pong_working.cpp):
- **Player 1:** W (up), S (down)
- **Player 2:** I (up), K (down)
- **Quit:** Q
- **Debug output:** Shows key presses and movements

## 🎯 Recent Fixes & Improvements

### ✅ Fixed Ball Reflection Logic (Latest Update!)
- **Problem:** Ball would sometimes bounce back toward the same paddle
- **Solution:** Added direction checking - ball only reflects when coming from correct direction
- **Impact:** Much more realistic and predictable ball physics

### ✅ Fixed Screen Disappearing 
- **Problem:** Game screen would disappear after moving paddles
- **Solution:** Used cursor positioning instead of screen clearing
- **Impact:** Smooth, stable gameplay without flickering

### ✅ Fixed Control Issues
- **Problem:** Keys sometimes wouldn't register
- **Solution:** Multiple input methods and debug feedback
- **Impact:** Reliable controls with fallback options

### ✅ Enhanced AI Behavior
- **Smart AI:** Predicts ball trajectory and moves intelligently  
- **Patrol AI:** Moves in patterns for varied gameplay
- **Balanced difficulty:** Challenging but beatable

## 🎯 Enhanced Features

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

## 🎉 Quick Start

**Want to play right now?**
```bash
cd "/Users/tomimac/Downloads/terminal pong"
./quick_pong
```
Use keys: 1↑ 2↓ (Player 1), 8↑ 9↓ (Player 2), 0 (Quit)

**Want the full experience?**
```bash
./run_game.sh
```
Choose option 4 for the most stable version!

Enjoy playing Pong! 🏓
**Made by TomDev using GitHub Copilot ❤️!**

---
*Last updated: August 13, 2025 - Fixed ball reflection logic and screen stability*
