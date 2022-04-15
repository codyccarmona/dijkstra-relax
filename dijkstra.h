#include <vector>
#include <math.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <map>

struct Node{
    double estimate = __DBL_MAX__;
    std::string adjacent_info = "";
    Node* predecessor = nullptr;
    std::string id = "";
};

int left(int i){
    return ((i * 2) + 1);
}

int right(int i){
    return (2 * (i + 1));
}

int parent(int i){
    return std::floor(i / 2);
}

void min_heapify(std::vector<Node*>& nodes, int i){
    int smallest;
    auto l = left(i);
    auto r = right(i);

    if(l < nodes.size() && (nodes[l]->estimate < nodes[i]->estimate))
        smallest = l;
    else
        smallest = i;

    if(r < nodes.size() && (nodes[r]->estimate < nodes[smallest]->estimate))
        smallest = r;

    if(smallest != i){
        auto temp = nodes[i];
        nodes[i] = nodes[smallest];
        nodes[smallest] = temp;
        min_heapify(nodes, smallest);
    }
}

Node* extract_min(std::vector<Node*>& nodes){
    if(nodes.size() < 0)
        std::__throw_underflow_error("heap underflow");
    auto max = nodes[0];
    nodes[0] = nodes[nodes.size() - 1];
    nodes[nodes.size() - 1] = nullptr;
    nodes.pop_back();
    min_heapify(nodes, 0);
    return max;
}

void heap_decrease_key(std::vector<Node*>& nodes, int index){
    while(index >= 0 && nodes[parent(index)] > nodes[index]){
        auto current = nodes[index];
        nodes[index] = nodes[parent(index)];
        nodes[parent(index)] = current;
        current = nullptr;
        index = parent(index);
    }
}

void min_heap_insert(std::vector<Node*>& nodes, Node* node){
    nodes.push_back(node);
    heap_decrease_key(nodes, nodes.size() - 1);
}