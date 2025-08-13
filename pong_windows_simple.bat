@echo off
chcp 65001 >nul 2>nul
title Terminal Pong Game

echo ================================================
echo          Terminal Pong Game for Windows
echo ================================================

:: Check if g++ is available
where g++ >nul 2>nul
if %errorlevel% neq 0 (
    echo [ERROR] g++ compiler not found!
    echo.
    echo Please install one of the following:
    echo   1. MinGW-w64: https://www.mingw-w64.org/
    echo   2. MSYS2: https://www.msys2.org/
    echo   3. Git for Windows (includes g++)
    echo.
    echo After installation, restart Command Prompt and try again.
    pause
    exit /b 1
)

echo [OK] Compiler detected
echo.

:: Create temporary directory
set TEMP_DIR=%TEMP%\pong_%RANDOM%
mkdir "%TEMP_DIR%" >nul 2>nul
cd /d "%TEMP_DIR%"

:: Create simplified C++ source
echo Creating game source...
(
echo #include ^<iostream^>
echo #include ^<cstdlib^>
echo #include ^<ctime^>
echo #include ^<windows.h^>
echo #include ^<conio.h^>
echo using namespace std;
echo.
echo #ifndef BOT_MODE
echo #define BOT_MODE 1
echo #endif
echo.
echo bool gameOver = false;
echo int ballX = 20, ballY = 9, ballDirX = 1, ballDirY = 1;
echo int player1Y = 7, player2Y = 7, p1Score = 0, p2Score = 0;
echo int frameCount = 0, ballSpeed = 1, hitCount = 0;
echo.
echo void gotoxy^(int x, int y^) {
echo     COORD coord = {x, y};
echo     SetConsoleCursorPosition^(GetStdHandle^(STD_OUTPUT_HANDLE^), coord^);
echo }
echo.
echo void setup^(^) {
echo     srand^(time^(0^)^);
echo     ballDirX = ^(rand^(^) %% 2 == 0^) ? 1 : -1;
echo     ballDirY = ^(rand^(^) %% 2 == 0^) ? 1 : -1;
echo }
echo.
echo void draw^(^) {
echo     system^("cls"^);
echo     if^(BOT_MODE == 0^) cout ^<^< "HUMAN vs HUMAN";
echo     else if^(BOT_MODE == 1^) cout ^<^< "HUMAN vs BOT";
echo     else cout ^<^< "BOT vs BOT";
echo     cout ^<^< " ^| Score: " ^<^< p1Score ^<^< "-" ^<^< p2Score ^<^< " ^| Speed: " ^<^< ballSpeed ^<^< "x\\n";
echo     
echo     if^(BOT_MODE == 0^) cout ^<^< "Controls: W/S ^(P1^), I/K ^(P2^), Q=quit\\n";
echo     else if^(BOT_MODE == 1^) cout ^<^< "Controls: W/S ^(You^), Q=quit\\n";
echo     else cout ^<^< "Controls: Q=quit ^(watch bots^)\\n";
echo     
echo     for^(int i=0; i^<42; i++^) cout ^<^< "=";
echo     cout ^<^< "\\n";
echo     
echo     for^(int i=0; i^<18; i++^) {
echo         cout ^<^< "^|";
echo         for^(int j=0; j^<40; j++^) {
echo             if^(i == ballY ^&^& j == ballX^) cout ^<^< "O";
echo             else if^(j == 2 ^&^& i ^>= player1Y ^&^& i ^< player1Y+4^) cout ^<^< "#";
echo             else if^(j == 37 ^&^& i ^>= player2Y ^&^& i ^< player2Y+4^) cout ^<^< "#";
echo             else if^(j == 20^) cout ^<^< "^|";
echo             else cout ^<^< " ";
echo         }
echo         cout ^<^< "^|\\n";
echo     }
echo     
echo     for^(int i=0; i^<42; i++^) cout ^<^< "=";
echo     cout ^<^< "\\n";
echo }
echo.
echo void input^(^) {
echo     if^(_kbhit^(^)^) {
echo         char key = _getch^(^);
echo         if^(key == 'q' ^|^| key == 'Q'^) gameOver = true;
echo         if^(key == 'w' ^&^& BOT_MODE != 2 ^&^& player1Y ^> 0^) player1Y--;
echo         if^(key == 's' ^&^& BOT_MODE != 2 ^&^& player1Y ^< 14^) player1Y++;
echo         if^(key == 'i' ^&^& BOT_MODE == 0 ^&^& player2Y ^> 0^) player2Y--;
echo         if^(key == 'k' ^&^& BOT_MODE == 0 ^&^& player2Y ^< 14^) player2Y++;
echo     }
echo }
echo.
echo void logic^(^) {
echo     frameCount++;
echo     ballX += ballDirX;
echo     ballY += ballDirY;
echo     
echo     if^(ballY ^<= 0 ^|^| ballY ^>= 17^) ballDirY = -ballDirY;
echo     
echo     if^(ballX == 3 ^&^& ballY ^>= player1Y ^&^& ballY ^< player1Y+4 ^&^& ballDirX ^< 0^) {
echo         ballDirX = 1; hitCount++; if^(hitCount %% 3 == 0 ^&^& ballSpeed ^< 5^) ballSpeed++;
echo     }
echo     if^(ballX == 36 ^&^& ballY ^>= player2Y ^&^& ballY ^< player2Y+4 ^&^& ballDirX ^> 0^) {
echo         ballDirX = -1; hitCount++; if^(hitCount %% 3 == 0 ^&^& ballSpeed ^< 5^) ballSpeed++;
echo     }
echo     
echo     if^(BOT_MODE == 1^) {
echo         if^(ballY ^< player2Y+2 ^&^& player2Y ^> 0^) player2Y--;
echo         if^(ballY ^> player2Y+2 ^&^& player2Y ^< 14^) player2Y++;
echo     }
echo     if^(BOT_MODE == 2^) {
echo         if^(ballY ^< player1Y+2 ^&^& player1Y ^> 0^) player1Y--;
echo         if^(ballY ^> player1Y+2 ^&^& player1Y ^< 14^) player1Y++;
echo         if^(ballY ^< player2Y+2 ^&^& player2Y ^> 0^) player2Y--;
echo         if^(ballY ^> player2Y+2 ^&^& player2Y ^< 14^) player2Y++;
echo     }
echo     
echo     if^(ballX ^<= 0^) { p2Score++; ballX=20; ballY=9; ballDirX=1; ballSpeed=1; hitCount=0; }
echo     if^(ballX ^>= 39^) { p1Score++; ballX=20; ballY=9; ballDirX=-1; ballSpeed=1; hitCount=0; }
echo     
echo     if^(p1Score ^>= 5 ^|^| p2Score ^>= 5^) {
echo         system^("cls"^);
echo         cout ^<^< "GAME OVER! Final Score: " ^<^< p1Score ^<^< "-" ^<^< p2Score ^<^< "\\n";
echo         if^(BOT_MODE == 0^) cout ^<^< ^(p1Score ^> p2Score ? "Player 1 Wins!" : "Player 2 Wins!"^);
echo         else if^(BOT_MODE == 1^) cout ^<^< ^(p1Score ^> p2Score ? "You Win!" : "Bot Wins!"^);
echo         else cout ^<^< ^(p1Score ^> p2Score ? "Bot 1 Wins!" : "Bot 2 Wins!"^);
echo         cout ^<^< "\\n"; gameOver = true;
echo     }
echo }
echo.
echo int main^(^) {
echo     system^("cls"^);
echo     cout ^<^< "Starting Terminal Pong...\\n";
echo     if^(BOT_MODE == 0^) cout ^<^< "HUMAN vs HUMAN MODE\\n";
echo     else if^(BOT_MODE == 1^) cout ^<^< "HUMAN vs BOT MODE\\n";
echo     else cout ^<^< "BOT vs BOT DEMO\\n";
echo     cout ^<^< "Press any key to start..."; _getch^(^);
echo     
echo     setup^(^);
echo     while^(^!gameOver^) {
echo         draw^(^); input^(^); logic^(^);
echo         int delay = ballSpeed == 1 ? 200 : ballSpeed == 2 ? 150 : ballSpeed == 3 ? 100 : ballSpeed == 4 ? 70 : 50;
echo         Sleep^(delay^);
echo     }
echo     cout ^<^< "\\nThanks for playing! Press any key to exit..."; _getch^(^);
echo     return 0;
echo }
) > pong_simple.cpp

