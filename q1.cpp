/* @Author

Student Name: Enes Demirag
Student ID  : 504201571
Mail        : ensdmrg@gmail.com
Date		: 23.04.2021


Dear sir/madam,

This projects consist of a Graph class with methods like Minimum Spanning Tree (MST).
Below commands can be used to build and run this project with g++.

>> g++ -std=c++11 q1.cpp -o q1
>> ./q1
>> city_plan_1.txt

All of the standard libraries used in this project is given below.

<algorithm> : To find element positions inside lists and vectors.
<iostream>  : To print things to the terminal.
<fstream>   : To read things from a file.
<sstream>   : To parse sub strings
<string>    : String operations.
<vector>    : Storing some elements and accessing them.
<set>       : Storing unique elements.
<map>       : Mapping pairs of elements.

If you encounter any problem regarding this projects, feel free to reach me.

Thanks and kind regards,
Enes
*/

// Including necessary standard libraries.
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>

/* Definitions:
 * Node is just a string,
 * A pair of two nodes make a Connection
 * Weighted connection is  called Edge
 * Solution is a vector of multiple Edges.
 */
typedef std::string Node;
typedef std::pair<Node, Node> Connection;
typedef std::pair<int, Connection> Edge;
typedef std::pair<std::vector<Edge>, int> Solution;

/* This is a very simple class which stores all the nodes,
 * all the Edges (connections with cost values), and the mapping of the directions.
 */
class Graph {
private:
    std::vector<Edge> edges;
    std::set<Node> nodes;
    std::map<Node, Node> tree; // Actually its not a tree structure. Just a dictionary of directions.
public:
    void addNode(Node& node);
    Node& findNode(Node& node);
    void addEdge(Edge& edge);
    Solution MST();
};

/* This method adds a new node into the graph.
 * Given node should not be already inside the graph.
 * @param node Node to be added.
 */
void Graph::addNode(Node& node)
{
    // Insert the node into the nodes vector.
    this->nodes.insert(node);
    // Every node is connected to itself.
    this->tree.insert(Connection(node, node));
}

/* This recursive method call itself until it finds the source of itself.
 * @param node Node which we want to find its source
 * @return Node source node of the given node.
 */
Node& Graph::findNode(Node& node)
{
    if (node != this->tree[node])
    {
        this->tree[node] = findNode(this->tree[node]);
    }
    return this->tree[node];
}

/* This method adds a new edge into the graph.
 * While adding the edge, it also adds the nodes of the edge into the class attribute nodes.
 * @param edge Edge to be added.
 */
void Graph::addEdge(Edge& edge)
{
    addNode(edge.second.first);
    addNode(edge.second.second);
    this->edges.push_back(edge);
}

/* This method is a Minimum Spanning Tree algorithm implementation.
 * First we check every edge using loop to count for the constrains.
 * Every iteration process will check different constrains.
 * After obtaining constrains, at the last loop we will span the tree while pushing the nodes we visit
 * and counting the total cost.
 * @return Solution Found minimum spanning tree.
 */
