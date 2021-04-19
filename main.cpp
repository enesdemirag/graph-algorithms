#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

typedef std::string Node;

struct Connection {
    Node src;
    Node dst;
};

typedef std::pair<int, Connection> Edge;

bool comparePtrToWeight(Edge& a, Edge& b)
{
    return (a.first < b.first);
}

class Graph {
private:
    std::set<Node> nodes;
    std::vector<Edge> graph;
    std::map<Node, Node> tree;
public:
    const Node& addNode(Node& node);
    Node& findNode(Node& node);
    void addEdge(Edge& edge);
    std::pair<std::vector<Edge>, int> MST();
};

const Node& Graph::addNode(Node& node)
{
    std::pair<std::set<Node>::iterator, bool> insert_result = nodes.insert(node);
    const Node& result = *insert_result.first;
    this->tree.insert(std::pair<Node, Node>(node, node));
    return result;
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
    addNode(edge.second.src);
    addNode(edge.second.dst);

    this->graph.push_back(edge);
}


std::pair<std::vector<Edge>, int> Graph::MST()
{
    std::vector<Edge> min_spanning_tree;
    int total_cost = 0;

    // Sort the edges of the graph.
    std::sort(this->graph.begin(), this->graph.end(), comparePtrToWeight);

    std::vector<Edge>::iterator it;
    // Constrain 2 and 5
    for (it = graph.begin(); it != graph.end(); ++it)
    {
        Node start_node = it->second.src;
        Node end_node = it->second.dst;

        Node& src = findNode(start_node);
        Node& dst = findNode(end_node);

        if ("GP" == src && "Hipp" == dst)
        {
            src = findNode(src);
            dst = findNode(dst);
            tree[dst] = src;

            Connection e = { src, dst };
            min_spanning_tree.push_back(std::make_pair(it->first, e));
            total_cost += it->first;
            break;
        }
    }

    // Constrain 3 and 4
    for (it = graph.begin(); it != graph.end(); ++it)
    {
        Node start_node = it->second.src;
        Node end_node = it->second.dst;

        Node& src = findNode(start_node);
        Node& dst = findNode(end_node);

        if (("GP" == src && "Ch" == dst.substr(0, 2)) || ("GP" == dst && "Ch" == src.substr(0, 2)))
        {
            src = findNode(src);
            dst = findNode(dst);
            tree[dst] = src;

            Connection e = { src, dst };
            min_spanning_tree.push_back(std::make_pair(it->first, e));
            total_cost += it->first;
            break;
        }
    }

    for (it = graph.begin(); it != graph.end(); ++it)
    {
        Node start_node = it->second.src;
        Node end_node = it->second.dst;

        Node& src = findNode(start_node);
        Node& dst = findNode(end_node);

        if ("Hp" == src.substr(0, 2) && "Hp" == dst.substr(0, 2)) // Constrain 7
        {
            continue;
        }
        else if (("Hipp" == src && "Bas" == dst.substr(0, 3)) || ("Bas" == src.substr(0, 3) && "Hipp" == dst)) // Constrain 6
        {
            continue;
        }
        else
        {
            src = findNode(src);
            dst = findNode(dst);
            tree[dst] = src;

            Connection e = { src, dst };
            min_spanning_tree.push_back(std::make_pair(it->first, e));
            total_cost += it->first;
            break;
        }
    }

    sort(min_spanning_tree.begin(), min_spanning_tree.end(), comparePtrToWeight);

    return std::pair<std::vector<Edge>, int>(min_spanning_tree, total_cost);
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
                Connection c = { params[0], params[1] };
                std::pair<int, Connection> e = std::make_pair(std::stoi(params[2]), c);
                g.addEdge(e);
            }
        }
        city_plan.close();
    }

    // Run the Minimum Spanning Tree algorithm.
    std::pair<std::vector<Edge>, int> min_spanning_tree = g.MST();

    // Print edges
    for (Edge& e : min_spanning_tree.first)
    {
        std::cout << e.second.src << " " << e.second.dst << " " << e.first << std::endl;
    }

    // Print total cost
    std::cout << min_spanning_tree.second << std::endl;

    return 0;
}
