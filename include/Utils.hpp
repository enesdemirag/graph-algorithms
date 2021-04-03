#pragma once
#include "Node.hpp"
#include <iostream>

void addNewLayer(Node* parent, std::list<char> keys);
std::list<int> findSolution(Node* node);
bool checkSolution(std::list<char> keys, std::list<int> values, const char* str1, const char* str2, const char* sum);
std::list<int> BFS(Node* start_node, std::list<char> keys, const char* str1, const char* str2, const char* sum);