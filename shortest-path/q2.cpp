/* @Author

Student Name: Enes Demirag
Student ID  : 504201571
Mail        : ensdmrg@gmail.com
Date        : 23.04.2021


Dear sir/madam,

This projects consist of a Graph class with methods like Dijkstra'a Shortest Path algorithm.
Below commands can be used to build and run this project with g++.

>> g++ -std=c++11 q2.cpp -o q2
>> ./q2
>> path_info_1.txt

All of the standard libraries used in this project is given below.

<algorithm> : To find element positions inside lists and vectors.
<iostream>  : To print things to the terminal.
<fstream>   : To read things from a file.
<sstream>   : To parse sub strings
<climits>   : To assign the maximum integer value.
<string>    : String operations.
<vector>    : Storing some elements and accessing them.
<tuple>     : To store three values in a pack.
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
#include <climits>
#include <string>
#include <vector>
#include <tuple>
#include <set>
#include <map>

/* Definitions:
 * Node is just a string,
 * Edge is a pack of one int and two strings.
 */
typedef std::string Node;
typedef std::tuple<int, Node, Node> Edge;

/* This is a very simple class which stores all the nodes,
 * all the edges, and a 2D array which represents the adjacency matrix of the graph.
 */
class Graph {
private:
    std::vector<Edge> edges;
    std::vector<Node> nodes;
public:
    //int** adj_matrix;
    int adj_matrix[100][100];
    void addEdge(Edge& edge);
    void createAdjacencyMatrix();
    int minDistance(int distances[], bool visited[]);
    void printPath(int parent[], int node_index);
    void dijkstra();
};

/* This method adds a new edge into the graph.
 * Also we will store the nodes of the edges in the class attribute nodes.
 * For possible duplicate nodes to emerged, we should watch out.
 * First I want to use set instead of a vector but accessing elements of a set with indexes is not possible.
 * So I used vector and carefully check every node before pushing inside the vector.
 * */
void Graph::addEdge(Edge& edge)
{
    // Add the edge inside the graph's edges vector.
    this->edges.push_back(edge);

    // Get both end of the edge from the tuple.
    Node begin_node = std::get<1>(edge);
    Node end_node = std::get<2>(edge);

    // Only the unique nodes should be added. So check for duplicates.
	if (std::find(this->nodes.begin(), this->nodes.end(), begin_node) == this->nodes.end())
	{
        this->nodes.push_back(begin_node);
	}
	if (std::find(this->nodes.begin(), this->nodes.end(), end_node) == this->nodes.end())
	{
        this->nodes.push_back(end_node);
	}
}

/* This method will be called after all the edges were push inside a vector.
 * This method will create the adjacency matrix of the graph.
 * We need this matrix in order to search the shortest path via Dijstra's algorithm.
 * First I used double integer pointer int** adj_matrix to dynamically allocate enough memory space for the inputs.
 * For the initialization I used below code section.
    *adj_matrix = new int[nodes.size()];
    for (uint x = 0; x < nodes.size(); x++)
    {
        adj_matrix[x] = new int[nodes.size()];
        std::fill_n(adj_matrix[x], nodes.size(), 0);
    }
 * Although it works on two different linux systems I use, I got segmentation fault runtime error on the ITU server.
 * I cannot find the real reason beneath this error, so I give up this approach and simply used a fixed size 2D array
 * large enough to store given values. int adj_matrix[100][100].
 */
void Graph::createAdjacencyMatrix()
{
    // Initialize the adjacency matrix.
    // Actually we do not need this part but I want to set initial value 0 to every element.
    for (uint x = 0; x < 100; x++)
    {
        std::fill_n(adj_matrix[x], 100, 0);
    }

    // For every node in the graph
    for (uint i = 0; i < nodes.size(); i++)
    {
        // For every edge in the graph
        for (Edge& e : this->edges)
        {
            // Unpack edge variables.
            int cost = std::get<0>(e);
            Node begin_node = std::get<1>(e);
            Node end_node = std::get<2>(e);

            // Enemy constrain
            // If one of the nodes of the edge is enemy, omit this edge and not update the adjacency matrix.
            // Actually we dont need this part because even if we wrote these costs into the adjacency matrix
            // we are also checking this constrain inside the dijkstra method as well.
            if ("E" == begin_node.substr(0, 1) || "E" == end_node.substr(0, 1))
            {
                continue;
            }
            // If this edge is connected to the this node
            else if (begin_node == nodes[i])
            {
                // Find the other node of the edge inside our unique nodes vector.
                // I am using find() and distance() functions in order to get the index of the node.
                int j = std::distance(this->nodes.begin(), std::find(this->nodes.begin(), this->nodes.end(), end_node));

                // Write the cost to the intersections of this nodes inside the matrix.
                // Keep in mind that this matrix is always symmetrical along the diagonals and its a square matrix
                // with 0 values at the diagonals. Because we do not want to choose the same node again and again.
                adj_matrix[i][j] = cost;
                adj_matrix[j][i] = cost;
            }
        }
    }
}
/* This method looks for every edge and returns the closest one (minimum cost value)
 * @param distances[] Array of distance values (costs) of all possible edges.
 * @param visited[] Array of booleans which stores true if an edge was visited before and already inside the path.
 * @return int Index of the shortest chosen edge.
 */
