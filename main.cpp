#include "include/Node.hpp"
#include "include/Utils.hpp"

int main(int argc, char** argv)
{
    Node root(' ', -1);

    std::list<char> unique_keys {'T', 'W', 'O', 'F', 'U', 'R'};
    const char* str1 = "TWO";
    const char* str2 = "TWO";
    const char* sum = "FOUR";

    addNewLayer(&root, unique_keys);

    std::list<int> solution = BFS(&root, unique_keys, str1, str2, sum);

    if (std::list<int>() == solution)
    {
        std::cout << "No possible solution found." << std::endl;
    }
    else
    {
        //printResult(unique_keys, solution);
        //writeResult(unique_keys, solution);
    }

    return 0;
}