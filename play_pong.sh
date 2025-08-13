#!/bin/bash

# 🏓 Terminal Pong Game - Pure Bash Version
# One file, no compilation needed!
# Download and run: curl -L https://raw.githubusercontent.com/TomDevX/terminal-pong/main/play_pong.sh | bash

clear

# Game variables
width=40
height=18
ballX=20
ballY=9
ballDirX=1
ballDirY=1
player1Y=7
player2Y=7
paddleSize=4
player1Score=0
player2Score=0
gameOver=0
frameCount=0
ballSpeed=1
hitCount=0
ai2Direction=1

# Terminal setup
setup_terminal() {
    stty -echo -icanon time 0 min 0
}

restore_terminal() {
    stty echo icanon
}

get_key() {
    local key
    read -n1 -t 0.001 key 2>/dev/null
    echo "$key"
}

setup_game() {
    ballX=$((width / 2))
    ballY=$((height / 2))
    ballDirX=$((RANDOM % 2 == 0 ? 1 : -1))
    ballDirY=$((RANDOM % 2 == 0 ? 1 : -1))
    player1Y=$((height / 2 - paddleSize / 2))
    player2Y=$((height / 2 - paddleSize / 2))
    ballSpeed=1
    hitCount=0
}

draw_game() {
    printf '\033[H'  # Move cursor to top
    
    case $BOT_MODE in
        0) echo "👥 HUMAN vs HUMAN (Frame: $frameCount)" ;;
        1) echo "🧠 HUMAN vs BOT (Frame: $frameCount)" ;;
        2) echo "🤖 BOT vs BOT (Frame: $frameCount)" ;;
    esac
    
    echo "Score: P1=$player1Score P2=$player2Score | Speed: ${ballSpeed}x | Hits: $hitCount"
    
    case $BOT_MODE in
        0) echo "Controls: W/S (P1), I/K (P2), Q=quit" ;;
        1) echo "Controls: W/S (You), Q=quit" ;;
        2) echo "Controls: Q=quit (watch bots)" ;;
    esac
    
    # Top border
    printf '='
    for ((i=0; i<width; i++)); do printf '='; done
    printf '=\n'
    
    # Game field
    for ((i=0; i<height; i++)); do
        printf '|'
        for ((j=0; j<width; j++)); do
            if [[ $i -eq $ballY && $j -eq $ballX ]]; then
                printf 'O'
            elif [[ $j -eq 2 && $i -ge $player1Y && $i -lt $((player1Y + paddleSize)) ]]; then
                printf '#'
            elif [[ $j -eq $((width - 3)) && $i -ge $player2Y && $i -lt $((player2Y + paddleSize)) ]]; then
                printf '#'
            elif [[ $j -eq $((width / 2)) ]]; then
                printf '|'
            else
                printf ' '
            fi
        done
        printf '|\n'
    done
    
    # Bottom border
    printf '='
    for ((i=0; i<width; i++)); do printf '='; done
    printf '=\n'
}

handle_input() {
    local key=$(get_key)
    case $key in
        'q'|'Q') gameOver=1 ;;
        'w'|'W') [[ $BOT_MODE -ne 2 && $player1Y -gt 0 ]] && ((player1Y--)) ;;
        's'|'S') [[ $BOT_MODE -ne 2 && $player1Y -lt $((height - paddleSize)) ]] && ((player1Y++)) ;;
        'i'|'I') [[ $BOT_MODE -eq 0 && $player2Y -gt 0 ]] && ((player2Y--)) ;;
        'k'|'K') [[ $BOT_MODE -eq 0 && $player2Y -lt $((height - paddleSize)) ]] && ((player2Y++)) ;;
    esac
}

update_smart_bot() {
    local paddle_var=$1
    local paddle_y=$(eval echo \$$paddle_var)
    local paddle_center=$((paddle_y + paddleSize / 2))
    
    if [[ $ballY -lt $paddle_center && $paddle_y -gt 0 ]]; then
        ((paddle_y--))
    elif [[ $ballY -gt $paddle_center && $paddle_y -lt $((height - paddleSize)) ]]; then
        ((paddle_y++))
    fi
    
    eval $paddle_var=$paddle_y
}

update_patrol_bot() {
    ((player2Y += ai2Direction))
    if [[ $player2Y -le 0 ]]; then
        player2Y=0
        ai2Direction=1
    elif [[ $player2Y -ge $((height - paddleSize)) ]]; then
        player2Y=$((height - paddleSize))
        ai2Direction=-1
    fi
}

