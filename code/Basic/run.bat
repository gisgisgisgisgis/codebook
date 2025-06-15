@echo off
g++ -std=c++23 -DLOCAL -Wall -Wextra -Wshadow -O2 %1.cpp -o %1.exe
if "%2" == "" ("%1.exe") else ("%1.exe" < "%2")