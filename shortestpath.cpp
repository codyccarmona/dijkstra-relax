#include "dijkstra.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
#include <deque>
using namespace std;

string src_file_name;
string start_node_id;
string end_node_id;

void read_into_nodes(vector<Node*>&, map<string, Node*>&);
void dijkstra(vector<Node*>&, map<string, Node*>&);


int main(int argc, char* argv[]){
    vector<Node*> nodes;
    map<string, Node*> node_addresses;

    src_file_name = argv[1];
    start_node_id = argv[2];
    end_node_id = argv[3];

    read_into_nodes(nodes, node_addresses);
    build_min_heap(nodes);
    dijkstra(nodes, node_addresses);

    Node* node_itr = node_addresses.find(end_node_id)->second;
    string path = "";
    double weight = node_itr->estimate;

    while(node_itr->id != start_node_id){
        path += node_itr->id;
        path += " ";
        node_itr = node_itr->predecessor;
    }

    std::cout << path << " " << node_itr->id << std::endl << weight << std::endl;
    node_itr = nullptr;
    
    
    
    nodes.erase(nodes.begin(), nodes.end());
    node_addresses.erase(node_addresses.begin(), node_addresses.end());
     
    return 0;
}

void read_into_nodes(vector<Node*>& nodes, map<string, Node*>& src_nodes){
    ifstream file(src_file_name);
    map<string, Node*> node_addresses;
    string line = "";
    int node_count = (getline(file, line)) ? stoi(line) : 0;
    
    for(auto index = 0; index < node_count; index++){
        string node_id;
        nodes.push_back(new Node{});
        getline(file, line);
        stringstream ss(line);

        ss >> nodes[index]->id;
        getline(ss, nodes[index]->adjacent_info);

        if(nodes[index]->id == start_node_id)
            nodes[index]->estimate = 0.0;

        src_nodes.insert(pair<string, Node*>(nodes[index]->id, nodes[index]));
    }

    file.close();
}

void dijkstra(vector<Node*>& nodes, map<string, Node*>& node_addresses){
    while(!nodes.empty()){
        auto current_node = extract_min(nodes);
        stringstream ss(current_node->adjacent_info);
        string id;
        double weight;
        while(ss >> id >> weight){
            auto adj_node = node_addresses.find(id);
            if(adj_node->second->estimate > (current_node->estimate + weight)){
                adj_node->second->estimate = (current_node->estimate + weight);
                adj_node->second->predecessor = current_node;
            }
        }
    }
}
