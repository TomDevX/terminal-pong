@echo off
:: 🏓 Terminal Pong Game - Windows Installer & Runner
:: Download this file and double-click to run, or run from Command Prompt

echo 🏓 Terminal Pong Game - Windows Installer
echo =============================================

:: Check if g++ is available
where g++ >nul 2>nul
if %errorlevel% neq 0 (
    echo ❌ g++ compiler not found!
    echo.
    echo Please install g++ first:
    echo   Option 1: Install MinGW-w64 from https://www.mingw-w64.org/
    echo   Option 2: Install MSYS2 from https://www.msys2.org/
    echo   Option 3: Install Visual Studio Build Tools
    echo   Option 4: Install Git Bash (includes g++)
    echo.
    pause
    exit /b 1
)

echo ✅ Compiler found!
g++ --version | findstr /C:"g++"

:: Create temporary directory
set TEMP_DIR=%TEMP%\terminal_pong_%RANDOM%
mkdir "%TEMP_DIR%"
cd /d "%TEMP_DIR%"

echo 📁 Creating game files...

:: Create the game source code
(
echo #include ^<iostream^>
echo #include ^<cstdlib^>
echo #include ^<ctime^>
echo #include ^<thread^>
echo #include ^<chrono^>
echo #include ^<conio.h^>
echo.
echo using namespace std;
echo.
echo #ifndef BOT_MODE
echo #define BOT_MODE 1  // 0=human vs human, 1=human vs bot, 2=bot vs bot
echo #endif
echo.
echo // Game variables
echo bool gameOver = false;
echo const int width = 40;
echo const int height = 18;
echo int ballX, ballY;
echo int ballDirX = 1, ballDirY = 1;
echo int player1Y, player2Y;
echo int player1Score = 0, player2Score = 0;
echo const int paddleSize = 4;
echo int frameCount = 0;
echo int ballSpeed = 1;
echo int hitCount = 0;
echo int ai2Direction = 1;
echo.
echo char getKey^(^) {
echo     if ^(_kbhit^(^)^) {
echo         return _getch^(^);
echo     }
echo     return 0;
echo }
echo.
echo void Setup^(^) {
echo     ballX = width / 2;
echo     ballY = height / 2;
echo     ballDirX = ^(rand^(^) %% 2 == 0^) ? 1 : -1;
echo     ballDirY = ^(rand^(^) %% 2 == 0^) ? 1 : -1;
echo     player1Y = height / 2 - paddleSize / 2;
echo     player2Y = height / 2 - paddleSize / 2;
echo     ballSpeed = 1;
echo     hitCount = 0;
echo     srand^(time^(0^)^);
echo }
echo.
echo void Draw^(^) {
echo     system^("cls"^);
echo     
echo     if ^(BOT_MODE == 0^) {
echo         cout ^<^< "👥 HUMAN vs HUMAN";
echo     } else if ^(BOT_MODE == 1^) {
echo         cout ^<^< "🧠 HUMAN vs BOT";
echo     } else {
echo         cout ^<^< "🤖 BOT vs BOT";
echo     }
echo     
echo     cout ^<^< " ^(Frame: " ^<^< frameCount ^<^< "^)" ^<^< endl;
echo     cout ^<^< "Score: P1=" ^<^< player1Score ^<^< " P2=" ^<^< player2Score ^<^< " | Speed: " ^<^< ballSpeed ^<^< "x | Hits: " ^<^< hitCount ^<^< endl;
echo     
echo     if ^(BOT_MODE == 0^) {
echo         cout ^<^< "Controls: W/S ^(P1^), I/K ^(P2^), Q=quit" ^<^< endl;
echo     } else if ^(BOT_MODE == 1^) {
echo         cout ^<^< "Controls: W/S ^(You^), Q=quit" ^<^< endl;
echo     } else {
echo         cout ^<^< "Controls: Q=quit ^(watch bots^)" ^<^< endl;
echo     }
echo     
echo     for ^(int i = 0; i ^< width + 2; i++^) cout ^<^< "=";
echo     cout ^<^< endl;
echo     
echo     for ^(int i = 0; i ^< height; i++^) {
echo         cout ^<^< "|";
echo         for ^(int j = 0; j ^< width; j++^) {
echo             if ^(i == ballY ^&^& j == ballX^) {
echo                 cout ^<^< "O";
echo             } else if ^(j == 2 ^&^& i ^>= player1Y ^&^& i ^< player1Y + paddleSize^) {
echo                 cout ^<^< "#";
echo             } else if ^(j == width - 3 ^&^& i ^>= player2Y ^&^& i ^< player2Y + paddleSize^) {
echo                 cout ^<^< "#";
echo             } else if ^(j == width / 2^) {
echo                 cout ^<^< "|";
echo             } else {
echo                 cout ^<^< " ";
echo             }
echo         }
echo         cout ^<^< "|" ^<^< endl;
echo     }
echo     
echo     for ^(int i = 0; i ^< width + 2; i++^) cout ^<^< "=";
echo     cout ^<^< endl;
echo }
echo.
echo void Input^(^) {
echo     char key = getKey^(^);
echo     if ^(key == 'q' ^|^| key == 'Q'^) {
echo         gameOver = true;
echo     }
echo     if ^(key == 'w' ^|^| key == 'W'^) {
echo         if ^(BOT_MODE != 2 ^&^& player1Y ^> 0^) player1Y--;
echo     }
echo     if ^(key == 's' ^|^| key == 'S'^) {
echo         if ^(BOT_MODE != 2 ^&^& player1Y + paddleSize ^< height^) player1Y++;
echo     }
echo     if ^(key == 'i' ^|^| key == 'I'^) {
echo         if ^(BOT_MODE == 0 ^&^& player2Y ^> 0^) player2Y--;
echo     }
echo     if ^(key == 'k' ^|^| key == 'K'^) {
echo         if ^(BOT_MODE == 0 ^&^& player2Y + paddleSize ^< height^) player2Y++;
echo     }
echo }
echo.
echo void UpdateSmartBot^(int ^&paddleY^) {
echo     if ^(ballY ^< paddleY + paddleSize / 2 ^&^& paddleY ^> 0^) {
echo         paddleY--;
echo     } else if ^(ballY ^> paddleY + paddleSize / 2 ^&^& paddleY + paddleSize ^< height^) {
echo         paddleY++;
echo     }
echo }
echo.
echo void UpdatePatrolBot^(int ^&paddleY, int ^&direction^) {
echo     paddleY += direction;
echo     if ^(paddleY ^<= 0^) {
echo         paddleY = 0;
echo         direction = 1;
echo     } else if ^(paddleY + paddleSize ^>= height^) {
echo         paddleY = height - paddleSize;
echo         direction = -1;
echo     }
echo }
echo.
echo void Logic^(^) {
echo     frameCount++;
echo     
echo     ballX += ballDirX;
echo     ballY += ballDirY;
echo     
echo     if ^(ballY ^<= 0 ^|^| ballY ^>= height - 1^) {
echo         ballDirY = -ballDirY;
echo         ballY = ^(ballY ^<= 0^) ? 0 : height - 1;
echo     }
echo     
echo     if ^(ballX == 3 ^&^& ballY ^>= player1Y ^&^& ballY ^< player1Y + paddleSize ^&^& ballDirX ^< 0^) {
echo         ballDirX = 1;
echo         hitCount++;
echo         if ^(hitCount %% 3 == 0 ^&^& ballSpeed ^< 5^) {
echo             ballSpeed++;
echo         }
echo     }
echo     if ^(ballX == width - 4 ^&^& ballY ^>= player2Y ^&^& ballY ^< player2Y + paddleSize ^&^& ballDirX ^> 0^) {
echo         ballDirX = -1;
echo         hitCount++;
echo         if ^(hitCount %% 3 == 0 ^&^& ballSpeed ^< 5^) {
echo             ballSpeed++;
echo         }
echo     }
echo     
echo     if ^(BOT_MODE == 1^) {
echo         UpdateSmartBot^(player2Y^);
echo     } else if ^(BOT_MODE == 2^) {
echo         UpdateSmartBot^(player1Y^);
echo         UpdatePatrolBot^(player2Y, ai2Direction^);
echo     }
echo     
echo     if ^(ballX ^<= 0^) {
echo         player2Score++;
echo         ballX = width / 2;
echo         ballY = height / 2;
echo         ballDirX = 1;
echo         ballSpeed = 1;
echo         hitCount = 0;
echo     }
echo     
echo     if ^(ballX ^>= width - 1^) {
echo         player1Score++;
echo         ballX = width / 2;
echo         ballY = height / 2;
echo         ballDirX = -1;
echo         ballSpeed = 1;
echo         hitCount = 0;
echo     }
echo     
echo     if ^(player1Score ^>= 5 ^|^| player2Score ^>= 5^) {
echo         system^("cls"^);
echo         cout ^<^< "🏆 GAME OVER!" ^<^< endl;
echo         cout ^<^< "Final Score: " ^<^< player1Score ^<^< " - " ^<^< player2Score ^<^< endl;
echo         
echo         if ^(BOT_MODE == 0^) {
echo             cout ^<^< ^(player1Score ^> player2Score ? "🎉 Player 1 Wins!" : "🎉 Player 2 Wins!"^) ^<^< endl;
echo         } else if ^(BOT_MODE == 1^) {
echo             cout ^<^< ^(player1Score ^> player2Score ? "🎉 You Win!" : "🤖 Bot Wins!"^) ^<^< endl;
echo         } else {
echo             cout ^<^< ^(player1Score ^> player2Score ? "🧠 Smart Bot Wins!" : "🤖 Patrol Bot Wins!"^) ^<^< endl;
echo         }
echo         gameOver = true;
echo     }
echo }
echo.
echo int main^(^) {
echo     system^("cls"^);
echo     
echo     if ^(BOT_MODE == 0^) {
echo         cout ^<^< "👥 HUMAN vs HUMAN PONG" ^<^< endl;
echo         cout ^<^< "Player 1: W ^(up^) / S ^(down^)" ^<^< endl;
echo         cout ^<^< "Player 2: I ^(up^) / K ^(down^)" ^<^< endl;
echo     } else if ^(BOT_MODE == 1^) {
echo         cout ^<^< "🧠 HUMAN vs BOT PONG" ^<^< endl;
echo         cout ^<^< "You: W ^(up^) / S ^(down^)" ^<^< endl;
echo         cout ^<^< "Bot: Auto-follows ball" ^<^< endl;
echo     } else {
echo         cout ^<^< "🤖 BOT vs BOT DEMO" ^<^< endl;
echo         cout ^<^< "Smart Bot vs Patrol Bot" ^<^< endl;
echo         cout ^<^< "Just watch them play!" ^<^< endl;
echo     }
echo     
echo     cout ^<^< "Press Q to quit anytime" ^<^< endl;
echo     cout ^<^< "Speed increases every 3 hits!" ^<^< endl;
echo     cout ^<^< "Starting in 2 seconds..." ^<^< endl;
echo     this_thread::sleep_for^(chrono::seconds^(2^)^);
echo     
echo     Setup^(^);
echo     
echo     while ^(^!gameOver^) {
echo         Draw^(^);
echo         Input^(^);
echo         Logic^(^);
echo         
echo         int delay;
echo         if ^(ballSpeed == 1^) delay = 140;
echo         else if ^(ballSpeed == 2^) delay = 110;
echo         else if ^(ballSpeed == 3^) delay = 80;
echo         else if ^(ballSpeed == 4^) delay = 55;
echo         else delay = 35;
echo         
echo         this_thread::sleep_for^(chrono::milliseconds^(delay^)^);
echo     }
echo     
echo     return 0;
echo }
) > pong_game.cpp

