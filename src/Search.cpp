#include "Search.hpp"

std::list<int> BFS(Node* start_node, std::list<char>& keys, std::string& str1, std::string& str2, std::string& sum, int& visited_nodes, int& max_nodes_in_memory, double& time)
{
    // Set output values to 0.
    // Pay attention that this function takes these parameters as passbyreference.
    // In order to return a tuple of multiple things, this function returns
    // the solution list which holds the corresponding numeric values of the keys.
    // And it sets the other variables' values.
    max_nodes_in_memory = 0;
    visited_nodes = 0;
    time = 0.0;

    // Get a timestamp in milliseconds.
    int begin_time_ms = getSystemTime();

    // Create an empty list called queue.
    // For the implementation of the Queue data structure I used a list.
    // For every new incoming element, I pushed it into the back of the list,
    // and for every calculation, I get an element from the beginning of the list.
    // In this way, FIFO behaviour is achieved.
    std::list<Node*> queue;

    // Push the start node into list.
    queue.push_back(start_node);

    // If there is at least one node in queue.
    while (!queue.empty())
    {
        // Take a node from the beginning of the queue.
        Node* node = queue.front();
        queue.pop_front();

        // Increment visited nodes by one.
        visited_nodes++;

        // If node has no children, this means it is a leaf.
        // So we can get a possible solution and check if its correct.
        if (node->getChildren().empty())
        {
            // Get a possible solution.
            std::list<int> solution = findSolution(node);

            // Check if the possible solution is correct.
            if (checkSolution(keys, solution, str1, str2, sum))
            {
                // It the solution holds. Get a new timestamp and set the running time in seconds.
                time = (getSystemTime() - begin_time_ms) / 1000.0;
                // And return the solution.
                return solution;
            }
        }

        // If its not a leaf node. Add its children at the back of the queue.
        for (Node* child : node->getChildren())
        {
            queue.push_back(child);
        }

        // Set the maximum nodes in the queue.
        max_nodes_in_memory = std::max(max_nodes_in_memory, static_cast<int>(queue.size()));
    }

    // If every node was searched and no solution was found, return an empty list.
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