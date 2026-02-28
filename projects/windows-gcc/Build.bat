@echo off

g++ -std=c++20 -c ../../../src/All.cpp -O3 -D KONGKONG_NO_PLATFORM_SPECIFICS
ar rcs klib.Lib All.o

pause