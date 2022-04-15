#include "dijkstra.h"
#include <algorithm>
//#include <chrono>
//using namespace std::chrono;

std::string src_file_name;
std::string start_node_id;
std::string end_node_id;

std::vector<Node*> nodes;
std::map<std::string, Node*> node_addresses;

//_V2::system_clock::time_point start;
//_V2::system_clock::time_point end;


void read_into_nodes();
void dijkstra();
void printPath();
void free_memory();
//void start_timer();
//void finish_timer(std::string);

int main(int argc, char* argv[]){
    src_file_name = argv[1];
    start_node_id = argv[2];
    end_node_id = argv[3];
    nodes = std::vector<Node*>();
    node_addresses = std::map<std::string, Node*>();

    //start_timer();
    read_into_nodes();
    //finish_timer("read_into_nodes()");
    
    //start_timer();
    dijkstra();
    //finish_timer("dijkstra()");

    
    printPath();
    free_memory();

    return 0;
}

void read_into_nodes(){
    std::ifstream file(src_file_name);
    std::string line = "";
    int node_count = (getline(file, line)) ? stoi(line) : 0;
    
    for(auto index = 0; index < node_count; index++){
        nodes.push_back(new Node{});

        getline(file, line);
        std::stringstream ss(line);

        ss >> nodes[index]->id;
        getline(ss, nodes[index]->adjacent_info);

        if(nodes[index]->id == start_node_id)
            nodes[index]->estimate = 0.0;

        node_addresses.insert(std::pair<std::string, Node*>(nodes[index]->id, nodes[index]));
    }

    file.close();
}

void dijkstra(){
    while(!nodes.empty()){
        auto current_node = extract_min(nodes);
        std::stringstream ss(current_node->adjacent_info);
        std::string id;
        double weight;

        if(current_node->id == end_node_id)
            return;

        while(ss >> id >> weight){
            auto adj_node = node_addresses.find(id);

            if(adj_node->second->estimate > (current_node->estimate + weight)){
                adj_node->second->estimate = (current_node->estimate + weight);
                adj_node->second->predecessor = current_node;
            }
        }
    }
}

void printPath(){
    auto currentNode = node_addresses.find(end_node_id)->second;
    double pathWeight = currentNode->estimate;
    std::string path = "";

    while(currentNode->predecessor != nullptr){
        if(path.empty())
            path = currentNode->id;
        else
            path = (currentNode->id + " " + path);
        currentNode = currentNode->predecessor;
    }

    if(path.empty() && currentNode->id != start_node_id)
        std::cout << "no path found from " << start_node_id << " to " << end_node_id << std::endl;
    else
        std::cout << currentNode->id << " " << path << std::endl << pathWeight << std::endl;

    currentNode = nullptr;
}   

void free_memory(){
    // Empty left over nodes in vector while also clearing node predecessor pointer
    if(!nodes.empty()){
        for(int i = nodes.size() - 1; i >= 0; i--){
            auto itr = nodes[i];
            itr->predecessor = nullptr;
            nodes.pop_back();
        }  
    }

    // Remaining references to nodes, okay to delete each index
    while(!node_addresses.empty()){
        auto itr = node_addresses.begin();
        delete itr->second;
        node_addresses.erase(itr);
    }
}
/*
void start_timer(){
    start = high_resolution_clock::now();
}

void finish_timer(std::string function){
    auto duration = duration_cast<seconds>(high_resolution_clock::now() - start);
    auto average = std::chrono::duration<double>(duration).count() / 2;

    std::cout << "Time taken by " << function << " : " << duration.count() << " milliseconds" << std::endl;
    std::cout << "\t" << average << " milliseconds per node" << std::endl << std::endl;
}
*/