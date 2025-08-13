# 🔧 TROUBLESHOOTING GUIDE

## 🚨 PROBLEM 1: Game shows board but no controls/movement

### ✅ SOLUTION: Use Working Version
```bash
./run_game.sh
# Choose option 1, 2, or 3 (working versions)
```

## 🚨 PROBLEM 2: Screen disappears after moving a few times

### ✅ SOLUTION: Use Stable Version  
```bash
./run_game.sh
# Choose option 4 (Stable Version)
```

**🛡️ Stable Version Features:**
- ✅ **No screen clearing** during gameplay
- ✅ **Cursor positioning** instead of clearing
- ✅ **Debug mode** - Press D to see key presses
- ✅ **Frame counter** - Shows game is running
- ✅ **Fixed display** - Screen never disappears

## 🚨 PROBLEM 3: Nothing works at all

### ✅ SOLUTION: Ultra Simple Version
```bash
./run_game.sh
# Choose option 5 (Ultra Simple)
```

Uses **number input**: 1,2,8,9,0 - **Guaranteed to work!**

---

## 🔍 HOW TO DIAGNOSE ISSUES

### Issue: Screen Disappears
**Symptoms:**
- Game starts fine
- After pressing keys a few times, screen goes blank
- Terminal shows empty or garbled output

**Solution:** Use **Option 4 (Stable Version)**

### Issue: No Controls
**Symptoms:**  
- See game board but paddles don't move
- No response to W,S,I,K keys
- Game appears frozen

**Solution:** Use **Options 1-3** or **Option 5**

### Issue: Game Too Fast/Slow
**Symptoms:**
- Ball moves too quickly to follow
- Or game seems laggy/slow

**Solution:** Stable version has optimized timing

---

## 🛠️ STEP-BY-STEP FIX

### Step 1: Try Stable Version
```bash
./run_game.sh
# Choose 4, then choose a/b/c for game mode
```

### Step 2: Enable Debug Mode
- Press **D** during game to see key presses
- Should show "Key: w (ASCII: 119) P1↑"

### Step 3: Check Frame Counter
- Should see "Frame: 1, 2, 3..." incrementing
- If stuck on same number, game is frozen

### Step 4: Last Resort
- If all else fails, use **Option 5** (Ultra Simple)
- Guaranteed to work with number input

---

## 📊 VERSION COMPARISON

| Version | Screen Stability | Input Type | Debug Mode |
|---------|------------------|------------|------------|
| Options 1-3 | Good | Keyboard | Basic |
| **Option 4** | **Excellent** | **Keyboard** | **Advanced** |
| Option 5 | Perfect | Numbers | None |

---

## 🎯 QUICK FIXES

**Screen disappears?** → **Option 4**
**Controls don't work?** → **Option 1-3** 
**Nothing works?** → **Option 5**
**Want debug info?** → **Option 4** + press D

---

**The Stable Version (Option 4) should fix the disappearing screen issue! 🎉**

---

## 🔍 HOW TO TEST IF CONTROLS WORK

### Test 1: Check Debug Output
When running options 1-3, you should see:
```
Key pressed: w
Player 1 moved up!
```

### Test 2: Check Frame Counter
The game should show: `Frame: 1, 2, 3...` (game is running)

### Test 3: Try Ultra Simple
If nothing else works, option 4 definitely will!

---

## 🛠️ COMMON FIXES

### Fix 1: Terminal Focus
- **Click on the terminal window** before pressing keys
- Make sure terminal is the active window

### Fix 2: Check Caps Lock
- Turn OFF caps lock
- Try both uppercase and lowercase (W/w, S/s)

### Fix 3: Try Different Keys
Working version accepts:
- **W/w** and **S/s** for Player 1
- **I/i** and **K/k** for Player 2  
- **Q/q** to quit

### Fix 4: Terminal Type
Try running in different terminal:
- macOS Terminal.app
- iTerm2
- VS Code terminal

---

## 📊 WHAT EACH VERSION DOES

### Options 1-3 (Advanced):
- Real-time keyboard input (W,S,I,K)
- Non-blocking input
- Debug messages
- Faster gameplay

### Option 4 (Ultra Simple):
- Number input (1,2,8,9,0)
- Blocking input (press Enter after each move)
- Guaranteed to work
- Turn-based style

---

## 🎯 QUICK DIAGNOSIS

**See the game board but nothing happens?**
→ Try **Option 4** (Ultra Simple)

**See "Key pressed: X" messages?** 
→ Controls are working! Keep playing.

**Don't see frame counter increasing?**
→ Game is frozen, restart and try Option 4.

**Game too fast/slow?**
→ Options 1-3 auto-run, Option 4 is turn-based.

---

**One of these versions WILL work! 🎉**
