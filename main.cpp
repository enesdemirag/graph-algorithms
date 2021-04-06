#include "Node.hpp"
#include "Utils.hpp"
#include "Search.hpp"

int main(int argc, char** argv)
{
    if (!checkArguments(argv))
    {
        return -1;
    }

    Node root(' ', -1);

    std::string str1 = argv[2];
    std::string str2 = argv[3];
    std::string sum = argv[4];

    std::list<char> first_chars{ str1[0], str2[0], sum[0] };
    first_chars.sort();
    first_chars.unique();

    std::list<char> unique_keys;
    for (char c : str1 + str2 + sum)
    {
        if (std::find(unique_keys.begin(), unique_keys.end(), c) == unique_keys.end())
        {
            unique_keys.push_back(c);
        }
    }

    addNewLayer(&root, unique_keys, first_chars);

    int number_of_visited_nodes, max_nodes_in_memory;
    double running_time;

    std::list<int> solution;

    if (std::string("BFS") == argv[1])
    {
        solution = BFS(&root, unique_keys, str1, str2, sum, number_of_visited_nodes, max_nodes_in_memory, running_time);
        if (!solution.empty())
        {
            printResults("BFS", unique_keys, solution, number_of_visited_nodes, max_nodes_in_memory, running_time);
            printMatrix(argv[5], unique_keys, solution);
        }
        else
        {
            std::cout << "No solution found." << std::endl;
        }
    }
    else
    {
        solution = DFS(&root, unique_keys, str1, str2, sum, number_of_visited_nodes, max_nodes_in_memory, running_time);
        if (!solution.empty())
        {
            printResults("DFS", unique_keys, solution, number_of_visited_nodes, max_nodes_in_memory, running_time);
            printMatrix(argv[5], unique_keys, solution);
        }
        else
        {
            std::cout << "No solution found." << std::endl;
        }
    }

    return 0;
}