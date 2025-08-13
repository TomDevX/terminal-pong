#!/bin/bash

echo "🏓 Welcome to Pong Game! 🏓"
echo ""
echo "Choose game mode:"
echo "1. 🧠 Human vs Bot"
echo "2. 👥 Human vs Human"
echo "3. 🤖 Bot vs Bot"
echo ""
read -p "Enter your choice (1-3): " choice

case $choice in
    1)
        echo "🧠 Starting Human vs Bot mode..."
        g++ -std=c++11 -DBOT_MODE=1 pong_stable_fixed.cpp -o pong_game
        if [ $? -eq 0 ]; then
            echo "✅ Ready to challenge the bot!"
            echo "Controls: Use W/S to control your paddle"
            echo "Features: Speed increases every 3 hits!"
            echo ""
            ./pong_game
        else
            echo "❌ Compilation error!"
        fi
        ;;
    2)
        echo "👥 Starting Human vs Human mode..."
        g++ -std=c++11 -DBOT_MODE=0 pong_stable_fixed.cpp -o pong_game
        if [ $? -eq 0 ]; then
            echo "✅ Ready to play!"
            echo "Controls: Player 1 (W/S), Player 2 (I/K)"
            echo "Features: Speed increases every 3 hits!"
            echo ""
            ./pong_game
        else
            echo "❌ Compilation error!"
        fi
        ;;
    3)
        echo "🤖 Starting Bot vs Bot demo..."
        g++ -std=c++11 -DBOT_MODE=2 pong_stable_fixed.cpp -o pong_game
        if [ $? -eq 0 ]; then
            echo "✅ Watch the bots play!"
            echo "Smart Bot vs Patrol Bot"
            echo "Features: Speed increases every 3 hits!"
            echo "Controls: Q to quit only"
            echo ""
            ./pong_game
        else
            echo "❌ Compilation error!"
        fi
        ;;
    *)
        echo "❌ Invalid choice. Please run the script again."
        ;;
esac