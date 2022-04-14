#include "dijkstra.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <set>
using namespace std;

string src_file_name;
string start_node_id;
string end_node_id;

void read_into_nodes(deque<Node>&, string, string);
vector<Node> dijkstra(deque<Node>&);


int main(int argc, char* argv[]){
    deque<Node> src_nodes;
    vector<Node> result_nodes;

    src_file_name = argv[1];
    start_node_id = argv[2];
    end_node_id = argv[3];

    read_into_nodes(src_nodes);
    build_min_heap(src_nodes);
    dijkstra(src_nodes, result_nodes);

    return 0;
}

void read_into_nodes(deque<Node>& nodes){
    ifstream file(src_file_name);
    string line;

    // Size nodes to node count read from first line. If a line is not read, keep it empty
    //      to avoid performing next loop
    nodes = (getline(file, line)) ? deque<Node>(stoi(line), Node{}) : deque<Node>(0);

    for(auto& n : nodes){
        getline(file, line);
        stringstream ss(line);
        ss >> n.id;
        getline(ss, n.adjacent_info);
        if(n.id == start_node_id)
            n.estimate = 0.0;
    }

    file.close();
}

void dijkstra(deque<Node>& nodes, vector<Node>& result){
    while(!nodes.empty()){
        auto current_node = extract_min(nodes);


        if(current_node.id == start_node_id)
            return;
    }
}