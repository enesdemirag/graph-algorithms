#include <cstdio>
#include <climits>
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
    std::vector<Edge> edges;
public:
    std::vector<Node> nodes;
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
    for (int x = 0; x < nodes.size(); x++)
    {
        adj_matrix[x] = new int[nodes.size()] {0};
    }

    // Put cost values
    for (int i = 0; i < nodes.size(); i++)
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
                int j = std::distance(this->nodes.begin(), std::find(this->nodes.begin(), this->nodes.end(), end_node));
                adj_matrix[i][j] = cost;
                adj_matrix[j][i] = cost;
            }
        }
    }
}

using namespace std;
int V = 12;

int minDistance(int distances[], bool visited[])
{
    // Initialize min value
    int min = INT_MAX;
    int min_index = 0;
  
    for (int v = 0; v < V; v++)
    {
        if (visited[v] == false && distances[v] <= min)
        {
             min = distances[v], min_index = v;
        }
    }
    return min_index;
}

std::vector<Node> global_nodes;

void printPath(int parent[], int node_index)
{
    // If start node reached.
    if (parent[node_index] == - 1)
    {
        cout << global_nodes[node_index] << " ";
        return;
    }
  
    printPath(parent, parent[node_index]);
    cout << global_nodes[node_index] << " ";
}
  
void dijkstra(int** graph, int src)
{
      
    // The output array. dist[i]
    // will hold the shortest
    // distance from src to i
    int dist[V]; 
  
    // sptSet[i] will true if vertex
    // i is included / in shortest
    // path tree or shortest distance 
    // from src to i is finalized
    bool sptSet[V];
  
    // Parent array to store
    // shortest path tree
    int parent[V];
  
    // Initialize all distances as 
    // INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
    {
        parent[0] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
  
    // Distance of source vertex 
    // from itself is always 0
    dist[src] = 0;
  
    // Find shortest path
    // for all vertices
    for (int count = 0; count < V - 1; count++)
    {
        // Pick the minimum distance
        // vertex from the set of
        // vertices not yet processed. 
        // u is always equal to src
        // in first iteration.
        int u = minDistance(dist, sptSet);
  
        // Mark the picked vertex 
        // as processed
        sptSet[u] = true;
  
        // Update dist value of the 
        // adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < V; v++)
  
            // Update dist[v] only if is
            // not in sptSet, there is
            // an edge from u to v, and 
            // total weight of path from
            // src to v through u is smaller
            // than current value of
            // dist[v]
            if (!sptSet[v] && graph[u][v] &&
                dist[u] + graph[u][v] < dist[v])
            {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            } 
    }
  
    // print the constructed
    // distance array
    printPath(parent, V - 1);
    cout << dist[V - 1];
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

    global_nodes = g.nodes;
    dijkstra(g.adj_matrix, 0);

    return 0;
}