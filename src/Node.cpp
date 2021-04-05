#include "Node.hpp"

Node::Node(char _key, int _value)
{
    this->key = _key;
    this->value = _value;
};

void Node::addChildren(char child_key, std::list<int> values)
{
    for (int value : values)
    {
        Node* child = new Node(child_key, value);
        child->setParent(this);
        this->children.push_back(child);
    }
}

void Node::setParent(Node* parent_node)
{
    this->parent = parent_node;
}

char Node::getKey() const
{
    return this->key;
}

int Node::getValue() const
{
    return this->value;
}

Node* Node::getParent()
{
    return this->parent;
}

std::list<Node*> Node::getChildren()
{
    return this->children;
}

bool checkZeroCondition(char& key, std::list<char>& first_chars)
{
    for (char c : first_chars)
    {
        if (key == c)
        {
            return false;
        }
    }
    return true;
}

void addNewLayer(Node* parent, std::list<char> keys, std::list<char>& first_chars)
{
    if (keys.empty()) return;

    std::list<int> possible_values{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    char letter = keys.front();
    if (!checkZeroCondition(letter, first_chars))
    {
        possible_values.pop_front();
    }

    Node* temp = parent;
    while (temp != nullptr)
    {
        possible_values.remove(temp->getValue());
        temp = temp->getParent();
    }

    parent->addChildren(letter, possible_values);

    keys.pop_front();

    for (Node* child : parent->getChildren())
    {
        addNewLayer(child, keys, first_chars);
    }
}