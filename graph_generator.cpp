#include "graphgenerator.h"
using namespace std;


int main(int argc, char* argv[]){
    Nodes nodes = Nodes();
    readUnformattedFile("Email-Enron.txt", nodes);

    switch(stoi(argv[2])){
        case(1):
            outputFormattedGraphDescription("graph.in", nodes);
            break;
        case(2):
            outputAdjacencyMatrix("adjacencymatrix.txt", nodes);
            break;
    }
    return 0;
}