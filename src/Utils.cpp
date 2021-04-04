#include "../include/Utils.hpp"

void addNewLayer(Node* parent, std::list<char> keys)
{
    if (0 == keys.size()) return; 
    
    parent->addChildren(keys.front(), std::list<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9});

    keys.pop_front();

    for (Node* child : parent->getChildren())
    {
        addNewLayer(child, keys);
    }
}

std::list<int> findSolution(Node* node)
{
    std::list<int> selected_keys;
    std::list<int> selected_values;

    Node* parent_node = node->getParent();
    while (nullptr != parent_node)
    {
        selected_keys.push_back(node->getParent()->getKey());
        selected_values.push_back(node->getParent()->getValue());
        parent_node = parent_node->getParent();
    }

    selected_keys.reverse();
    selected_values.reverse();

    return selected_values;
}

bool checkSolution(std::list<char> keys, std::list<int> values, const char* str1, const char* str2, const char* sum)
{
    return true;
}

std::list<int> BFS(Node* start_node, std::list<char> keys, const char* str1, const char* str2, const char* sum)
{
    std::list<Node*> queue;
    queue.push_back(start_node);

    while (0 != queue.size())
    {
        Node* node = queue.front();
        queue.pop_front();
        
        if (0 == node->getChildren().size())
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
