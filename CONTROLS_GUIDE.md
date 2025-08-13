# 🏓 PONG GAME - SIMPLE GUIDE

## 🎮 GAME MODES

### **OPTION 1: 👥 Human vs Human**
- Player 1 (left): **W** = up, **S** = down
- Player 2 (right): **I** = up, **K** = down
- Classic two-player mode

### **OPTION 2: 🧠 Human vs Bot**
- You (left): **W** = up, **S** = down  
- Bot (right): **Smart AI** - automatically follows the ball
- The bot predicts ball trajectory and moves intelligently

### **OPTION 3: 🤖 Bot vs Bot Demo**
- **Smart Bot** (left): Follows ball with prediction
- **Patrol Bot** (right): Moves up and down continuously, bounces off edges
- Watch different AI strategies compete!

---

## 🚀 HOW TO PLAY

### Quick Start:
```bash
./run_game.sh
# Choose 1, 2, or 3
```

### Universal Controls:
- **+** = Increase game speed
- **-** = Decrease game speed  
- **Q** = Quit game

---

## 🤖 AI BEHAVIOR EXPLAINED

### **Smart Bot (Type 1):**
✅ **Follows the ball intelligently**
- Only moves when ball is coming towards it
- Predicts where ball will be when it arrives
- Accounts for ball bouncing off walls
- Never gets stuck in one position

### **Patrol Bot (Type 2):**
✅ **Continuous movement pattern**
- Always moving up or down
- Bounces off top and bottom edges
- Creates predictable but effective defense
- Never stops moving

---

## 🏆 GAME RULES

- **Goal**: Get ball past opponent's paddle
- **Win**: First to **5 points** wins
- **Physics**: Ball angle changes based on paddle hit position
- **Speed**: Adjustable with +/- keys during gameplay

---

## � TIPS

### Against Smart Bot:
- Try to hit ball at sharp angles
- Use paddle edges for spin shots
- Change ball direction unexpectedly

### Watching Bot vs Bot:
- Smart Bot usually wins with strategy
- Patrol Bot can surprise with consistent coverage
- Adjust speed to see different outcomes

---

## �️ TROUBLESHOOTING

**Controls not working?**
- Click on terminal window first
- Make sure caps lock is off
- Try pressing keys gently

**Game too fast/slow?**
- Use **+** and **-** keys during game
- Start with slower speed for practice

---

**Simple, focused, and fun! 🎉**
