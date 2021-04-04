#include <algorithm>
#include "include/Node.hpp"
#include "include/Utils.hpp"

int main(int argc, char** argv)
{
    Node root(' ', -1);

    std::string str1 = "TWO";
    std::string str2 = "TWO";
    std::string sum = "FOUR";

    std::list<char> unique_keys {'T', 'W', 'O', 'F', 'U', 'R'};

    addNewLayer(&root, unique_keys);

    std::list<int> solution = BFS(&root, unique_keys, str1, str2, sum);

    if (solution.empty())
    {
        std::cout << "No possible solution found." << std::endl;
    }
    else
    {
        std::cout << "YES" << std::endl;
        //printResult(unique_keys, solution);
        //writeResult(unique_keys, solution);
    }
}