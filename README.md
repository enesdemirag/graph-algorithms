# cryptarithmetic-puzzles
Solving Cryptarithmetic Puzzles with Breadth-First Search & Depth-First Search

BLG336E - Analysis of Algorithms II, Spring 2021, Homework 1

Student Name: Enes Demirag<br>
Student ID  : 504201571<br>
Mail        : ensdmrg@gmail.com<br>
Date		    : 06.04.2021<br>

For any necessary information about this project first read the [assignment](assignment.pdf). This projects consist of a Node class, two graph traverse algorithms (BFS and DFS) and other utility functions. In order to compile and run this project, first you need to link files under **include/** directory. Below commands can be used to build and run this project with *g++*.

```
>> g++ -std=c++11 -Iinclude -c src/*
>> g++ -std=c++11 -Iinclude -g *.o -o executable main.cpp
>> ./executable DFS TWO TWO FOUR solution.txt
```

All of the standard libraries used in this project is given below.

```
<list>      : To implement a FIFO type Queue structure.
<stack>     : To implement a LIFO type Stack structure.
<string>    : String operations.
<vector>    : Storing some elements and accessing them.
<iostream>  : To print things to the terminal.
<algorithm> : To find element positions inside lists and vectors.
<cmath>     : Numaric operations like power and max.
<chrono>    : To calculate running time.
```

I explained my decisions and way of thinking in depth via inline documentation and comments inside this project. Also you can check my submitted report [here](report.pdf). If you encounter any problem regarding this projects, feel free to reach me.

Sincerely, Enes.
