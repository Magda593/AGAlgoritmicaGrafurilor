#ifndef GRAPH_H
#define GRAPH_H
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "edge.h"
#include <vector>
#include <random>

using namespace std;
class Graph
{
    vector<Node> nodes;
    vector<Edge> edges;
    vector<vector<int>> Matrice;
    vector<vector<int>> listaAdiacenta;
    bool eOrientat;
    const int nrNodes = 10;
    const int nrPaths = 1;
    const int nrCycles = 0;
public:
    Graph();
    int getNrPaths()
    {
        return nrPaths;
    }
    int getNrCycles()
    {
        return nrCycles;
    }
    void generatePath();
    void generateCycle();
    void MatriceInLista();
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

    bool seSuprapun(Node a)
    {
        bool ok = false;
               for(Node n : nodes)
                {
                    QPointF coord = n.getCoordinate();
                    float dist = sqrt((a.getCoordinate().x() - coord.x())*(a.getCoordinate().x() - coord.x())+
                                      (a.getCoordinate().y() - coord.y())*(a.getCoordinate().y() - coord.y()));
                    if(dist < 2 * 10)
                       {
                         ok=true;
                         break;
                        }
                }
         return ok;
    }
    void createNodes()
    {

        for(int i=0;i<nrNodes;i++)
        {
            random_device rd;
            mt19937 eng(rd());
            uniform_int_distribution<> distr(10, 700);
            int x = distr(eng);
            random_device rd1;
            mt19937 eng1(rd1());
            uniform_int_distribution<> distr1(10, 550);
            int y = distr1(eng1);
            QPointF coord(x,y);
            Node n = Node(coord,i+1);
            while(seSuprapun(n))
            {
                random_device rd;
                mt19937 eng(rd());
                uniform_int_distribution<> distr(10, 700);
                x = distr(eng);
                random_device rd1;
                mt19937 eng1(rd1());
                uniform_int_distribution<> distr1(10, 550);
                y = distr1(eng1);
                n.setCoord(QPointF(x,y));
            }
            QPointF coord1(x,y);
            addNode(Node(coord1,i+1));

        }
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
        QString filename = "C:\\Users\\Magda\\Documents\\TemaAG2and1\\Matrice.txt";
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
    void printLista()
    {
        QString filename = "C:\\Users\\Magda\\Documents\\TemaAG2and1\\Lista.txt";
        QFile file(filename);
        if (file.open(QIODevice::ReadWrite))
        {
            file.resize(0);
            QTextStream stream(&file);

            stream << nrNodes << "\n";

            for(int i = 0; i < listaAdiacenta.size(); i++)
            {
                stream << i+1 << " : ";
                for(int j = 0; j < listaAdiacenta[i].size(); j++)
                {
                   stream << listaAdiacenta[i][j] << " ";
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
