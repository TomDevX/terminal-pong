@echo off
chcp 65001 >nul 2>nul
title Terminal Pong Game - Auto Installer

echo ================================================
echo     Terminal Pong Game - Auto Installer
echo ================================================

:: Check if running as Administrator
net session >nul 2>&1
if %errorlevel% neq 0 (
    echo [INFO] This script will try to install dependencies automatically.
    echo [INFO] For best results, run as Administrator.
    echo.
    timeout /t 3 >nul
)

:: Check if g++ is available
echo Checking for C++ compiler...
where g++ >nul 2>nul
if %errorlevel% neq 0 (
    echo [WARNING] g++ compiler not found!
    echo.
    echo Attempting automatic installation...
    echo.
    
    :: Try Chocolatey first
    where choco >nul 2>nul
    if %errorlevel% equ 0 (
        echo [INFO] Found Chocolatey. Installing MinGW...
        choco install mingw -y
        echo.
        echo [INFO] Refreshing PATH...
        call refreshenv
        
        :: Check again
        where g++ >nul 2>nul
        if %errorlevel% equ 0 (
            echo [SUCCESS] g++ installed successfully!
        ) else (
            echo [WARNING] g++ installation may need PATH refresh.
            echo [INFO] Please restart Command Prompt and try again.
            echo.
            set /p continue="Continue anyway? (y/n): "
            if /i "!continue!"=="n" (
                pause
                exit /b 1
            )
        )
    ) else (
        echo [INFO] Chocolatey not found. Installing Chocolatey first...
        echo.
        
        :: Install Chocolatey
        powershell -Command "Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))"
        
        if %errorlevel% equ 0 (
            echo [SUCCESS] Chocolatey installed!
            echo [INFO] Installing MinGW...
            
            :: Refresh PATH and install MinGW
            call refreshenv
            choco install mingw -y
            
            :: Check if g++ is now available
            where g++ >nul 2>nul
            if %errorlevel% equ 0 (
                echo [SUCCESS] g++ installed successfully!
            ) else (
                echo [WARNING] Automatic installation completed.
                echo [INFO] Please restart Command Prompt and try again.
                echo.
                echo Manual install option:
                echo   Download Git for Windows: https://git-scm.com/download/win
                echo.
                set /p continue="Continue anyway? (y/n): "
                if /i "!continue!"=="n" (
                    pause
                    exit /b 1
                )
            )
        ) else (
            echo [ERROR] Failed to install Chocolatey automatically.
            echo.
            echo MANUAL INSTALLATION REQUIRED:
            echo.
            echo Option 1 - Git for Windows (Easiest):
            echo   1. Download: https://git-scm.com/download/win
            echo   2. Install with default options
            echo   3. Restart Command Prompt
            echo.
            echo Option 2 - MSYS2:
            echo   1. Download: https://www.msys2.org/
            echo   2. Install and follow setup instructions
            echo.
            echo Option 3 - Visual Studio Build Tools:
            echo   1. Download: https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2022
            echo.
            set /p continue="Continue without compiler? (y/n): "
            if /i "!continue!"=="n" (
                pause
                exit /b 1
            )
        )
    )
) else (
    echo [OK] Compiler detected: 
    g++ --version | head -1
)

echo.
echo ================================================
echo.

:: Create temporary directory
set TEMP_DIR=%TEMP%\pong_%RANDOM%
mkdir "%TEMP_DIR%" >nul 2>nul
cd /d "%TEMP_DIR%"

:: Create C++ source code
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
) > pong_game.cpp

echo.
echo === TERMINAL PONG GAME ===
echo.
echo Choose game mode:
echo   1. Human vs Bot
echo   2. Human vs Human  
echo   3. Bot vs Bot (Demo)
echo.
set /p choice="Enter choice (1-3): "

:: Check if compiler is available for compilation
where g++ >nul 2>nul
set COMPILER_AVAILABLE=%errorlevel%

if "%choice%"=="1" (
    echo.
    if %COMPILER_AVAILABLE% equ 0 (
        echo Compiling Human vs Bot mode...
        g++ -DBOT_MODE=1 pong_game.cpp -o pong.exe 2>nul
        if %errorlevel% equ 0 (
            echo [OK] Starting game...
            echo.
            pong.exe
        ) else (
            echo [ERROR] Compilation failed. Check your g++ installation.
        )
    ) else (
        echo [ERROR] No compiler available. Installation may have failed.
        echo Please restart Command Prompt and try again.
    )
) else if "%choice%"=="2" (
    echo.
    if %COMPILER_AVAILABLE% equ 0 (
        echo Compiling Human vs Human mode...
        g++ -DBOT_MODE=0 pong_game.cpp -o pong.exe 2>nul
        if %errorlevel% equ 0 (
            echo [OK] Starting game...
            echo.
            pong.exe
        ) else (
            echo [ERROR] Compilation failed. Check your g++ installation.
        )
    ) else (
        echo [ERROR] No compiler available. Installation may have failed.
        echo Please restart Command Prompt and try again.
    )
) else if "%choice%"=="3" (
    echo.
    if %COMPILER_AVAILABLE% equ 0 (
        echo Compiling Bot vs Bot demo...
        g++ -DBOT_MODE=2 pong_game.cpp -o pong.exe 2>nul
        if %errorlevel% equ 0 (
            echo [OK] Starting demo...
            echo.
            pong.exe
        ) else (
            echo [ERROR] Compilation failed. Check your g++ installation.
        )
    ) else (
        echo [ERROR] No compiler available. Installation may have failed.
        echo Please restart Command Prompt and try again.
    )
) else (
    echo [ERROR] Invalid choice: %choice%
)

:: Cleanup
cd /d %USERPROFILE%
if exist "%TEMP_DIR%" rmdir /s /q "%TEMP_DIR%" >nul 2>nul

echo.
echo ================================================
echo Thanks for playing Terminal Pong!
echo.
echo If you had issues, try:
echo   1. Run as Administrator
echo   2. Restart Command Prompt after installation
echo   3. Visit: https://github.com/TomDevX/terminal-pong
echo ================================================
pause
