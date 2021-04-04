#pragma once
#include "Node.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>

void addNewLayer(Node* parent, std::list<char> keys);
std::list<int> findSolution(Node* node);
bool checkSolution(std::list<char>& keys, std::list<int>& values, std::string str1, std::string str2, std::string sum);
std::list<int> BFS(Node* start_node, std::list<char>& keys, std::string& str1, std::string& str2, std::string& sum);
int string2int(std::string& input_str, std::list<char>& keys, std::list<int>& values);