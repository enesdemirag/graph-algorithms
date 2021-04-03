#include "../include/Node.hpp"

Node::Node(char _key = ' ', int _value = -1)
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

char Node::getKey()
{
	return this->key;
}

int Node::getValue()
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