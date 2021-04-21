#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>

typedef std::string Node;
typedef std::pair<Node, Node> Connection;
typedef std::pair<int, Connection> Edge;
typedef std::pair<std::vector<Edge>, int> Solution;

class Graph {
private:
    std::vector<Edge> edges;
    std::set<Node> nodes;
    std::map<Node, Node> tree;
public:
    void addNode(Node& node);
    Node& findNode(Node& node);
    void addEdge(Edge& edge);
    Solution MST();
};

void Graph::addNode(Node& node)
{
    this->nodes.insert(node);
    this->tree.insert(Connection(node, node));
}

Node& Graph::findNode(Node& node)
{
    if (node != this->tree[node])
    {
        this->tree[node] = findNode(this->tree[node]);
    }
    return this->tree[node];
}

void Graph::addEdge(Edge& edge)
{
    addNode(edge.second.first);
    addNode(edge.second.second);
    this->edges.push_back(edge);
}

Solution Graph::MST()
{
    std::vector<Edge> min_spanning_tree;
    int total_cost = 0;

    // Sort the edges of the graph.
    std::sort(this->edges.begin(), this->edges.end());
    
    // Constrain 2 and 5
    for (Edge& e : this->edges)
    {
        Node begin_node = e.second.first;
        Node end_node = e.second.second;

        Node src = findNode(begin_node);
        Node dst = findNode(end_node);
        int cost = e.first;

        if ("GP" == begin_node && "Hipp" == end_node)
        {
            src = findNode(src);
            dst = findNode(dst);
            tree[dst] = src;

            min_spanning_tree.push_back(Edge(cost, Connection(begin_node, end_node)));
            total_cost += cost;
            break;
        }
    }

    // Constrain 3 and 4
    for (Edge& e : this->edges)
    {
        Node begin_node = e.second.first;
        Node end_node = e.second.second;

        Node src = findNode(begin_node);
        Node dst = findNode(end_node);
        int cost = e.first;

        if (("GP" == begin_node && "Ch" == end_node.substr(0, 2)) || ("GP" == end_node && "Ch" == begin_node.substr(0, 2)))
        {
            src = findNode(src);
            dst = findNode(dst);
            tree[dst] = src;

            min_spanning_tree.push_back(Edge(cost, Connection(begin_node, end_node)));
            total_cost += cost;
            break;
        }
    }

    // Spanning
    for (Edge& e : this->edges)
    {
        Node begin_node = e.second.first;
        Node end_node = e.second.second;

        Node src = findNode(begin_node);
        Node dst = findNode(end_node);
        int cost = e.first;

        if ("Hp" == begin_node.substr(0, 2) && "Hp" == end_node.substr(0, 2)) // Constrain 7
        {
            continue;
        }
        else if (("Hipp" == begin_node && "Bas" == end_node.substr(0, 3)) || ("Bas" == begin_node.substr(0, 3) && "Hipp" == end_node)) // Constrain 6
        {
            continue;
        }
        else if (src != dst)
        {
            src = findNode(src);
            dst = findNode(dst);
            tree[dst] = src;

            min_spanning_tree.push_back(Edge(cost, Connection(begin_node, end_node)));
            total_cost += cost;
        }
    }

    sort(min_spanning_tree.begin(), min_spanning_tree.end());

    return Solution(min_spanning_tree, total_cost);
}

int main()
{
    // Create an empty graph.
    Graph graph;

    // Read from file
    std::string file_name, line, str;
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
                Edge e(std::stoi(params[2]), Connection(params[0], params[1]));
                graph.addEdge(e);
            }
        }
        city_plan.close();
    }

    // Run the Minimum Spanning Tree algorithm.
    Solution min_spanning_tree = graph.MST();
    
    // Print edges
    std::sort(min_spanning_tree.first.begin(), min_spanning_tree.first.end());
    for (Edge& e : min_spanning_tree.first)
    {
        std::cout << e.second.first << " " << e.second.second << " " << e.first << std::endl;
    }

    // Print total cost
    std::cout << min_spanning_tree.second << std::endl;

    return 0;
}