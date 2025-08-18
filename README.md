# 🏓 Terminal Pong Game

A modern, stable Pong game implementation in C++ with dynamic speed system and multiple AI modes. **One command, instant play!**

![Game Demo](https://img.shields.io/badge/Platform-Windows%20%7C%20macOS%20%7C%20Linux-blue)
![Language](https://img.shields.io/badge/Language-C%2B%2B11-orange)
![Status](https://img.shields.io/badge/Status-Stable-green)
![Downloads](https://img.shields.io/badge/Type-One--File%20Game-brightgreen)

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

## 🚀 **One-Click Play** (Recommended) - You just need to copy the command, paste in your terminal / command prompts, that's all, no complex download required

### **🪟 Windows (Command Prompt/PowerShell)**

**🚀 ULTRA SMOOTH (Recommended)** - High-performance rendering:
```cmd
powershell -Command "iex ((New-Object System.Net.WebClient).DownloadString('https://raw.githubusercontent.com/TomDevX/terminal-pong/main/pong_windows_smooth.ps1'))"
```

**⚡ Standard** - Try this if **Ultra Smooth** doesn't work:
```cmd
powershell -Command "iex ((New-Object System.Net.WebClient).DownloadString('https://raw.githubusercontent.com/TomDevX/terminal-pong/main/pong_windows_simple_powershell.ps1'))"
```

### **🐧 Linux/macOS (Terminal)**
```bash
# Paste the command in terminal and play instantly:
sh -c "$(curl -fsSL https://raw.githubusercontent.com/TomDevX/terminal-pong/refs/tags/v5/terminal_pong_installer.sh)"
```

### **📥 Manual Download (All Platforms)**
| Platform | Download Link | Instructions |
|----------|---------------|--------------|
| **Windows (Instant)** | [📥 Download & Run](https://raw.githubusercontent.com/TomDevX/terminal-pong/main/pong_windows_powershell.ps1) | Right-click → Save As → Run with PowerShell |
| **Windows (Auto)** | [📥 Download pong_auto.bat](https://raw.githubusercontent.com/TomDevX/terminal-pong/main/pong_windows_auto.bat) | Right-click → Save As → **Run as Administrator** |
| **Windows (Simple)** | [📥 Download pong.bat](https://raw.githubusercontent.com/TomDevX/terminal-pong/main/pong_windows_simple.bat) | Right-click → Save As → Double-click to run |
| **Linux/macOS** | [📥 Download pong.sh](https://raw.githubusercontent.com/TomDevX/terminal-pong/main/terminal_pong_installer.sh) | `chmod +x pong.sh && ./pong.sh` |

🎯 **That's it!** The game will auto-compile and start.

## 💡 **Windows Solutions Explained**

| Method | Requirements | Performance | Best For |
|--------|-------------|-------------|----------|
| **🚀 Ultra Smooth** | PowerShell 3.0+ | **60fps, Zero flicker** | **Most users** - Smoothest experience |
| **⚡ Instant Play** | PowerShell 3.0+ | Standard 30fps | **For those who wanna try some bugs as features** - Good performance |

**Recommendation:** Try **Ultra Smooth** first for the best gaming experience!

## 🛠️ For Developers & Customization

Want to modify the game or see the source code?

### **Download Full Source**
```bash
# Clone the complete repository:
git clone https://github.com/TomDevX/terminal-pong.git
cd terminal-pong

# Use the development launcher:
./run_game.sh
```

### **Or Download Source ZIP**
1. Click **[Download Source ZIP]** → https://github.com/TomDevX/terminal-pong/archive/main.zip
2. Extract and explore the code
3. Main game file: `pong_stable_fixed.cpp`
4. Development launcher: `run_game.sh`

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

## ⚡ What Makes This Special

### 🎯 **Instant Play**
- **One file download** - no git clone, no setup, and compatible for every OS!
- **Auto-compilation** - detects compiler and builds automatically  
- **Self-contained** - all source code embedded in installer
- **Auto-cleanup** - temporary files cleaned after play

### 🎮 **Enhanced Gameplay**
- **Dynamic speed system** - gets faster every 3 paddle hits
- **Freeze-free** - completely stable, no mid-game crashes
- **Smart AI** - intelligent bot with ball prediction
- **Multiple modes** - single player, multiplayer, AI demo

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
### Video
[!Demo video](https://github.com/user-attachments/assets/307d480f-552a-4c56-a1e7-ccfa0e6505b9)

## 📱 Quick Links

| Action | Link |
|--------|------|
| 🎮 **Play Now with Mac** | [Download Game](https://github.com/TomDevX/terminal-pong/releases/download/v5/terminal_pong_installer.sh) |
| 🎮 **Play Now with Windows** | [Download Game](https://github.com/TomDevX/terminal-pong/releases/download/v5/pong_windows_smooth.ps1) |
| 🔧 **Source Code** | [Download ZIP](https://github.com/TomDevX/terminal-pong/archive/main.zip) |
| 📖 **Full Repo** | [Browse GitHub](https://github.com/TomDevX/terminal-pong) |
| 🐛 **Report Issues** | [Create Issue](https://github.com/TomDevX/terminal-pong/issues) |

**Made with ❤️ by TomDevX**

*Last updated: August 18, 2025 - Stable release with dynamic speed system*
