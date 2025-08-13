#!/bin/bash

echo "🏓 Welcome to Pong Game Collection! 🏓"
echo ""
echo "Choose game version:"
echo "1. Enhanced Pong (Fast Ball + Two Players)"
echo "2. Auto Demo (AI vs AI)"
echo "3. Interactive Play (Player vs AI)"
echo "4. Exit"
echo ""
read -p "Enter your choice (1-4): " choice

case $choice in
    1)
        echo "Compiling Enhanced Pong..."
        g++ -std=c++11 test.cpp -o enhanced_pong
        if [ $? -eq 0 ]; then
            echo "Starting Enhanced Pong Game..."
            ./enhanced_pong
        else
            echo "Compilation error!"
        fi
        ;;
    2)
        echo "Compiling demo version..."
        g++ -std=c++11 pong_simple.cpp -o pong_simple
        if [ $? -eq 0 ]; then
            echo "Starting demo game..."
            echo "Press Enter to begin!"
            ./pong_simple
        else
            echo "Compilation error!"
        fi
        ;;
    3)
        echo "Compiling interactive version..."
        g++ -std=c++11 pong_interactive.cpp -o pong_interactive
        if [ $? -eq 0 ]; then
            echo "Starting interactive game..."
            ./pong_interactive
        else
            echo "Compilation error!"
        fi
        ;;
    4)
        echo "Goodbye!"
        exit 0
        ;;
    *)
        echo "Invalid choice!"
        ;;
esac
