@echo off
del build\CMakeCache.txt
cmake -B build .
cmake --build build