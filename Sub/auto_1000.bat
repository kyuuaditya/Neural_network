@echo off
setlocal ENABLEDELAYEDEXPANSION
set/a mine=1
set loopcount=1000
:loop
set /a loopcount=loopcount-1
start "D:\Github\Neural_network\Sub" image.exe
timeout /t 1
ren img.png !mine!".png"
set/a mine+=1
if %loopcount%==0 goto exitloop
goto loop
:exitloop
pause