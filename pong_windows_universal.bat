@echo off
chcp 65001 >nul 2>nul
title Terminal Pong - Universal Windows

echo ================================================
echo      Terminal Pong - Universal Windows
echo ================================================
echo.

:: Create VBScript version for maximum compatibility
echo Creating universal Windows game...

(
echo Dim gameOver, ballX, ballY, ballDirX, ballDirY
echo Dim player1Y, player2Y, p1Score, p2Score, ballSpeed, hitCount, gameMode
echo Dim WshShell
echo Set WshShell = CreateObject^("WScript.Shell"^)
echo.
echo Sub InitGame^(^)
echo     gameOver = False
echo     ballX = 20: ballY = 9: ballDirX = 1: ballDirY = 1
echo     player1Y = 7: player2Y = 7: p1Score = 0: p2Score = 0
echo     ballSpeed = 1: hitCount = 0: gameMode = 1
echo     Randomize
echo     If Rnd ^< 0.5 Then ballDirX = -1
echo     If Rnd ^< 0.5 Then ballDirY = -1
echo End Sub
echo.
echo Sub DrawGame^(^)
echo     WshShell.SendKeys "^{HOME}"
echo     WScript.Sleep 50
echo     WshShell.SendKeys "cls{ENTER}"
echo     WScript.Sleep 100
echo     
echo     If gameMode = 0 Then
echo         WScript.Echo "HUMAN vs HUMAN | Score: " ^& p1Score ^& "-" ^& p2Score ^& " | Speed: " ^& ballSpeed ^& "x"
echo         WScript.Echo "Controls: W/S ^(P1^), I/K ^(P2^), Q=quit"
echo     ElseIf gameMode = 1 Then
echo         WScript.Echo "HUMAN vs BOT | Score: " ^& p1Score ^& "-" ^& p2Score ^& " | Speed: " ^& ballSpeed ^& "x"
echo         WScript.Echo "Controls: W/S ^(You^), Q=quit"
echo     Else
echo         WScript.Echo "BOT vs BOT | Score: " ^& p1Score ^& "-" ^& p2Score ^& " | Speed: " ^& ballSpeed ^& "x"
echo         WScript.Echo "Controls: Q=quit ^(watch bots^)"
echo     End If
echo     
echo     WScript.Echo "=========================================="
echo     
echo     For i = 0 To 17
echo         line = "|"
echo         For j = 0 To 39
echo             If i = ballY And j = ballX Then
echo                 line = line ^& "O"
echo             ElseIf j = 2 And i ^>= player1Y And i ^< player1Y + 4 Then
echo                 line = line ^& "#"
echo             ElseIf j = 37 And i ^>= player2Y And i ^< player2Y + 4 Then
echo                 line = line ^& "#"
echo             ElseIf j = 20 Then
echo                 line = line ^& "|"
echo             Else
echo                 line = line ^& " "
echo             End If
echo         Next
echo         WScript.Echo line ^& "|"
echo     Next
echo     
echo     WScript.Echo "=========================================="
echo End Sub
echo.
echo Sub GameLogic^(^)
echo     ballX = ballX + ballDirX
echo     ballY = ballY + ballDirY
echo     
echo     If ballY ^<= 0 Or ballY ^>= 17 Then ballDirY = -ballDirY
echo     
echo     If ballX = 3 And ballY ^>= player1Y And ballY ^< player1Y + 4 And ballDirX ^< 0 Then
echo         ballDirX = 1
echo         hitCount = hitCount + 1
echo         If hitCount Mod 3 = 0 And ballSpeed ^< 5 Then ballSpeed = ballSpeed + 1
echo     End If
echo     
echo     If ballX = 36 And ballY ^>= player2Y And ballY ^< player2Y + 4 And ballDirX ^> 0 Then
echo         ballDirX = -1
echo         hitCount = hitCount + 1
echo         If hitCount Mod 3 = 0 And ballSpeed ^< 5 Then ballSpeed = ballSpeed + 1
echo     End If
echo     
echo     ' Bot AI
echo     If gameMode = 1 Then
echo         If ballY ^< player2Y + 2 And player2Y ^> 0 Then player2Y = player2Y - 1
echo         If ballY ^> player2Y + 2 And player2Y ^< 14 Then player2Y = player2Y + 1
echo     End If
echo     
echo     If gameMode = 2 Then
echo         If ballY ^< player1Y + 2 And player1Y ^> 0 Then player1Y = player1Y - 1
echo         If ballY ^> player1Y + 2 And player1Y ^< 14 Then player1Y = player1Y + 1
echo         If ballY ^< player2Y + 2 And player2Y ^> 0 Then player2Y = player2Y - 1
echo         If ballY ^> player2Y + 2 And player2Y ^< 14 Then player2Y = player2Y + 1
echo     End If
echo     
echo     If ballX ^<= 0 Then
echo         p2Score = p2Score + 1
echo         ballX = 20: ballY = 9: ballDirX = 1: ballSpeed = 1: hitCount = 0
echo     End If
echo     
echo     If ballX ^>= 39 Then
echo         p1Score = p1Score + 1
echo         ballX = 20: ballY = 9: ballDirX = -1: ballSpeed = 1: hitCount = 0
echo     End If
echo     
echo     If p1Score ^>= 5 Or p2Score ^>= 5 Then
echo         WshShell.SendKeys "cls{ENTER}"
echo         WScript.Sleep 100
echo         WScript.Echo "GAME OVER! Final Score: " ^& p1Score ^& "-" ^& p2Score
echo         If gameMode = 0 Then
echo             If p1Score ^> p2Score Then
echo                 WScript.Echo "Player 1 Wins!"
echo             Else
echo                 WScript.Echo "Player 2 Wins!"
echo             End If
echo         ElseIf gameMode = 1 Then
echo             If p1Score ^> p2Score Then
echo                 WScript.Echo "You Win!"
echo             Else
echo                 WScript.Echo "Bot Wins!"
echo             End If
echo         Else
echo             If p1Score ^> p2Score Then
echo                 WScript.Echo "Bot 1 Wins!"
echo             Else
echo                 WScript.Echo "Bot 2 Wins!"
echo             End If
echo         End If
echo         gameOver = True
echo     End If
echo End Sub
echo.
echo ' Main Game
echo WScript.Echo "=== TERMINAL PONG GAME ==="
echo WScript.Echo ""
echo WScript.Echo "Choose game mode:"
echo WScript.Echo "  1. Human vs Bot"
echo WScript.Echo "  2. Human vs Human"
echo WScript.Echo "  3. Bot vs Bot ^(Demo^)"
echo WScript.Echo ""
echo choice = InputBox^("Enter choice ^(1-3^):", "Terminal Pong"^)
echo.
echo Select Case choice
echo     Case "1": gameMode = 1
echo     Case "2": gameMode = 0
echo     Case "3": gameMode = 2
echo     Case Else: gameMode = 1
echo End Select
echo.
echo InitGame
echo.
echo WScript.Echo "Starting Terminal Pong..."
echo If gameMode = 0 Then
echo     WScript.Echo "HUMAN vs HUMAN MODE"
echo ElseIf gameMode = 1 Then
echo     WScript.Echo "HUMAN vs BOT MODE"
echo Else
echo     WScript.Echo "BOT vs BOT DEMO"
echo End If
echo.
echo WScript.Echo "Note: This is a simplified version for maximum compatibility."
echo WScript.Echo "For the full interactive experience, use the PowerShell version."
echo WScript.Echo ""
echo MsgBox "Press OK to start the game!", 0, "Terminal Pong"
echo.
echo ' Simple game loop ^(demo mode^)
echo For gameLoop = 1 To 50
echo     DrawGame
echo     GameLogic
echo     
echo     delay = 300
echo     If ballSpeed = 2 Then delay = 250
echo     If ballSpeed = 3 Then delay = 200
echo     If ballSpeed = 4 Then delay = 150
echo     If ballSpeed = 5 Then delay = 100
echo     
echo     WScript.Sleep delay
echo     
echo     If gameOver Then Exit For
echo Next
echo.
echo WScript.Echo ""
echo WScript.Echo "Thanks for playing Terminal Pong!"
echo WScript.Echo "For full interactive controls, use the PowerShell version."
echo MsgBox "Thanks for playing!", 0, "Terminal Pong"
) > pong_game.vbs

echo [OK] Universal Windows game created
echo.
echo Starting VBScript version ^(maximum compatibility^)...
echo Note: This version shows a demo. For full controls use PowerShell version.
echo.

cscript //nologo pong_game.vbs

echo.
echo ================================================
echo For full interactive experience, try PowerShell:
echo powershell -Command "iex ((New-Object System.Net.WebClient).DownloadString('https://raw.githubusercontent.com/TomDevX/terminal-pong/main/pong_windows_simple_powershell.ps1'))"
echo ================================================
pause

:: Cleanup
if exist pong_game.vbs del pong_game.vbs