game_logic() {
    ((frameCount++))
    
    # Ball movement
    ((ballX += ballDirX))
    ((ballY += ballDirY))
    
    # Wall collision
    if [[ $ballY -le 0 || $ballY -ge $((height - 1)) ]]; then
        ballDirY=$((ballDirY * -1))
        [[ $ballY -le 0 ]] && ballY=0 || ballY=$((height - 1))
    fi
    
    # Paddle collision
    if [[ $ballX -eq 3 && $ballY -ge $player1Y && $ballY -lt $((player1Y + paddleSize)) && $ballDirX -lt 0 ]]; then
        ballDirX=1
        ((hitCount++))
        [[ $((hitCount % 3)) -eq 0 && $ballSpeed -lt 5 ]] && ((ballSpeed++))
    fi
    
    if [[ $ballX -eq $((width - 4)) && $ballY -ge $player2Y && $ballY -lt $((player2Y + paddleSize)) && $ballDirX -gt 0 ]]; then
        ballDirX=-1
        ((hitCount++))
        [[ $((hitCount % 3)) -eq 0 && $ballSpeed -lt 5 ]] && ((ballSpeed++))
    fi
    
    # AI updates
    case $BOT_MODE in
        1) update_smart_bot player2Y ;;
        2) update_smart_bot player1Y; update_patrol_bot ;;
    esac
    
    # Scoring
    if [[ $ballX -le 0 ]]; then
        ((player2Score++))
        ballX=$((width / 2))
        ballY=$((height / 2))
        ballDirX=1
        ballSpeed=1
        hitCount=0
    fi
    
    if [[ $ballX -ge $((width - 1)) ]]; then
        ((player1Score++))
        ballX=$((width / 2))
        ballY=$((height / 2))
        ballDirX=-1
        ballSpeed=1
        hitCount=0
    fi
    
    # Win condition
    if [[ $player1Score -ge 5 || $player2Score -ge 5 ]]; then
        clear
        echo "🏆 GAME OVER!"
        echo "Final Score: $player1Score - $player2Score"
        
        case $BOT_MODE in
            0) [[ $player1Score -gt $player2Score ]] && echo "🎉 Player 1 Wins!" || echo "🎉 Player 2 Wins!" ;;
            1) [[ $player1Score -gt $player2Score ]] && echo "🎉 You Win!" || echo "🤖 Bot Wins!" ;;
            2) [[ $player1Score -gt $player2Score ]] && echo "🧠 Smart Bot Wins!" || echo "🤖 Patrol Bot Wins!" ;;
        esac
        gameOver=1
    fi
}

show_menu() {
    clear
    echo "🏓 Welcome to Terminal Pong! 🏓"
    echo "==============================="
    echo "Choose game mode:"
    echo "1. 🧠 Human vs Bot"
    echo "2. 👥 Human vs Human"
    echo "3. 🤖 Bot vs Bot (Demo)"
    echo "4. ❌ Exit"
    echo "==============================="
    echo -n "Enter your choice (1-4): "
}

play_game() {
    local mode=$1
    local mode_desc=$2
    
    BOT_MODE=$mode
    
    clear
    echo "$mode_desc PONG"
    
    case $mode in
        0) echo "Player 1: W (up) / S (down)"
           echo "Player 2: I (up) / K (down)" ;;
        1) echo "You: W (up) / S (down)"
           echo "Bot: Auto-follows ball" ;;
        2) echo "Smart Bot vs Patrol Bot"
           echo "Just watch them play!" ;;
    esac
    
    echo "Press Q to quit anytime"
    echo "Speed increases every 3 hits!"
    echo "Starting in 2 seconds..."
    sleep 2
    
    setup_terminal
    setup_game
    gameOver=0
    player1Score=0
    player2Score=0
    frameCount=0
    
    while [[ $gameOver -eq 0 ]]; do
        draw_game
        handle_input
        game_logic
        
        # Speed delay
        case $ballSpeed in
            1) sleep 0.14 ;;
            2) sleep 0.11 ;;
            3) sleep 0.08 ;;
            4) sleep 0.055 ;;
            *) sleep 0.035 ;;
        esac
    done
    
    restore_terminal
    echo "Press Enter to return to menu..."
    read
}

# Main game loop
trap restore_terminal EXIT

while true; do
    show_menu
    read -n1 choice
    echo
    
    case $choice in
        '1') play_game 1 "🧠 HUMAN vs BOT" ;;
        '2') play_game 0 "👥 HUMAN vs HUMAN" ;;
        '3') play_game 2 "🤖 BOT vs BOT" ;;
        '4') echo "👋 Thanks for playing!"; break ;;
        *) echo "❌ Invalid choice! Please try again."; sleep 1 ;;
    esac
done
