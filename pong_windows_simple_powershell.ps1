if (-not ([System.Management.Automation.PSTypeName]'SimplePong').Type) {
Add-Type @"
using System;
using System.Threading;

public class SimplePong {
    public static bool gameOver = false;
    public static int ballX = 20, ballY = 9, ballDirX = 1, ballDirY = 1;
    public static int player1Y = 7, player2Y = 7, p1Score = 0, p2Score = 0;
    public static int ballSpeed = 1, hitCount = 0;
    public static int gameMode = 1;
    public static Random rand = new Random();
    
    public static void Setup() {
        ballDirX = rand.Next(2) == 0 ? 1 : -1;
        ballDirY = rand.Next(2) == 0 ? 1 : -1;
        Console.CursorVisible = false;
    }
    
    public static void Draw() {
        Console.Clear();
        string mode = gameMode == 0 ? "HUMAN vs HUMAN" : gameMode == 1 ? "HUMAN vs BOT" : "BOT vs BOT";
        Console.WriteLine(mode + " | Score: " + p1Score + "-" + p2Score + " | Speed: " + ballSpeed + "x");
        
        string controls = gameMode == 0 ? "Controls: W/S (P1), I/K (P2), Q=quit" :
                         gameMode == 1 ? "Controls: W/S (You), Q=quit" :
                         "Controls: Q=quit (watch bots)";
        Console.WriteLine(controls);
        Console.WriteLine("==========================================");
        
        for(int i = 0; i < 18; i++) {
            Console.Write("|");
            for(int j = 0; j < 40; j++) {
                if(i == ballY && j == ballX) Console.Write("O");
                else if(j == 2 && i >= player1Y && i < player1Y + 4) Console.Write("#");
                else if(j == 37 && i >= player2Y && i < player2Y + 4) Console.Write("#");
                else if(j == 20) Console.Write("|");
                else Console.Write(" ");
            }
            Console.WriteLine("|");
        }
        Console.WriteLine("==========================================");
    }
    
    public static void Input() {
        if(Console.KeyAvailable) {
            ConsoleKeyInfo key = Console.ReadKey(true);
            if(key.Key == ConsoleKey.Q) gameOver = true;
            if(key.Key == ConsoleKey.W && gameMode != 2 && player1Y > 0) player1Y--;
            if(key.Key == ConsoleKey.S && gameMode != 2 && player1Y < 14) player1Y++;
            if(key.Key == ConsoleKey.I && gameMode == 0 && player2Y > 0) player2Y--;
            if(key.Key == ConsoleKey.K && gameMode == 0 && player2Y < 14) player2Y++;
        }
    }
    
    public static void Logic() {
        ballX += ballDirX;
        ballY += ballDirY;
        
        if(ballY <= 0 || ballY >= 17) ballDirY = -ballDirY;
        
        if(ballX == 3 && ballY >= player1Y && ballY < player1Y + 4 && ballDirX < 0) {
            ballDirX = 1; hitCount++; 
            if(hitCount % 3 == 0 && ballSpeed < 5) ballSpeed++;
        }
        if(ballX == 36 && ballY >= player2Y && ballY < player2Y + 4 && ballDirX > 0) {
            ballDirX = -1; hitCount++; 
            if(hitCount % 3 == 0 && ballSpeed < 5) ballSpeed++;
        }
        
        if(gameMode == 1) {
            if(ballY < player2Y + 2 && player2Y > 0) player2Y--;
            if(ballY > player2Y + 2 && player2Y < 14) player2Y++;
        }
        if(gameMode == 2) {
            if(ballY < player1Y + 2 && player1Y > 0) player1Y--;
            if(ballY > player1Y + 2 && player1Y < 14) player1Y++;
            if(ballY < player2Y + 2 && player2Y > 0) player2Y--;
            if(ballY > player2Y + 2 && player2Y < 14) player2Y++;
        }
        
        if(ballX <= 0) { 
            p2Score++; ballX = 20; ballY = 9; ballDirX = 1; ballSpeed = 1; hitCount = 0; 
        }
        if(ballX >= 39) { 
            p1Score++; ballX = 20; ballY = 9; ballDirX = -1; ballSpeed = 1; hitCount = 0; 
        }
        
        if(p1Score >= 5 || p2Score >= 5) {
            Console.Clear();
            Console.WriteLine("GAME OVER! Final Score: " + p1Score + "-" + p2Score);
            string winner = gameMode == 0 ? (p1Score > p2Score ? "Player 1 Wins!" : "Player 2 Wins!") :
                           gameMode == 1 ? (p1Score > p2Score ? "You Win!" : "Bot Wins!") :
                           (p1Score > p2Score ? "Bot 1 Wins!" : "Bot 2 Wins!");
            Console.WriteLine(winner);
            gameOver = true;
        }
    }
    
    public static void StartGame() {
        Console.Title = "Terminal Pong Game";
        Console.Clear();
        Console.WriteLine("=== TERMINAL PONG GAME ===");
        Console.WriteLine("");
        Console.WriteLine("Choose game mode:");
        Console.WriteLine("  1. Human vs Bot");
        Console.WriteLine("  2. Human vs Human");
        Console.WriteLine("  3. Bot vs Bot (Demo)");
        Console.WriteLine("");
        Console.Write("Enter choice (1-3): ");
        
        string choice = Console.ReadLine();
        
        switch(choice) {
            case "1": gameMode = 1; break;
            case "2": gameMode = 0; break;
            case "3": gameMode = 2; break;
            default: 
                Console.WriteLine("Invalid choice, defaulting to Human vs Bot");
                gameMode = 1;
                Thread.Sleep(1000);
                break;
        }
        
        Console.Clear();
        Console.WriteLine("Starting Terminal Pong...");
        string modeText = gameMode == 0 ? "HUMAN vs HUMAN MODE" : 
                         gameMode == 1 ? "HUMAN vs BOT MODE" : 
                         "BOT vs BOT DEMO";
        Console.WriteLine(modeText);
        Console.WriteLine("Press any key to start...");
        Console.ReadKey(true);
        
        Setup();
        while(!gameOver) {
            Draw();
            Input();
            Logic();
            
            int delay = ballSpeed == 1 ? 200 : ballSpeed == 2 ? 150 : 
                       ballSpeed == 3 ? 100 : ballSpeed == 4 ? 70 : 50;
            Thread.Sleep(delay);
        }
        
        Console.WriteLine("");
        Console.WriteLine("Thanks for playing! Press any key to exit...");
        Console.ReadKey(true);
    }
}
"@
}

Clear-Host
Write-Host "================================================" -ForegroundColor Cyan
Write-Host "         Terminal Pong - Windows Compatible" -ForegroundColor Cyan  
Write-Host "================================================" -ForegroundColor Cyan
Write-Host ""
Write-Host "Starting game using .NET Framework..." -ForegroundColor Green
Write-Host "No external dependencies required!" -ForegroundColor Green
Write-Host ""

try {
    [SimplePong]::StartGame()
} catch {
    Write-Host "Error starting game: $($_.Exception.Message)" -ForegroundColor Red
    Write-Host ""
    Write-Host "This might be due to PowerShell execution policy."
    Write-Host "Try running: Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser"
    Write-Host ""
}

Write-Host ""
Write-Host "================================================" -ForegroundColor Cyan
Write-Host "Thanks for playing Terminal Pong!" -ForegroundColor Yellow
Write-Host "Pure Windows solution - No installation needed!" -ForegroundColor Green
Write-Host "Visit: https://github.com/TomDevX/terminal-pong" -ForegroundColor Blue
Write-Host "================================================" -ForegroundColor Cyan
Read-Host "Press Enter to exit"
