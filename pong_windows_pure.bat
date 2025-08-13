@echo off
chcp 65001 >nul 2>nul
title Terminal Pong - Pure Windows Game

echo ================================================
echo          Terminal Pong - Pure Windows
echo ================================================
echo.
echo Creating game executable using built-in Windows tools...
echo.

:: Create temporary directory
set TEMP_DIR=%TEMP%\pong_%RANDOM%
mkdir "%TEMP_DIR%" >nul 2>nul
cd /d "%TEMP_DIR%"

:: Create C# source that compiles and runs the game
echo Creating game source...
(
echo using System;
echo using System.Threading;
echo using System.Runtime.InteropServices;
echo.
echo class PongGame {
echo     [DllImport^("kernel32.dll"^)]
echo     static extern IntPtr GetStdHandle^(int nStdHandle^);
echo     
echo     [DllImport^("kernel32.dll"^)]
echo     static extern bool SetConsoleCursorPosition^(IntPtr hConsoleOutput, COORD dwCursorPosition^);
echo     
echo     [DllImport^("kernel32.dll"^)]
echo     static extern bool GetConsoleScreenBufferInfo^(IntPtr hConsoleOutput, out CONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo^);
echo     
echo     [StructLayout^(LayoutKind.Sequential^)]
echo     public struct COORD {
echo         public short X;
echo         public short Y;
echo         public COORD^(short x, short y^) { X = x; Y = y; }
echo     }
echo     
echo     [StructLayout^(LayoutKind.Sequential^)]
echo     public struct CONSOLE_SCREEN_BUFFER_INFO {
echo         public COORD dwSize;
echo         public COORD dwCursorPosition;
echo         public short wAttributes;
echo         public SMALL_RECT srWindow;
echo         public COORD dwMaximumWindowSize;
echo     }
echo     
echo     [StructLayout^(LayoutKind.Sequential^)]
echo     public struct SMALL_RECT {
echo         public short Left;
echo         public short Top;
echo         public short Right;
echo         public short Bottom;
echo     }
echo     
echo     static IntPtr handle = GetStdHandle^(-11^);
echo     static bool gameOver = false;
echo     static int ballX = 20, ballY = 9, ballDirX = 1, ballDirY = 1;
echo     static int player1Y = 7, player2Y = 7, p1Score = 0, p2Score = 0;
echo     static int ballSpeed = 1, hitCount = 0;
echo     static int gameMode = 1; // 0=Human vs Human, 1=Human vs Bot, 2=Bot vs Bot
echo     static Random rand = new Random^(^);
echo     
echo     static void SetCursorPosition^(int x, int y^) {
echo         SetConsoleCursorPosition^(handle, new COORD^(^(short^)x, ^(short^)y^)^);
echo     }
echo     
echo     static void Setup^(^) {
echo         ballDirX = rand.Next^(2^) == 0 ? 1 : -1;
echo         ballDirY = rand.Next^(2^) == 0 ? 1 : -1;
echo         Console.CursorVisible = false;
echo     }
echo     
echo     static void Draw^(^) {
echo         Console.Clear^(^);
echo         string mode = gameMode == 0 ? "HUMAN vs HUMAN" : gameMode == 1 ? "HUMAN vs BOT" : "BOT vs BOT";
echo         Console.WriteLine^($"{mode} ^| Score: {p1Score}-{p2Score} ^| Speed: {ballSpeed}x"^);
echo         
echo         string controls = gameMode == 0 ? "Controls: W/S ^(P1^), I/K ^(P2^), Q=quit" :
echo                          gameMode == 1 ? "Controls: W/S ^(You^), Q=quit" :
echo                          "Controls: Q=quit ^(watch bots^)";
echo         Console.WriteLine^(controls^);
echo         Console.WriteLine^("=========================================="^);
echo         
echo         for^(int i = 0; i ^< 18; i++^) {
echo             Console.Write^("^|"^);
echo             for^(int j = 0; j ^< 40; j++^) {
echo                 if^(i == ballY ^&^& j == ballX^) Console.Write^("O"^);
echo                 else if^(j == 2 ^&^& i ^>= player1Y ^&^& i ^< player1Y + 4^) Console.Write^("#"^);
echo                 else if^(j == 37 ^&^& i ^>= player2Y ^&^& i ^< player2Y + 4^) Console.Write^("#"^);
echo                 else if^(j == 20^) Console.Write^("^|"^);
echo                 else Console.Write^(" "^);
echo             }
echo             Console.WriteLine^("^|"^);
echo         }
echo         Console.WriteLine^("=========================================="^);
echo     }
echo     
echo     static void Input^(^) {
echo         if^(Console.KeyAvailable^) {
echo             ConsoleKeyInfo key = Console.ReadKey^(true^);
echo             if^(key.Key == ConsoleKey.Q^) gameOver = true;
echo             if^(key.Key == ConsoleKey.W ^&^& gameMode != 2 ^&^& player1Y ^> 0^) player1Y--;
echo             if^(key.Key == ConsoleKey.S ^&^& gameMode != 2 ^&^& player1Y ^< 14^) player1Y++;
echo             if^(key.Key == ConsoleKey.I ^&^& gameMode == 0 ^&^& player2Y ^> 0^) player2Y--;
echo             if^(key.Key == ConsoleKey.K ^&^& gameMode == 0 ^&^& player2Y ^< 14^) player2Y++;
echo         }
echo     }
echo     
echo     static void Logic^(^) {
echo         ballX += ballDirX;
echo         ballY += ballDirY;
echo         
echo         if^(ballY ^<= 0 ^|^| ballY ^>= 17^) ballDirY = -ballDirY;
echo         
echo         if^(ballX == 3 ^&^& ballY ^>= player1Y ^&^& ballY ^< player1Y + 4 ^&^& ballDirX ^< 0^) {
echo             ballDirX = 1; hitCount++; 
echo             if^(hitCount %% 3 == 0 ^&^& ballSpeed ^< 5^) ballSpeed++;
echo         }
echo         if^(ballX == 36 ^&^& ballY ^>= player2Y ^&^& ballY ^< player2Y + 4 ^&^& ballDirX ^> 0^) {
echo             ballDirX = -1; hitCount++; 
echo             if^(hitCount %% 3 == 0 ^&^& ballSpeed ^< 5^) ballSpeed++;
echo         }
echo         
echo         // Bot AI
echo         if^(gameMode == 1^) {
echo             if^(ballY ^< player2Y + 2 ^&^& player2Y ^> 0^) player2Y--;
echo             if^(ballY ^> player2Y + 2 ^&^& player2Y ^< 14^) player2Y++;
echo         }
echo         if^(gameMode == 2^) {
echo             if^(ballY ^< player1Y + 2 ^&^& player1Y ^> 0^) player1Y--;
echo             if^(ballY ^> player1Y + 2 ^&^& player1Y ^< 14^) player1Y++;
echo             if^(ballY ^< player2Y + 2 ^&^& player2Y ^> 0^) player2Y--;
echo             if^(ballY ^> player2Y + 2 ^&^& player2Y ^< 14^) player2Y++;
echo         }
echo         
echo         if^(ballX ^<= 0^) { 
echo             p2Score++; ballX = 20; ballY = 9; ballDirX = 1; ballSpeed = 1; hitCount = 0; 
echo         }
echo         if^(ballX ^>= 39^) { 
echo             p1Score++; ballX = 20; ballY = 9; ballDirX = -1; ballSpeed = 1; hitCount = 0; 
echo         }
echo         
echo         if^(p1Score ^>= 5 ^|^| p2Score ^>= 5^) {
echo             Console.Clear^(^);
echo             Console.WriteLine^($"GAME OVER! Final Score: {p1Score}-{p2Score}"^);
echo             string winner = gameMode == 0 ? ^(p1Score ^> p2Score ? "Player 1 Wins!" : "Player 2 Wins!"^) :
echo                           gameMode == 1 ? ^(p1Score ^> p2Score ? "You Win!" : "Bot Wins!"^) :
echo                           ^(p1Score ^> p2Score ? "Bot 1 Wins!" : "Bot 2 Wins!"^);
echo             Console.WriteLine^(winner^);
echo             gameOver = true;
echo         }
echo     }
echo     
echo     static void Main^(^) {
echo         Console.Title = "Terminal Pong Game";
echo         Console.Clear^(^);
echo         Console.WriteLine^("=== TERMINAL PONG GAME ==="^);
echo         Console.WriteLine^(^);
echo         Console.WriteLine^("Choose game mode:"^);
echo         Console.WriteLine^("  1. Human vs Bot"^);
echo         Console.WriteLine^("  2. Human vs Human"^);
echo         Console.WriteLine^("  3. Bot vs Bot ^(Demo^)"^);
echo         Console.WriteLine^(^);
echo         Console.Write^("Enter choice ^(1-3^): "^);
echo         
echo         string choice = Console.ReadLine^(^);
echo         
echo         switch^(choice^) {
echo             case "1": gameMode = 1; break;
echo             case "2": gameMode = 0; break;
echo             case "3": gameMode = 2; break;
echo             default: 
echo                 Console.WriteLine^("Invalid choice, defaulting to Human vs Bot"^);
echo                 gameMode = 1;
echo                 Thread.Sleep^(1000^);
echo                 break;
echo         }
echo         
echo         Console.Clear^(^);
echo         Console.WriteLine^("Starting Terminal Pong..."^);
echo         string modeText = gameMode == 0 ? "HUMAN vs HUMAN MODE" : 
echo                          gameMode == 1 ? "HUMAN vs BOT MODE" : 
echo                          "BOT vs BOT DEMO";
echo         Console.WriteLine^(modeText^);
echo         Console.WriteLine^("Press any key to start..."^);
echo         Console.ReadKey^(true^);
echo         
echo         Setup^(^);
echo         while^(^!gameOver^) {
echo             Draw^(^);
echo             Input^(^);
echo             Logic^(^);
echo             
echo             int delay = ballSpeed == 1 ? 200 : ballSpeed == 2 ? 150 : 
echo                        ballSpeed == 3 ? 100 : ballSpeed == 4 ? 70 : 50;
echo             Thread.Sleep^(delay^);
echo         }
echo         
echo         Console.WriteLine^("\\nThanks for playing! Press any key to exit..."^);
echo         Console.ReadKey^(true^);
echo     }
echo }
) > PongGame.cs

