#include "Utils.hpp"

/* This function takes a node (a leaf node in our case)
 * and iteratively looks its parents up to the root node of the tree
 * and puts every value it came across into a list.
 * @param node A leaf node in a tree.
 * @return List of all the values from root node to the input node.
 */
std::list<int> findSolution(Node* node)
{
    // Create empty lists for letters and their values'.
    std::list<char> selected_keys;
    std::list<int> selected_values;

    // Add key and value of the node into corresponding list.
    selected_keys.push_back(node->getKey());
    selected_values.push_back(node->getValue());

    // Define a node pointer, and search every parent of the node iteratively up to the root.
    Node* parent_node = node->getParent();
    // This while loop will stop when it reaches the root node. Because root node has no parent.
    while (nullptr != parent_node->getParent())
    {
        // Add key and value of the node into corresponding list.
        selected_keys.push_back(parent_node->getKey());
        selected_values.push_back(parent_node->getValue());
        // Go one parent up.
        parent_node = parent_node->getParent();
    }

    // Because we add keys and values into list from bottom leaf node to top root node,
    // we need to reverse the list in order to preserve the same sequence of input unique keys.
    selected_keys.reverse();
    selected_values.reverse();

    // We do not need to return keys, just values list is enough.
    return selected_values;
}

/* This function maps a string to a number using key, value pairs.
 * @param input_str Input string.
 * @param keys List of unique keys.
 * @param values List of corresponding integer values of keys.
 * @return Integer value of input string.
 */
int string2int(std::string input_str, const std::list<char>& keys, const std::list<int>& values)
{
    // Initialize the number with 0 value.
    int number = 0;
    // Define a variable to keep the digit value.
    int digit_count = 0;

    // Reverse the string in order to start from last digit to first digit.
    std::reverse(input_str.begin(), input_str.end());

    // I wanted to access an element using an index,
    // and I also wanted to find the index of an element.
    // Because of these reasons I decide to use vector instead of list.
    // First I copied everything from lists into corresponding vectors.
    std::vector<char> k;
    std::vector<int> v;
    for (char x : keys) { k.push_back(x); }
    for (int x : values) { v.push_back(x); }

    // For every letter in input string, find its index inside the keys vector,
    // and get its numeric value from v vector using achieved index.
    // Then multiply it with its digit value and add it to the number.
    for (char c : input_str)
    {
        number += v.at(std::find(k.begin(), k.end(), c) - k.begin()) * std::pow(10, digit_count++);
    }

    // Return the numeric equivalent of the input string.
    return number;
}

/* This function checks if the sum of first two input strings equals to the other input string.
 * It first maps strings into integers using string2int() function, then checks the result.
 * @param keys List of unique keys.
 * @param values List of corresponding integer values of keys.
 * @param str1 Input string 1
 * @param str2 Input string 2
 * @param sum Input string 3
 * @return True if using the given key-value pairs the sum operation holds, otherwise false.
 */
bool checkSolution(const std::list<char>& keys, const std::list<int>& values, std::string& str1, std::string& str2, std::string& sum)
{
    // It is not possible to any two of the elements of values list can be same
    // because of the tree structure. While creating the tree, this constrain is checked,
    // and we are sure that values are unique.
    // Nevertheless, this constrain is also applied here as well. Double check :)
    // If we want to optimize the program, we can remove this extra check.
    // But for my homework, optimization is not required.
    std::list<int> unique_values(values);
    unique_values.sort();
    unique_values.unique();

    // If values are not unique, means there is at least two same number inside list,
    // this solution is not valid, return false.
    if (unique_values.size() != values.size())
    {
        return false;
    }

    // Convert input strings to integers.
    int number1 = string2int(str1, keys, values);
    int number2 = string2int(str2, keys, values);
    int total = string2int(sum, keys, values);

    // Check if anything is 0, which is not possible by the way,
    // because we also already checked this constrain while creating tree.
    if (0 == number1 || 0 == number2 || 0 == total) { return false; }

    // Check the math, and return true if solution holds.
    return number1 + number2 == total;
}

/* This function returns a timestamp in milliseconds.
 * @return A timestamp in milliseconds.
 */
int getSystemTime()
{
    // Using chrono library, get a timestamp in milliseconds.
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

/* This function prints all required results to the terminal.
 * @param algorithm Used algorithm.
 * @param keys List of unique letters.
 * @param values List of corresponding integers.
 * @param number_of_visited_nodes Number of visited nodes in tree before finding a valid solution.
 * @param max_nodes_in_memory Maximum number of nodes in queue/stack in all search process.
 * @param running_time Total time of the search process.
 */
void printResults(const char* algorithm, std::list<char> keys, std::list<int> values, int number_of_visited_nodes, int max_nodes_in_memory, double running_time)
{
    // Print results to terminal.
    std::cout << "Algorithm: " << algorithm << std::endl;
    std::cout << "Number of the visited nodes: " << number_of_visited_nodes << std::endl;
    std::cout << "Maximum number of nodes kept in the memory: " << max_nodes_in_memory << std::endl;
    std::cout << "Running time: " << running_time << " seconds" <<std::endl;
    std::cout << "Solution: ";

    while (!keys.empty() || !values.empty())
    {
        std::cout << keys.front() << ": " << values.front();
        if (1 != values.size()) { std::cout << ", "; }

        keys.pop_front();
        values.pop_front();
    }
    std::cout << "\n";
}

/* This function creates a file and writes the matrix of letter-number pairs.
 * @param out_file Name of the output file.
 * @param keys List of letters.
 * @param values List of corresponding integers.
 */
void printMatrix(const char* out_file, std::list<char> keys, std::list<int> values)
{
    // Create a file with write flag.
    FILE* pFile = fopen(out_file, "w");

    // First line if the numbers from 0 to 9.
    for (int i = 0; i < 9; i++)
    {
        fprintf(pFile, "\t%d", i);
    }
    fprintf(pFile, "\t9\n");

    // For every letter.
    while (!keys.empty())
    {
        // Write the letter itself.
        fprintf(pFile, "%c\t", keys.front());

        // Write 10 values with tabs between.
        for (int n = 0; n < 10; n++)
        {
            // If value of the key is reached, write 1.
            if (values.front() == n)
            {
                fprintf(pFile, "1\t");
            }
            // For other values, write dot.
            else
            {
                fprintf(pFile, ".\t");
            }
        }

        keys.pop_front();
        values.pop_front();
        fprintf(pFile, "\n");
    }

    // Close the file.
    fclose(pFile);
}

/* This function used before anything to be sure that there is no problem in input arguments.
 * @param argv Input arguments.
 * @return True if there is no problem, otherwise false.
 */
bool checkArguments(char** argv)
{
    // Try to read arguments
    try
    {
        // If any of the arguments is empty, return false.
        if (nullptr == argv[1] ||
            nullptr == argv[2] ||
            nullptr == argv[3] ||
            nullptr == argv[4] ||
            nullptr == argv[5])
        {
            std::cout << "Missing argument." << std::endl;
            return false;
        }
        // If algorithm is not BFS or DFS, return false.
        if (!(std::string("BFS") == argv[1] || std::string("DFS") == argv[1]))
        {
            std::cout << "Invalid algorithm." << std::endl;
            return false;
        }
    }
    // If there was an error occurred while reading arguments, return false;
    catch(std::exception& ex)
    {
        std::cout << "Invalid argument: " << ex.what() << std::endl;
        return false;
    }

    // If everything is passed without returning, this means argument are valid. Return true.
    return true;
}