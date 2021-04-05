#include "Utils.hpp"

std::list<int> findSolution(Node* node) {
    std::list<char> selected_keys;
    std::list<int> selected_values;

    selected_keys.push_back(node->getKey());
    selected_values.push_back(node->getValue());

    Node* parent_node = node->getParent();
    while (nullptr != parent_node->getParent())
    {
        selected_keys.push_back(parent_node->getKey());
        selected_values.push_back(parent_node->getValue());
        parent_node = parent_node->getParent();
    }

    selected_keys.reverse();
    selected_values.reverse();

    return selected_values;
}

int string2int(std::string input_str, const std::list<char>& keys, const std::list<int>& values)
{
    int number = 0;
    int digit_count = 0;
    std::reverse(input_str.begin(), input_str.end());

    std::vector<char> k;
    std::vector<int> v;

    for (auto x : keys)
    {
        k.push_back(x);
    }
    for (auto x : values)
    {
        v.push_back(x);
    }

    for (char c : input_str)
    {
        number += v.at(std::find(k.begin(), k.end(), c) - k.begin()) * std::pow(10, digit_count++);
    }

    return number;
}

bool checkSolution(const std::list<char>& keys, const std::list<int>& values, std::string& str1, std::string& str2, std::string& sum)
{
    std::list<int> unique_values(values);
    unique_values.sort();
    unique_values.unique();

    if (unique_values.size() != values.size())
    {
        return false;
    }

    int number1 = string2int(str1, keys, values);
    int number2 = string2int(str2, keys, values);
    int total = string2int(sum, keys, values);

    if (0 == number1 || 0 == number2 || 0 == total)
    {
        return false;
    }

    return number1 + number2 == total;
}

int getSystemTime()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void printResults(std::string algorithm, std::list<char> keys, std::list<int> values, int number_of_visited_nodes, int max_nodes_in_memory, double running_time)
{
    std::cout << "Algorithm: " << algorithm << std::endl;
    std::cout << "Number of the visited nodes: " << number_of_visited_nodes << std::endl;
    std::cout << "Maximum number of nodes kept in the memory: " << max_nodes_in_memory << std::endl;
    std::cout << "Running time: " << running_time << " seconds" <<std::endl;
    std::cout << "Solution: ";

    while (!keys.empty() || !values.empty())
    {
        std::cout << keys.front() << ": " << values.front();
        if (1 != values.size()) { std::cout << ", "; };

        keys.pop_front();
        values.pop_front();
    }
}

void printMatrix(std::string out_file, std::list<char> keys, std::list<int> values)
{
    FILE* pFile = fopen("solution.txt", "w");

    // First line
    for (int i = 0; i < 9; i++)
    {
        fprintf(pFile, "\t%d", i);
    }
    fprintf(pFile, "\t9\n");

    while (!keys.empty())
    {
        fprintf(pFile, "%c\t", keys.front());

        for (int n = 0; n < 10; n++)
        {
            if (values.front() == n)
            {
                fprintf(pFile, "1\t");
            }
            else
            {
                fprintf(pFile, ".\t");
            }
        }

        keys.pop_front();
        values.pop_front();
        fprintf(pFile, "\n");
    }

    fclose(pFile);
}