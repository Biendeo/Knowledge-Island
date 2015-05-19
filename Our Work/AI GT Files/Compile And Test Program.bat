gcc botTest.c Game.c testGame.c mechanicalTurk.c -o botTest -Wall -g
pause
botTest
pause
del "%~dp0botTest.exe" /P
