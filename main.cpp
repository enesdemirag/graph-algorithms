#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

class Graph {

    typedef pair<string, string> Edge; // calling Edge
    typedef pair<int, Edge> WEdge; // Weighted edge



private:
    set<string> nodes; // Keep track of unique Nodes in graph
    vector<WEdge> graph;
    map<string, string> disjoint; // map for disjoints

    const string& add_node(string node) {
        pair<set<string>::iterator,bool> insert_ret;
        insert_ret = nodes.insert(node);

        const string& retVal = *insert_ret.first;

        disjoint.insert(pair<string, string>(node, node));

        return retVal;
    }

    string& mst_find(string& index) {
        if (index != disjoint[index]) {
            disjoint[index] = mst_find(disjoint[index]);
        }

        return disjoint[index];
    }

public:
    void add_edge(string start, string end, int weight) {
        (void) add_node(start);
        (void) add_node(end);

        graph.push_back(WEdge(weight, Edge(start, end)));
    }

    int mst() {
        int total_w = 0;

        sort(graph.begin(), graph.end());
        vector<tuple<int, string, string>> out;

        vector<WEdge>::iterator it;
        for (it = graph.begin(); it != graph.end(); ++it) {
            string start = it->second.first;
            string end = it->second.second;

            string& set_start = mst_find(start);
            string& set_end = mst_find(end);

            if (start == "GP" && end.substr(0, 2) == "Ch")
            {
                set_start = mst_find(set_start);
                set_end = mst_find(set_end);
                disjoint[set_end] = set_start;

                out.push_back(make_tuple(it->first, start, end));
                total_w += it->first;
                break;
            }

        }

        for (it = graph.begin(); it != graph.end(); ++it) {
            string start = it->second.first;
            string end = it->second.second;

            string& set_start = mst_find(start);
            string& set_end = mst_find(end);

            if (start == "GP" && end == "Hipp")
            {
                set_start = mst_find(set_start);
                set_end = mst_find(set_end);
                disjoint[set_end] = set_start;

                out.push_back(make_tuple(it->first, start, end));
                total_w += it->first;
                break;
            }

        }


        for (it = graph.begin(); it != graph.end(); ++it) {
            string start = it->second.first;
            string end = it->second.second;

            string& set_start = mst_find(start);
            string& set_end = mst_find(end);

            if(start == "Hipp" && end.substr(0,3) == "Bas")
            {
                continue;
            }

            if( end == "Hipp" && start.substr(0,3) == "Bas")
            {
                continue;
            }

            if( end.substr(0, 2) == "Hp" && start.substr(0, 2) == "Hp")
            {
                continue;
            }


            if (set_start != set_end) {
                //cout << start << " " << end  << " " << it->first<< endl;
                out.push_back(make_tuple(it->first, start, end));
                total_w += it->first;

                set_start = mst_find(set_start);
                set_end = mst_find(set_end);
                disjoint[set_end] = set_start;

            }

        }
        sort(out.begin(), out.end());
        for (tuple<int, string, string> t : out)
        {
            cout << get<1>(t) << " " << get<2>(t)  << " " << get<0>(t) << endl;
        }

        cout << total_w << endl;

        return 0;
    }

    // Print out graph edges with weights
    friend ostream& operator << (ostream& outs, Graph& graph) {
        typename vector<WEdge>::iterator it;

        for (it = graph.graph.begin(); it != graph.graph.end(); ++it) {
            outs << it->second.first << " --" << it->first << "-- " << it->second.second << endl;
        }

        return outs;
    }
};

class City : public Graph {};

int main() {

    City deneme;

    string line;
    string line_param;
    vector<string> line_parse;
    //stringstream weight_converter;
    string weight_converter;

    ifstream city_plan("city_plan.txt");

    if (city_plan.is_open()) { // Sanity check
        // Parsing file into graph
        while (getline(city_plan, line)) {
            line_parse.clear();

            istringstream parsing_line(line);
            while (getline(parsing_line, line_param, ',')) {
                line_parse.push_back(line_param);
            }

            if (3 == line_parse.size()) { // Sanity check
                // weight_converter << line_parse[2];

                weight_converter = line_parse[2];
                int weight = std::stoi(weight_converter);
                deneme.add_edge(line_parse[0], line_parse[1], weight);

                /*int weight = 0;
                weight_converter >> weight;
                deneme.add_edge(line_parse[0], line_parse[1], weight);*/
            }
        }

        city_plan.close();
    }

    deneme.mst();

    return 0;
}