int Graph::minDistance(int distances[], bool visited[])
{
    // Initialize min value with integer limit.
    int min = INT_MAX;
    int min_index = 0;

    // Loop every node
    for (uint v = 0; v < this->nodes.size(); v++)
    {
        // If it was not already visited and closer than previous edge.
        if (!visited[v] && distances[v] <= min)
        {
            // Write this edge's index.
            min = distances[v];
            min_index = v;
        }
    }

    // After iterating over every possible edge, return the index of closest.
    return min_index;
}

/* Printing method for the question. Prints the travelled route from beginning to the end.
 * This recursive method will called from the end node and calls itself over and over again
 * until it reaches the beginning node (whose parent is -1) and starts printing while going back on the call stack.
 * @param parents[] Index array of parent nodes.
 * @param node_index Index of the current node.
 * */
void Graph::printPath(int parents[], int node_index)
{
    // If start node reached.
    if (parents[node_index] == - 1)
    {
        std::cout << this->nodes[node_index] << " ";
        return;
    }

    // Recursive call to the parent
    printPath(parents, parents[node_index]);
    std::cout << this->nodes[node_index] << " ";
}

/* This method is the implementation of the Dijkstra's Shortest Path algorithm.
 *
 * */
void Graph::dijkstra()
{
    // For every nodes initial values are set.
    int distances[this->nodes.size()];
    bool visited[this->nodes.size()];
    int parents[this->nodes.size()];
    parents[0] = -1;

    for (uint i = 0; i < this->nodes.size(); i++)
    {
        distances[i] = INT_MAX;
        visited[i] = false;
    }

    distances[0] = 0;

    for (uint count = 0; count < this->nodes.size() - 1; count++)
    {
        // Find the closest node.
        int u = minDistance(distances, visited);

        // Make it visited.
        visited[u] = true;

        // For every nodes, look for connections.
        for (uint v = 0; v < this->nodes.size(); v++)
  
            // If it is not visited yet and the next node is closer.
            if (!visited[v] && this->adj_matrix[u][v] && distances[u] + this->adj_matrix[u][v] < distances[v])
            {
                // Check for the enemy condition.
                // This if will not even become true. Because we did not wrote the costs of the enemies. (they were omited at the beginning).
                if (this->nodes[u].substr(0, 1) == "E")
                {
                    continue;
                }

                // Look at every edge connected to the node u and check if it has any enemy node closer than 5.
                bool smaller_than_5 = false;
                for (Edge e : this->edges)
                {
                    if ((std::get<1>(e) == nodes[v] && std::get<2>(e).substr(0, 1) == "E") || (std::get<2>(e) == nodes[v] && std::get<1>(e).substr(0, 1) == "E"))
                    {
                        int cost = std::get<0>(e);
                        if (cost < 5)
                        {
                            smaller_than_5 = true;
                            break;
                        }
                    }
                }

                // If there is a enemy within 5 value, ignore this node and continue.
                if (smaller_than_5)
                {
                    continue;
                }

                // Append new node v to the current node u.
                parents[v] = u;

                // Update the distance value of the current node.
                distances[v] = distances[u] + this->adj_matrix[u][v];
            } 
    }

    // Print the full route.
    printPath(parents, this->nodes.size() - 1);

    // Print the total distance value.
    std::cout << distances[this->nodes.size() - 1] << std::endl;
}

/* This is the main function.
 * It takes a file name from the terminal,
 * First creates a graph with the edges given in the file.
 * Then find the shortest path from them first node the the end node.
 * using Dijkstra's algorithm.
 */
int main()
{
    // Create an empty graph.
    Graph g;

    // Define variables for paring operations.
    std::string file_name, line, str;
    std::vector<std::string> params;

    // Get the input file name from terminal.
    std::cin >> file_name;
    std::ifstream road_map(file_name);

    // Read from file and fill the graph with given edges.
    if (road_map.is_open())
    {
        // Parse every line of the file
        while (std::getline(road_map, line))
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
                Edge e(std::stoi(params[2]), params[0], params[1]);
                g.addEdge(e);
            }
        }

        // Close the file after finishing the read operation.
        road_map.close();
    }

    // Create the adjacency matrix after adding every edge into the graph.
    g.createAdjacencyMatrix();

    // Run Dijkstra's Shortest Path Algorithm.
    g.dijkstra();

    // End program
    return 0;
}
