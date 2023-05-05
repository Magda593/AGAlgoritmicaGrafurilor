#ifndef EDGE_H
#define EDGE_H
#include "node.h"

class Edge
{
    Node firstNode, secondNode;
public:
    Edge();
    Edge(Node fN, Node sN){
        firstNode = fN;
        secondNode = sN;
    }
    Node getFirstNode(){return firstNode;}
    Node getSecondNode(){return secondNode;}
    void setFirstNode(Node firstNode){this->firstNode = firstNode;}
    void setSecondNode(Node secondNode) {this->secondNode = secondNode;}
};

#endif // EDGE_H
