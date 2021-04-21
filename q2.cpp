#include <climits>
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <set>
#include <tuple>

typedef std::string Node;
typedef std::tuple<int, std::string, std::string> Edge;

class Graph {
private:
    std::vector<Node> nodes;
    std::vector<Edge> edges;
public:
    int** adj_matrix;
    void addEdge(Edge& edge);
    void createAdjacencyMatrix();
};

void Graph::addEdge(Edge& edge)
{
    this->edges.push_back(edge);

    Node begin_node = std::get<1>(edge);
    Node end_node = std::get<2>(edge);

    // Only the unique nodes shoud be added.
	if (std::find(this->nodes.begin(), this->nodes.end(), begin_node) == this->nodes.end())
	{
        this->nodes.push_back(begin_node);
	}
	if (std::find(this->nodes.begin(), this->nodes.end(), end_node) == this->nodes.end())
	{
        this->nodes.push_back(end_node);
	}
}

void Graph::createAdjacencyMatrix()
{
    // Initialize the matrix, allocate memory and set initial values.
    *adj_matrix = new int[nodes.size()];
    for (uint x = 0; x < nodes.size(); x++)
    {
        adj_matrix[x] = new int[nodes.size()];
        std::fill_n(adj_matrix[x], nodes.size(), 9999);
    }


    // Put cost values
    for (uint i = 0; i < nodes.size(); i++)
    {
        for (Edge& e : this->edges)
        {
            int cost = std::get<0>(e);
            Node begin_node = std::get<1>(e);
            Node end_node = std::get<2>(e);

            // Enemy constrain
            if ("E" == begin_node.substr(0, 1) || "E" == end_node.substr(0, 1))
            {
                continue;
            }
            else if (begin_node == nodes[i])
            {
                // Find the end node's index.
                uint j = std::distance(this->nodes.begin(), std::find(this->nodes.begin(), this->nodes.end(), end_node));
                adj_matrix[i][j] = cost;
                adj_matrix[j][i] = cost;
            }
        }
    }
}

int main()
{
    // Create an empty graph.
    Graph g;

    // Read from file
    std::string file_name;
    std::string line;
    std::string str;
    std::vector<std::string> params;

    //std::cin >> file_name;
    std::ifstream city_plan("path_info_1.txt");

    // Fill the graph.
    if (city_plan.is_open())
    {
        while (std::getline(city_plan, line))
        {
            params.clear();
            std::istringstream parser(line);
            while (getline(parser, str, ','))
            {
                params.push_back(str);
            }
            if (3 == params.size())
            {
                Edge e(std::stoi(params[2]), params[0], params[1]);
                g.addEdge(e);
            }
        }
        city_plan.close();
    }

    g.createAdjacencyMatrix();

    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            std::cout << g.adj_matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
    return 0;
}