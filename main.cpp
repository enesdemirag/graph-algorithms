#include <algorithm>
#include "include/Node.hpp"
#include "include/Utils.hpp"
#include "include/Search.hpp"

int main(int argc, char** argv)
{
    Node root(' ', -1);

    std::string str1 = "TWO";
    std::string str2 = "TWO";
    std::string sum = "FOUR";

    std::list<char> unique_keys {'T', 'W', 'O', 'F', 'U', 'R'};
    std::list<char> first_chars {'T', 'F'};

    addNewLayer(&root, unique_keys, first_chars);

    int number_of_visited_nodes, max_nodes_in_memory;
    double running_time;

    std::list<int> solution = BFS(&root, unique_keys, str1, str2, sum, number_of_visited_nodes, max_nodes_in_memory, running_time);

    if (solution.empty())
    {
        std::cout << "No possible solution found." << std::endl;
    }
    else
    {
        std::cout << "BFS" << std::endl;

        for (int value : solution)
        {
            std::cout << value << std::endl;
        }
    }

    std::list<int> solution1 = DFS(&root, unique_keys, str1, str2, sum, number_of_visited_nodes, max_nodes_in_memory, running_time);

    if (solution1.empty())
    {
        std::cout << "No possible solution found." << std::endl;
    }
    else
    {
        std::cout << "DFS" << std::endl;

        for (int value : solution1)
        {
            std::cout << value << std::endl;
        }
    }

    return 0;
}