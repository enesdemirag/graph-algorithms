#include "../include/Search.hpp"

std::list<int> BFS(Node* start_node, std::list<char>& keys, std::string& str1, std::string& str2, std::string& sum, int& visited_nodes, int& max_nodes_in_memory, double& time)
{
    max_nodes_in_memory = 0;
    visited_nodes = 0;
    time = 0.0;

    int begin_time_ms = getSystemTime();

    std::list<Node*> queue;
    queue.push_back(start_node);

    while (!queue.empty())
    {
        Node* node = queue.front();
        queue.pop_front();
        visited_nodes++;

        if (node->getChildren().empty())
        {
            std::list<int> solution = findSolution(node);
            if (checkSolution(keys, solution, str1, str2, sum))
            {
                time = (getSystemTime() - begin_time_ms) / 1000.0;
                return solution;
            }
        }

        for (Node* child : node->getChildren())
        {
            queue.push_back(child);
        }

        max_nodes_in_memory = std::max(max_nodes_in_memory, static_cast<int>(queue.size()));
    }

    return std::list<int>();
}

std::list<int> DFS(Node* start_node, std::list<char>& keys, std::string& str1, std::string& str2, std::string& sum, int& visited_nodes, int& max_nodes_in_memory, double& time)
{
    max_nodes_in_memory = 0;
    visited_nodes = 0;
    time = 0.0;

    int begin_time_ms = getSystemTime();

    std::stack<Node*> stack;
    stack.push(start_node);

    while (!stack.empty())
    {
        Node* node = stack.top();
        stack.pop();
        visited_nodes++;

        if (node->getChildren().empty())
        {
            std::list<int> solution = findSolution(node);
            if (checkSolution(keys, solution, str1, str2, sum))
            {
                time = (getSystemTime() - begin_time_ms) / 1000.0;
                return solution;
            }
        }

        for (Node* child : node->getChildren())
        {
            stack.push(child);
        }

        max_nodes_in_memory = std::max(max_nodes_in_memory, static_cast<int>(stack.size()));
    }

    return std::list<int>();
}