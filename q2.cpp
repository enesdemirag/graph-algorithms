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

typedef std::tuple<int, std::string, std::string> Edge;

class Graph {
public:
    Graph(int node_number);
    std::vector<std::string> nodes;
    std::vector<Edge*> edges;
    void addEdge(Edge* edge);
    int adj_matrix[][];
    void fillMatrix();
};

Graph::Graph(int node_number)
{
    adj_matrix = new int[node_number][node_number];
}

void Graph::addEdge(Edge* edge)
{
    edges.push_back(edge);

    if (std::find(nodes.begin(), nodes.end(), std::get<1>(*edge)) == nodes.end())
    {
        nodes.push_back(std::get<1>(*edge));
    }
    if (std::find(nodes.begin(), nodes.end(), std::get<2>(*edge)) == nodes.end())
    {
        nodes.push_back(std::get<2>(*edge));
    }
}

void Graph::fillMatrix()
{
    for (int i = 0; i < nodes.size(); i++)
    {
        for (int ii = 0; ii < nodes.size(); ii++)
        {
            for (Edge* e : edges)
            {
                if (std::get<1>(*e) == nodes[i] && std::get<2>(*e) == nodes[ii] ||
                    std::get<1>(*e) == nodes[ii] && std::get<2>(*e) == nodes[i])
                {
                    adj_matrix[i][ii] = std::get<0>(*e);
                }
                else
                {
                    adj_matrix[i][ii] = 0;
                }
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

    std::cin >> file_name;
    std::ifstream city_plan(file_name);

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
                Edge* e = new Edge(std::stoi(params[2]), params[0], params[1]);
                g.addEdge(e);
            }
        }
        city_plan.close();
    }


    g.fillMatrix();

    return 0;
}