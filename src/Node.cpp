#include "Node.hpp"

/* Constructor of the Node class.
 * @param _key Letter.
 * @param _value Number.
 */
Node::Node(char _key, int _value)
{
    // Set the key and value of the node.
    this->key = _key;
    this->value = _value;
}

/* With this function, any node can create multiple children nodes under it
 * and connects them with itself.
 * @param child_key Letter of the child nodes.
 * @param values Numeric values for each child node.
 */
void Node::addChildren(char child_key, std::list<int> values)
{
    // For every value in values list, create a new child node.
    // Then connect the child and parent in both ways.
    // Add child node into parent's children list.
    // Set parent node to child's parent.
    for (int value : values)
    {
        Node* child = new Node(child_key, value);
        child->setParent(this);
        this->children.push_back(child);
    }
}

// @param Parent node of the node to be set.
void Node::setParent(Node* parent_node)
{
    this->parent = parent_node;
}

// @return The key/letter of the node.
char Node::getKey() const
{
    return this->key;
}

// @return The value/number of the node.
int Node::getValue() const
{
    return this->value;
}

// @return Parent of the node.
Node* Node::getParent()
{
    return this->parent;
}

// @return List of child nodes of the node.
std::list<Node*> Node::getChildren()
{
    return this->children;
}

/* This functions check if given letter is the first letter of the given words.
 * We need this constrain to not create extra nodes inside tree which cannot take 0 value.
 * @param key Letter.
 * @param first_chars List of first letters of the words.
 * @return False if key is inside first_chars, otherwise true.
 */
bool checkZeroCondition(char& key, std::list<char>& first_chars)
{
    // For every first letter, check if the key is one of them.
    for (char c : first_chars)
    {
        if (key == c)
        {
            // If key is a first letter, return false.
            return false;
        }
    }
    return true;
}

/* This is the function which creates a tree. It takes a node and creates every possible branch under it recursively.
 * @param parent Root of the tree to be created.
 * @param keys Each unique letter. Size of this list is the depth of our tree.
 * @param keys first_chars List of letters which cannot take 0 value because they are the left-most digit.
 */
void addNewLayer(Node* parent, std::list<char> keys, std::list<char>& first_chars)
{
    // This is the stop condition of the recursive call.
    // If there are no more key to create nodes,
    // this means the maximum depth is reached. We can stop adding child nodes now.
    if (keys.empty()) return;

    // There are 10 different values which a node can hold as value.
    std::list<int> possible_values{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    // If key is a first letter, its value cannot be 0.
    char letter = keys.front();
    if (!checkZeroCondition(letter, first_chars))
    {
        possible_values.pop_front();
    }

    // Create a temporary node to search for parents.
    // Look every parent of the child up to root node.
    // And remove the values of parents from the possible_values list.
    // Because two different letters cannot have the same numeric value.
    Node* temp = parent;
    while (temp != nullptr)
    {
        possible_values.remove(temp->getValue());
        temp = temp->getParent();
    }

    // Create child nodes for parent node with possible values.
    parent->addChildren(letter, possible_values);

    // Now that we are done with first letter, remove it.
    keys.pop_front();

    // Recursively call the same function for with keys and possible values.
    // Pay attention to the input parameters of this function.
    // We are giving the keys char list pass by value, not pass by reference.
    // Because for every recursion, we want to give a new keys list with one less element.
    for (Node* child : parent->getChildren())
    {
        // Recursive call
        addNewLayer(child, keys, first_chars);
    }
}