Solution Graph::MST()
{
    // We will push every visited Edge into this vector.
    std::vector<Edge> min_spanning_tree;
    // Total cost
    int total_cost = 0;

    // First, sort the edges of the graph.
    std::sort(this->edges.begin(), this->edges.end());

    // First loop constrains 2 and 5.
    // For every edge, we look for a Great Palace - Hippodrome pair.
    // As soon as we found it, we will add it into our solution spanning tree and break the loop.
    for (Edge& e : this->edges)
    {
        Node begin_node = e.second.first;
        Node end_node = e.second.second;

        Node src = findNode(begin_node);
        Node dst = findNode(end_node);
        int cost = e.first;

        // If Great Palace is connected to the Hippodrome, we want it add the Edge to our tree.
        if ("GP" == begin_node && "Hipp" == end_node)
        {
            // Mapping our way. Direction from source node to destination node.
            src = findNode(src);
            dst = findNode(dst);
            tree[dst] = src;

            // Add this Edge into the solution tree.
            min_spanning_tree.push_back(Edge(cost, Connection(begin_node, end_node)));
            total_cost += cost;

            // Then break the loop.
            break;
        }
    }

    // Second loop for constrains 3 and 4.
    // For every edge, we look for a Great Palace - Church pair.
    // Because we previously sorted the edges, first occurrence will have the least cost.
    // We will at it into our solution spanning tree and break the loop.
    for (Edge& e : this->edges)
    {
        Node begin_node = e.second.first;
        Node end_node = e.second.second;

        Node src = findNode(begin_node);
        Node dst = findNode(end_node);
        int cost = e.first;

        // If Great Palace is connected to a Church, we want it add the Edge to our tree.
        if (("GP" == begin_node && "Ch" == end_node.substr(0, 2)) || ("GP" == end_node && "Ch" == begin_node.substr(0, 2)))
        {
            // Mapping our way. Direction from source node to destination node.
            src = findNode(src);
            dst = findNode(dst);
            tree[dst] = src;

            // Add this Edge into the solution tree.
            min_spanning_tree.push_back(Edge(cost, Connection(begin_node, end_node)));

            // Then break the loop.
            total_cost += cost;
            break;
        }
    }

    // Third loop for spanning.
    // This is the real loop of Kruskal's algorithm. Others were implemented to achieve the given conditions.
    // Inside this loop we check the remaining constrains and omit them.
    // And for every edge we will span out tree to every node in the graph.
    for (Edge& e : this->edges)
    {
        Node begin_node = e.second.first;
        Node end_node = e.second.second;

        // Constrain 7
        // If both nodes of the edge are a house of an important person, we will omit this edge.
        if ("Hp" == begin_node.substr(0, 2) && "Hp" == end_node.substr(0, 2))
        {
            continue;
        }
        // Constrain 6
        // If a basilica is connected to the hippodrome, we will omit this edge either.
        else if (("Hipp" == begin_node && "Bas" == end_node.substr(0, 3)) || ("Bas" == begin_node.substr(0, 3) && "Hipp" == end_node))
        {
            continue;
        }

        Node src = findNode(begin_node);
        Node dst = findNode(end_node);
        int cost = e.first;

        // If two nodes are different.
        if (src != dst)
        {
            // Mapping our way. Direction from source node to destination node.
            src = findNode(src);
            dst = findNode(dst);
            tree[dst] = src;

            // Add this Edge into the solution tree.
            min_spanning_tree.push_back(Edge(cost, Connection(begin_node, end_node)));
            total_cost += cost;
        }
    }

    // Because we add two edges with different costs inside the first two loops
    // in order to apply the constrains. We will sort the solution tree again for the submission system.
    sort(min_spanning_tree.begin(), min_spanning_tree.end());

    // Return the minimum spanning tree of edges.
    return Solution(min_spanning_tree, total_cost);
}

/* This is the main function.
 * It takes a file name from the terminal,
 * First creates a graph with the edges given in the file.
 * Then find the minimum spanning tree using Kruskal's algorithm.
 */
int main()
{
    // Create an empty graph.
    Graph graph;

    // Define variables for paring operations.
    std::string file_name, line, str;
    std::vector<std::string> params;

    // Get the input file name from terminal.
    std::cin >> file_name;
    std::ifstream city_plan(file_name);

    // Read from file and fill the graph with given edges.
    if (city_plan.is_open())
    {
        // Parse every line of the file
        while (std::getline(city_plan, line))
        {
            params.clear();
            std::istringstream parser(line);

            // Split the line by ',' comma character.
            while (getline(parser, str, ','))
            {
                // Add parsed strings.
                params.push_back(str);
            }

            // Every line should have 3 strings separated with commas between them.
            if (3 == params.size())
            {
                // Add the edge into the graph.
                Edge e(std::stoi(params[2]), Connection(params[0], params[1]));
                graph.addEdge(e);
            }
        }

        // Close the file after finishing the read operation.
        city_plan.close();
    }

    // Run the Minimum Spanning Tree (MST) Kruskal's algorithm and get the solution tree.
    Solution min_spanning_tree = graph.MST();
    
    // We already sorted this solution before coming here, but just in case we will sort again :)
    std::sort(min_spanning_tree.first.begin(), min_spanning_tree.first.end());

    // For every edge inside the tree.
    for (Edge& e : min_spanning_tree.first)
    {
        // Print the edge information.
        std::cout << e.second.first << " " << e.second.second << " " << e.first << std::endl;
    }

    // Print total cost
    std::cout << min_spanning_tree.second << std::endl;

    // End program
    return 0;
}