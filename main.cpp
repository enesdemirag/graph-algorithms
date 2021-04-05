#include "Node.hpp"
#include "Utils.hpp"
#include "Search.hpp"

int main(int argc, char** argv)
{
    Node root(' ', -1);

    std::string str1 = "BASE"; //argv[2];
    std::string str2 = "BALL"; //argv[3];
    std::string sum = "GAMES"; // argv[4];

    std::list<char> unique_keys{ 'B', 'A', 'S', 'E', 'L', 'G', 'M' };
    std::list<char> first_chars{ 'B', 'G' };

    addNewLayer(&root, unique_keys, first_chars);

    int number_of_visited_nodes, max_nodes_in_memory;
    double running_time;

    std::list<int> solution;

    if ("BFS" == "DFS") //argv[1])
    {
        solution = BFS(&root, unique_keys, str1, str2, sum, number_of_visited_nodes, max_nodes_in_memory, running_time);
        if (!solution.empty())
        {
            printResults("BFS", unique_keys, solution, number_of_visited_nodes, max_nodes_in_memory, running_time);
            printMatrix("BFSsolution.txt", unique_keys, solution);
        }
    }
    else
    {
        solution = DFS(&root, unique_keys, str1, str2, sum, number_of_visited_nodes, max_nodes_in_memory, running_time);
        if (!solution.empty())
        {
            printResults("DFS", unique_keys, solution, number_of_visited_nodes, max_nodes_in_memory, running_time);
            printMatrix("DFSsolution.txt", unique_keys, solution);
        }
    }

    return 0;
}