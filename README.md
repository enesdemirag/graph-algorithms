# graph-algorithms

Student Name: Enes Demirag<br>
Student ID  : 504201571<br>
Mail        : ensdmrg@gmail.com<br>

If you encounter any problem regarding this projects, feel free to reach me.

Sincerely, Enes.

## cryptarithmetic-puzzles
Solving Cryptarithmetic Puzzles with Breadth-First Search & Depth-First Search

BLG336E - Analysis of Algorithms II, Spring 2021, Homework 1

For any necessary information about this project first read the [assignment](assignment1.pdf). This projects consist of a Node class, two graph traverse algorithms (BFS and DFS) and other utility functions. In order to compile and run this project, first you need to link files under **include/** directory. Below commands can be used to build and run this project with *g++*.

```
>> cd cryptarithmetic-puzzles
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
<algorithm> : To find element positions inside lists and vectors and sort them.
<cmath>     : Numeric operations like power and max.
<chrono>    : To calculate running time.
```

I explained my decisions and way of thinking in depth via inline documentation and comments inside this project. Also you can check my submitted [report](cryptarithmetic-puzzles/report.pdf).

## minimum-spanning-tree

For any necessary information about this project first read the [assignment](assignment2.pdf). This projects consist of a Graph class with methods like Minimum Spanning Tree (MST). Below commands can be used to build and run this project with *g++*.

```
>> cd minimum-spanning-tree
>> g++ -std=c++11 q1.cpp -o q1
>> ./q1
>> city_plan_1.txt
```

All of the standard libraries used in this project is given below.

```
<algorithm> : To find element positions inside lists and vectors.
<iostream>  : To print things to the terminal.
<fstream>   : To read things from a file.
<sstream>   : To parse sub strings
<string>    : String operations.
<vector>    : Storing some elements and accessing them.
<set>       : Storing unique elements.
<map>       : Mapping pairs of elements.
```

I explained my decisions and way of thinking in depth via inline documentation and comments inside this project. You can also test these programs using [calico tool](https://github.com/itublg/calico) with given [q1.t](q1.t) and [q2.t](q2.t) scripts.

In order to use calico, you should install it from pip and run the given .t files. Calico will automatically test the programs with different cases.

```
>> pip install calico
>> calico q1.t 
```

## shortest-path

This projects consist of a Graph class with methods like Dijkstra'a Shortest Path algorithm. Below commands can be used to build and run this project with *g++.*

```
>> cd shortest_path
>> g++ -std=c++11 q2.cpp -o q2
>> ./q2
>> path_info_1.txt
```

All of the standard libraries used in this project is given below.

```
<algorithm> : To find element positions inside lists and vectors.
<iostream>  : To print things to the terminal.
<fstream>   : To read things from a file.
<sstream>   : To parse sub strings
<climits>   : To assign the maximum integer value.
<string>    : String operations.
<vector>    : Storing some elements and accessing them.
<tuple>     : To store three values in a pack.
<set>       : Storing unique elements.
<map>       : Mapping pairs of elements.
```