echo.
echo === TERMINAL PONG GAME ===
echo.
echo Choose game mode:
echo   1. Human vs Bot
echo   2. Human vs Human
echo   3. Bot vs Bot (Demo)
echo.
set /p choice="Enter choice (1-3): "

if "%choice%"=="1" (
    echo.
    echo Compiling Human vs Bot mode...
    g++ -DBOT_MODE=1 pong_simple.cpp -o pong.exe 2>nul
    if %errorlevel% equ 0 (
        echo [OK] Starting game...
        pong.exe
    ) else (
        echo [ERROR] Compilation failed
    )
) else if "%choice%"=="2" (
    echo.
    echo Compiling Human vs Human mode...
    g++ -DBOT_MODE=0 pong_simple.cpp -o pong.exe 2>nul
    if %errorlevel% equ 0 (
        echo [OK] Starting game...
        pong.exe
    ) else (
        echo [ERROR] Compilation failed
    )
) else if "%choice%"=="3" (
    echo.
    echo Compiling Bot vs Bot demo...
    g++ -DBOT_MODE=2 pong_simple.cpp -o pong.exe 2>nul
    if %errorlevel% equ 0 (
        echo [OK] Starting demo...
        pong.exe
    ) else (
        echo [ERROR] Compilation failed
    )
) else (
    echo [ERROR] Invalid choice: %choice%
)

:: Cleanup
cd /d %USERPROFILE%
if exist "%TEMP_DIR%" rmdir /s /q "%TEMP_DIR%" >nul 2>nul

echo.
echo Thanks for playing Terminal Pong!
echo Visit: https://github.com/TomDevX/terminal-pong
pause
