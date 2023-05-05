#ifndef GRAPH_H
#define GRAPH_H
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "edge.h"
#include <vector>
#include<QStringList>

using namespace std;
class Graph
{
    vector<Node> nodes;
    vector<Edge> edges;
    vector<vector<int>> Matrice;
    vector<vector<int>> Labirint;
    vector<int> Lista;
    string *Lab;
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
    void addEdgeMat(Edge a, int i, int j)
    {
        edges.push_back(a);
        Matrice[i][j] = 1;
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
    vector<vector<int>> getLabirint() {return Labirint;}

    void createNodes(int x, int y, int a)
    {
        QPointF coord(x,y);
        addNode(Node(coord,a));
    }

    void PrintMatrice()
    {
        QString filename = "C:\\Users\\Magda\\Documents\\TemaAG3\\Matrice.txt";
            QFile file(filename);
            if (file.open(QIODevice::ReadWrite))
            {
                file.resize(0);
                QTextStream stream(&file);
                int numberOfNodes = (int)nodes.size();

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

    void ReadFromLabirint()
    {
        QString filename = "C:\\Users\\Magda\\Documents\\TemaAG3\\Labirint.txt";
        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly))
        {
            qDebug() << "error opening file: " << file.error();
            return;
        }
        QTextStream instream(&file);

        for(int i = 0; i < 6; i++)
        {
            vector<int> LabirintCurent;
            for(int j = 0; j < 6; j++)
            {
               int value;
               instream >> value;
               LabirintCurent.push_back(value);

            }
            qDebug() << LabirintCurent;
            Labirint.push_back(LabirintCurent);
        }
    }

    void Parcurgere()
    {
//        int i=0;
//        int j=0;
         for(Node n1:nodes)
         {
             for(Node n2:nodes)
             {
                 if(n1.getInfo()!=0 && n2.getInfo()!=0)
                 {
                     Edge e(n1,n2);
                     addEdge(e);
                     break;
                 }
             }
         }
    }

    void CreateGraph()
    {
        int x = 50;

        for(int i=0;i < (int)Labirint.size(); i++)
        {
            int y = 20;
            for(int j=0; j < (int)Labirint.size(); j++)
            {

                y= y + 30 ;
                createNodes(x,y,Labirint[j][i]);

            }
            x = x+30;
            qDebug() << "\n";
        }
        for(Edge a: edges)
        {
            qDebug() << a.getFirstNode().getInfo() << " "<<a.getSecondNode().getInfo();
        }
    }



    void BFS()
    {
        int s=0;
        vector<int> queueV;
        vector<int> predecesor;
        int nrNodes = (int)nodes.size() - 1;
        vector<bool> visited;

        visited[s] = true;
        queueV.push_back(s);

        for(int i = 0; i<nrNodes; i++)
        {
            predecesor[i] = 0;
        }
        Lista[s] = 1;
        for(int i = 1; i<nrNodes; i++)
        {
            Lista[s] = 0;
        }

        while(!queueV.empty())
        {

        }
    }
};

#endif // GRAPH_H
