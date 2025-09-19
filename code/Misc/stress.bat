@echo off
setlocal EnableExtensions

g++ -std=c++20 -O3 "%1.cpp" -o "%1.exe"
g++ -std=c++20 -O3 "%2.cpp" -o "%2.exe"
g++ -std=c++20 -O3 "%3.cpp" -o "%3.exe"

for /l %%i in (1,1,100) do (
  "%3.exe" > input.txt
  "%1.exe" < input.txt > output1.txt
  "%2.exe" < input.txt > output2.txt

  fc /b output1.txt output2.txt >nul
  if errorlevel 1 (
    echo Input:
    type input.txt
    echo Your Output:
    type output1.txt
    echo Correct Output:
    type output2.txt
    exit /b 1
  )
)

@REM ./stress main good gen