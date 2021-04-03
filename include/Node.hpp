#pragma once
#include <list>

class Node {
public:
	Node(char _key = ' ', int _value = -1);
	void addChildren(char child_key, std::list<int> values);
	void setParent(Node* parent_node);
	char getKey();
	int getValue();
	Node* getParent();
	std::list<Node*> getChildren();
private:
	char key;
	int value;
	Node* parent;
	std::list<Node*> children;
};