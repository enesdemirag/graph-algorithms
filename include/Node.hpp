#pragma once
#include <list>

class Node {
public:
    Node(char _key, int _value);
    void addChildren(char child_key, std::list<int> values);
    void setParent(Node* parent_node);
    char getKey() const;
    int getValue() const;
    Node* getParent();
    std::list<Node*> getChildren();
private:
    char key;
    int value;
    Node* parent = nullptr;
    std::list<Node*> children;
};

bool checkZeroCondition(char& key, std::list<char>& first_chars);
void addNewLayer(Node* parent, std::list<char> keys, std::list<char>& first_chars);