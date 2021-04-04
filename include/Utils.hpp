#pragma once
#include "Node.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>
#include <chrono>

void addNewLayer(Node* parent, std::list<char> keys);
std::list<int> findSolution(Node* node);
bool checkSolution(const std::list<char>& keys, const std::list<int>& values, std::string& str1, std::string& str2, std::string& sum);
int string2int(std::string input_str, const std::list<char>& keys, const std::list<int>& values);
int getSystemTime();