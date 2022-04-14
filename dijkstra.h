#include <deque>
#include <math.h>
#include <string>

struct Node{
    std::string id = "";
    double estimate = __DBL_MAX__;
    //int predecessor;
    std::string adjacent_info = "";
};

int left(int i, bool start_index_zero = true){
    return (start_index_zero) ? ((i * 2) + 1) : (i * 2);
}

int right(int i, bool start_index_zero = true){
    return (start_index_zero) ? (2 * (i + 1)) : (2 * i + 1);
}

int parent(int i){
    return floor(i / 2);
}

void min_heapify(std::deque<Node>& nodes, int i){
    int smallest;
    auto l = left(i);
    auto r = right(i);

    if(l < nodes.size() && (nodes[l].estimate < nodes[i].estimate))
        smallest = l;
    else
        smallest = i;

    if(r < nodes.size() && (nodes[r].estimate < nodes[smallest].estimate))
        smallest = r;
    if(smallest != i){
        auto temp = nodes[i];
        nodes[i] = nodes[smallest];
        nodes[smallest] = temp;
        min_heapify(nodes, smallest);
    }
}

Node extract_min(std::deque<Node>& nodes){
    if(nodes.size() < 0)
        std::__throw_underflow_error("heap underflow");
    Node max = nodes[0];
    nodes[0] = nodes[nodes.size() - 1];
    nodes.pop_back();
    min_heapify(nodes, 0);
    return max;
}

void decrease_key(std::deque<Node>& nodes, int i){
    if(nodes[i].estimate < nodes[0].estimate)
        std::__throw_invalid_argument("new key is smaller than current key");

    while((i > 0) && (nodes[parent(i)].estimate > nodes[i].estimate)){
        auto current = nodes[i];
        nodes[i] = nodes[parent(i)];
        nodes[parent(i)] = current;
        i = parent(i);
    }
}

void build_min_heap(std::deque<Node>& nodes){
    for(int i = floor(nodes.size()); i >= 0; i--)
        min_heapify(nodes, i);
}