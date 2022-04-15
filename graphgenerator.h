#include <vector>
#include <math.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <map>

struct Edge{
    std::string toNodeId;
    double weight;
};

constexpr int MIN = 10;
constexpr int MAX = 100;

typedef std::vector<Edge> Edges;
typedef std::map<std::string, Edges> Nodes;

void outputFormattedGraphDescription(std::string, Nodes&);
void readUnformattedFile(std::string, Nodes&);
void readFormattedFile(std::string, Nodes&);
void outputAdjacencyMatrix(std::string, Nodes&);
double fRand(double = MIN, double = MAX);

void readUnformattedFile(std::string srcfile, Nodes& nodes){
    std::ifstream file(srcfile);
    std::string line = "";

    while(getline(file, line)){
        std::stringstream ss(line);
        std::string startNodeId, endNodeId;
        double weight = fRand();

        ss >> startNodeId >> endNodeId;

        Nodes::iterator startNode = nodes.find(startNodeId);
        Nodes::iterator endNode = nodes.find(endNodeId);

        if(startNode == nodes.end()){
            nodes.insert({startNodeId, std::vector<Edge>()});
            startNode = nodes.find(startNodeId);
        }
        if(endNode == nodes.end()){
            nodes.insert({endNodeId, std::vector<Edge>()});
            endNode = nodes.find(endNodeId);
        }

        startNode->second.push_back(Edge{.toNodeId = endNodeId, .weight = weight });
        endNode->second.push_back(Edge{.toNodeId = startNodeId, .weight = weight });
    }

    file.close();
}

void outputFormattedGraphDescription(std::string outfilename, Nodes& nodes){
    std::ofstream ofile(outfilename);
    ofile << nodes.size() << std::endl;

    for(auto itr = nodes.begin(); itr != nodes.end(); itr++){
        ofile << itr->first << " ";
        for(auto e : itr->second)
            ofile << e.toNodeId << " " << e.weight << " ";
        ofile << std::endl;
    }
    ofile.close();
}

void readFormattedFile(std::string srcfile, Nodes& nodes){
    std::ifstream file(srcfile);
    std::string line = "";
    int nodeCount = (getline(file, line)) ? stoi(line) : 0;
    
    for(auto i = 0; i < nodeCount; i++){
        getline(file, line);
        std::stringstream ss(line);
        std::string startNodeId, endNodeId, adjacencies;
        double weight;

        ss >> startNodeId;
        getline(ss, adjacencies);

        Nodes::iterator startNode = nodes.find(startNodeId);

        if(startNode == nodes.end()){
            nodes.insert({startNodeId, std::vector<Edge>()});
            startNode = nodes.find(startNodeId);
        }
        
        while(ss >> endNodeId >> weight)
            startNode->second.push_back(Edge{.toNodeId = endNodeId, .weight = weight });     

        startNode->second.push_back(Edge{.toNodeId = endNodeId, .weight = weight });
    }

    file.close();
}

void outputAdjacencyMatrix(std::string filename, Nodes& nodes){
    std::ofstream ofile(filename);
    std::vector<std::vector<double>> adjacency_matrix;

    for(auto i = 0; i < nodes.size(); i++)
        adjacency_matrix[i] = std::vector<double>(nodes.size() - 1, 0.0);

    for(auto itr = nodes.begin(); itr != nodes.end(); itr++){
        int adjacencyRow = std::stoi(itr->first);
        
        for(auto i : itr->second){
            int adjacencyCol = std::stoi(i.toNodeId);
            adjacency_matrix[adjacencyRow][adjacencyCol] = i.weight;    
        }
    }

    for(auto itr = nodes.begin(); itr != nodes.end(); itr++){
        for(auto i : itr->second)
            ofile << i.weight << " ";
        ofile << std::endl;
    }

    ofile.close();
}

double fRand(double fMin, double fMax){
    double f = (double)rand() / RAND_MAX;
    double value = fMin + f * (fMax - fMin);
    return std::ceil(value * 100.0) / 100.0;
}