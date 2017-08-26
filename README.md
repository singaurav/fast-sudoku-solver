## Overview
[![Build Status](https://travis-ci.org/singaurav/fast-sudoku-solver.svg?branch=master)](https://travis-ci.org/singaurav/fast-sudoku-solver)

A fast __Sudoku__ solver written in __C++__ that uses a simple and efficient non-traditional backtracking approach to solve the popular logic puzzle. The project is in an early stage and more documentation will follow.

## Getting started
* #### Requirements
 > Windows

 + [CMake](https://cmake.org/)
 + [MinGW](http://www.mingw.org/)
* #### Build
 > Windows

   ```
   1. git clone https://github.com/singaurav/fast-sudoku-solver.git
   2. mkdir fast-sudoku-solver-build
   3. cd fast-sudoku-solver-build
   4. cmake -G "MinGW Makefiles" ../fast-sudoku-solver
   5. make         
   ```     
* #### Run
 > Windows

   ```
   1. cd src
   2. sudoku.exe -h (displays usage help)
   ```
* #### Test
 > Windows

 ```
 1. cd test
 2. sudokuTest.exe -d yes
 ```

## More
* Please raise any issues or bugs [here.](https://github.com/singaurav/fast-sudoku-solver/issues)
