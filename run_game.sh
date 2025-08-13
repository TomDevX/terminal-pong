#!/bin/bash

echo "🏓 Welcome to Pong Game! 🏓"
echo ""
echo "Choose game mode:"
echo "1. 👥 Human vs Human"
echo "2. 🧠 Human vs Bot"
echo "3. 🤖 Bot vs Bot (Demo)"
echo "4. 🛡️ Stable Version (Fixed disappearing screen)"
echo "5. 🔧 Ultra Simple (If controls don't work)"
echo "6. Exit"
echo ""
read -p "Enter your choice (1-6): " choice

case $choice in
    1)
        echo "👥 Starting Human vs Human mode..."
        g++ -std=c++11 -DBOT_MODE=0 pong_working.cpp -o pong_game
        if [ $? -eq 0 ]; then
            echo "✅ Ready to play!"
            echo "Controls: Player 1 (W/S), Player 2 (I/K)"
            echo "🔧 This version includes input testing and debug output"
            echo ""
            ./pong_game
        else
            echo "❌ Compilation error!"
        fi
        ;;
    2)
        echo "🧠 Starting Human vs Bot mode..."
        g++ -std=c++11 -DBOT_MODE=1 pong_working.cpp -o pong_game
        if [ $? -eq 0 ]; then
            echo "✅ Ready to challenge the bot!"
            echo "Controls: Use W/S to control your paddle"
            echo "The bot will intelligently follow the ball"
            echo ""
            ./pong_game
        else
            echo "❌ Compilation error!"
        fi
        ;;
    3)
        echo "🤖 Starting Bot vs Bot demo..."
        g++ -std=c++11 -DBOT_MODE=2 pong_working.cpp -o pong_game
        if [ $? -eq 0 ]; then
            echo "✅ Watch the bots play!"
            echo "Smart Bot (left) vs Patrol Bot (right)"
            echo "Press Q to quit during the game"
            echo ""
            ./pong_game
        else
            echo "❌ Compilation error!"
        fi
        ;;
    4)
        echo "🛡️ Starting Stable version (Fixed disappearing screen)..."
        echo "Choose sub-mode:"
        echo "  a) Human vs Human"
        echo "  b) Human vs Bot" 
        echo "  c) Bot vs Bot"
        read -p "Enter choice (a/b/c): " submode
        
        case $submode in
            a)
                g++ -std=c++11 -DBOT_MODE=0 pong_stable_fixed.cpp -o pong_game
                echo "Human vs Human (Stable)"
                ;;
            b)
                g++ -std=c++11 -DBOT_MODE=1 pong_stable_fixed.cpp -o pong_game
                echo "Human vs Bot (Stable)"
                ;;
            c)
                g++ -std=c++11 -DBOT_MODE=2 pong_stable_fixed.cpp -o pong_game
                echo "Bot vs Bot (Stable)"
                ;;
            *)
                echo "Invalid choice, defaulting to Human vs Human"
                g++ -std=c++11 -DBOT_MODE=0 pong_stable_fixed.cpp -o pong_game
                ;;
        esac
        
        if [ $? -eq 0 ]; then
            echo "✅ Stable version compiled!"
            echo "🛡️ Features:"
            echo "   • No screen clearing during game"
            echo "   • Cursor positioning instead"
            echo "   • Debug mode (press D)"
            echo "   • Frame counter visible"
            echo ""
            ./pong_game
        else
            echo "❌ Compilation error!"
        fi
        ;;
    5)
        echo "🔧 Starting Ultra Simple version..."
        g++ -std=c++11 pong_ultra_simple.cpp -o pong_game
        if [ $? -eq 0 ]; then
            echo "✅ This version uses number input (guaranteed to work!)"
            echo "Controls: 1=P1↑ 2=P1↓ 8=P2↑ 9=P2↓ 0=Quit"
            echo "Perfect if keyboard controls don't work"
            echo ""
            ./pong_game
        else
            echo "❌ Compilation error!"
        fi
        ;;
    6)
        echo "👋 Goodbye!"
        exit 0
        ;;
    *)
        echo "❌ Invalid choice!"
        ;;
esac