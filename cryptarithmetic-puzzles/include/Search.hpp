#pragma once
#include "Utils.hpp"
#include <stack>

std::list<int> BFS(Node* start_node, std::list<char>& keys, std::string& str1, std::string& str2, std::string& sum, int& visited_nodes, int& max_nodes_in_memory, double& time);
std::list<int> DFS(Node* start_node, std::list<char>& keys, std::string& str1, std::string& str2, std::string& sum, int& visited_nodes, int& max_nodes_in_memory, double& time);