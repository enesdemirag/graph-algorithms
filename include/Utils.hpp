#pragma once
#include "Node.hpp"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <vector>

std::list<int> findSolution(Node* node);
bool checkSolution(const std::list<char>& keys, const std::list<int>& values, std::string& str1, std::string& str2, std::string& sum);
int string2int(std::string input_str, const std::list<char>& keys, const std::list<int>& values);
int getSystemTime();
void printResults(std::string algorithm, std::list<char> keys, std::list<int> values, int number_of_visited_nodes, int max_nodes_in_memory, double running_time);
void printMatrix(std::string out_file, std::list<char> keys, std::list<int> values);
bool checkArguments(char** argv);