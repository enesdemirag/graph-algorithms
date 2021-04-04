#include <vector>
#include "../include/Utils.hpp"

void addNewLayer(Node* parent, std::list<char> keys)
{
    if (keys.empty()) return;
    
    parent->addChildren(keys.front(), std::list<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9});

    keys.pop_front();

    for (Node* child : parent->getChildren())
    {
        addNewLayer(child, keys);
    }
}

std::list<int> findSolution(Node *node) {
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
    int number1 = string2int(str1, keys, values);
    int number2 = string2int(str2, keys, values);
    int total = string2int(sum, keys, values);

    if (0 == number1 || 0 == number2 || 0 == total)
    {
        return false;
    }

    return number1 + number2 == total;
}

std::list<int> BFS(Node* start_node, std::list<char>& keys, std::string& str1, std::string& str2, std::string& sum)
{
    std::list<Node*> queue;
    queue.push_back(start_node);

    while (!queue.empty())
    {
        Node* node = queue.front();
        queue.pop_front();
        
        if (node->getChildren().empty())
        {
            std::list<int> solution = findSolution(node);
            if (checkSolution(keys, solution, str1, str2, sum))
            {
                return solution;
            }
        }

        for (Node* child : node->getChildren())
        {
            queue.push_back(child);
        }
    }
    
    return std::list<int>();
}