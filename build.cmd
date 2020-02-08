@echo off
del build\CMakeCache.txt

cmake -G"Visual Studio 15 2017 Win64" -B build -DBOOST_ROOT=C:\local\boost_1_72_0  .
cmake --build  build --config Release