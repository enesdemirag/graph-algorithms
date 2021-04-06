#include "Node.hpp"
#include "Utils.hpp"
#include "Search.hpp"

int main(int argc, char** argv)
{
    // Checking if there is an unexpected input argument
    // And if there is, stop the program.
    if (!checkArguments(argv))
    {
        return -1;
    }

    // Create the root note (with no parent, ' ' key and -1 value.
    Node root(' ', -1);

    // Parse input arguments into variables.
    std::string str1 = argv[2];
    std::string str2 = argv[3];
    std::string sum = argv[4];

    // Find first letters of each word from inputs
    std::list<char> first_chars{ str1[0], str2[0], sum[0] };
    first_chars.sort();
    first_chars.unique();

    // Find unique character list from inputs
    std::list<char> unique_keys;
    for (char c : str1 + str2 + sum)
    {
        // If c is not in unique_keys list, add c into the list.
        if (std::find(unique_keys.begin(), unique_keys.end(), c) == unique_keys.end())
        {
            unique_keys.push_back(c);
        }
    }

    // Recursively create the tree from root node.
    addNewLayer(&root, unique_keys, first_chars);

    // Define output variables
    int number_of_visited_nodes, max_nodes_in_memory;
    double running_time;
    std::list<int> solution;

    // BFS algorithm
    if (std::string("BFS") == argv[1])
    {
        solution = BFS(&root, unique_keys, str1, str2, sum, number_of_visited_nodes, max_nodes_in_memory, running_time);
        // If there is a solution.
        if (!solution.empty())
        {
            // Print results and write matrix to file.
            printResults("BFS", unique_keys, solution, number_of_visited_nodes, max_nodes_in_memory, running_time);
            printMatrix(argv[5], unique_keys, solution);
        }
        // If no solution was found.
        else
        {
            std::cout << "No solution found." << std::endl;
        }
    }
    // DFS algorithm
    else
    {
        solution = DFS(&root, unique_keys, str1, str2, sum, number_of_visited_nodes, max_nodes_in_memory, running_time);
        // If there is a solution.
        if (!solution.empty())
        {
            // Print results and write matrix to file.
            printResults("DFS", unique_keys, solution, number_of_visited_nodes, max_nodes_in_memory, running_time);
            printMatrix(argv[5], unique_keys, solution);
        }
        // If no solution was found.
        else
        {
            std::cout << "No solution found." << std::endl;
        }
    }

    return 0;
}