echo 🏓 Welcome to Terminal Pong! 🏓
echo.
echo Choose game mode:
echo 1. 🧠 Human vs Bot
echo 2. 👥 Human vs Human  
echo 3. 🤖 Bot vs Bot
echo.
set /p choice="Enter your choice (1-3): "

if "%choice%"=="1" (
    echo 🧠 Starting Human vs Bot mode...
    g++ -std=c++11 -DBOT_MODE=1 pong_game.cpp -o pong_game.exe
    if %errorlevel% equ 0 (
        echo ✅ Ready to challenge the bot!
        echo Controls: Use W/S to control your paddle
        echo Features: Speed increases every 3 hits!
        echo.
        pong_game.exe
    ) else (
        echo ❌ Compilation error!
    )
) else if "%choice%"=="2" (
    echo 👥 Starting Human vs Human mode...
    g++ -std=c++11 -DBOT_MODE=0 pong_game.cpp -o pong_game.exe
    if %errorlevel% equ 0 (
        echo ✅ Ready to play!
        echo Controls: Player 1 (W/S), Player 2 (I/K)
        echo Features: Speed increases every 3 hits!
        echo.
        pong_game.exe
    ) else (
        echo ❌ Compilation error!
    )
) else if "%choice%"=="3" (
    echo 🤖 Starting Bot vs Bot demo...
    g++ -std=c++11 -DBOT_MODE=2 pong_game.cpp -o pong_game.exe
    if %errorlevel% equ 0 (
        echo ✅ Watch the bots play!
        echo Smart Bot vs Patrol Bot
        echo Features: Speed increases every 3 hits!
        echo Controls: Q to quit only
        echo.
        pong_game.exe
    ) else (
        echo ❌ Compilation error!
    )
) else (
    echo ❌ Invalid choice. Please run the script again.
)

:: Cleanup
cd /d "%USERPROFILE%"
rmdir /s /q "%TEMP_DIR%"

echo.
echo 🎉 Thanks for playing Terminal Pong!
echo 💾 To install permanently, visit: https://github.com/TomDevX/terminal-pong
pause
