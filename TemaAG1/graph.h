#ifndef GRAPH_H
#define GRAPH_H
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "edge.h"
#include <vector>

using namespace std;
class Graph
{
    vector<Node> nodes;
    vector<Edge> edges;
    vector<vector<int>> Matrice;
    bool eOrientat;
public:
    Graph();
    void addNode(Node n)
    {
        vector<int> LinieNoua(nodes.size(), 0);
        Matrice.push_back(LinieNoua);
        nodes.push_back(n);
        for(int i =0; i< (int)nodes.size(); i++)
        {
            Matrice[i].push_back(0);
        }
        PrintMatrice();
    }
    void addEdge(Edge a)
    {
        edges.push_back(a);
        Matrice[a.getFirstNode().getInfo()-1][a.getSecondNode().getInfo()-1] = 1;
        PrintMatrice();
    }
    int getNumberOfNodes(){return (int)nodes.size();}
    vector<Node> getNodes(){return nodes;}
    vector<Edge> getEdges(){return edges;}
    bool getEOrientat() {return eOrientat;}
    void setNodes(vector<Node> nodes) {this->nodes = nodes;}
    void setEdges(vector<Edge> edges) {this->edges = edges;}
    void setEOrientat(bool eOrientat){this->eOrientat = eOrientat;}
    vector<vector<int>> getMatrice() {return Matrice;}

    void PrintMatrice()
    {
        QString filename = "C:\\Users\\Magda\\Documents\\TemaAG1\\Matrice.txt";
            QFile file(filename);
            if (file.open(QIODevice::ReadWrite))
            {
                file.resize(0);
                QTextStream stream(&file);
                int numberOfNodes = (int)nodes.size();

                stream << numberOfNodes << "\n";

                for(int i = 0; i < numberOfNodes; i++)
                {
                    for(int j = 0; j < numberOfNodes; j++)
                    {
                       stream << Matrice[i][j] << " ";
                    }
                    stream << "\n";
                }
                stream.flush();
                file.close();
            }
            else
            {
                qDebug() << "Couldn't open file";
            }
    }
};

#endif // GRAPH_H