echo [OK] Game source created
echo [INFO] Compiling using Windows built-in C# compiler...

:: Compile using .NET Framework CSC (available on all Windows)
%WINDIR%\Microsoft.NET\Framework64\v4.0.30319\csc.exe /target:exe /out:pong.exe PongGame.cs >nul 2>nul

if %errorlevel% equ 0 (
    echo [SUCCESS] Game compiled successfully!
    echo.
    echo ================================================
    echo                STARTING GAME...
    echo ================================================
    echo.
    pong.exe
) else (
    echo [WARNING] 64-bit compiler failed, trying 32-bit...
    %WINDIR%\Microsoft.NET\Framework\v4.0.30319\csc.exe /target:exe /out:pong.exe PongGame.cs >nul 2>nul
    
    if %errorlevel% equ 0 (
        echo [SUCCESS] Game compiled successfully!
        echo.
        echo ================================================
        echo                STARTING GAME...
        echo ================================================
        echo.
        pong.exe
    ) else (
        echo [ERROR] Compilation failed. Trying PowerShell alternative...
        echo.
        
        :: Fallback to PowerShell inline compilation
        powershell -Command "Add-Type -TypeDefinition (Get-Content PongGame.cs -Raw) -Language CSharp; [PongGame]::Main()"
    )
)

:: Cleanup
cd /d %USERPROFILE%
if exist "%TEMP_DIR%" rmdir /s /q "%TEMP_DIR%" >nul 2>nul

echo.
echo ================================================
echo Thanks for playing Terminal Pong!
echo No installation required - Pure Windows solution!
echo ================================================
pause
