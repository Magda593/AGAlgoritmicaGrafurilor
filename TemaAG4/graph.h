#ifndef GRAPH_H
#define GRAPH_H
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "edge.h"
#include <vector>
#include <stack>

using namespace std;
class Graph
{
    vector<Node> nodes;
    vector<Edge> edges;
    vector<Edge> MuchiiSortate;
    vector<vector<int>> Matrice;
    vector<vector<int>> Lista;
    vector<int> SortareaTopologica;
    bool hasCycles;
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
    vector<Edge> getEdgesSorted(){return MuchiiSortate;}
    bool getEOrientat() {return eOrientat;}
    bool getHasCycles() {return hasCycles;}
    void setNodes(vector<Node> nodes) {this->nodes = nodes;}
    void setEdges(vector<Edge> edges) {this->edges = edges;}
    void setEOrientat(bool eOrientat){this->eOrientat = eOrientat;}
    vector<vector<int>> getMatrice() {return Matrice;}

    void ReadLista()
    {
        QString filename = "C:\\Users\\Magda\\Documents\\TemaAG4\\Lista.txt";
        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly))
        {
             qDebug() << "Error opening file: " << file.error();
             return;
        }
        QTextStream instream(&file);

        for(int i = 0; i < 8; i++)
        {
            vector<int> ListaCurenta;
            for(int j = 0; j < 8; j++)
            {
               int value;
               instream >> value;
               ListaCurenta.push_back(value);
            }
            Lista.push_back(ListaCurenta);
         }
    }

    void PrintMatrice()
    {
        QString filename = "C:\\Users\\Magda\\Documents\\TemaAG4\\Matrice.txt";
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

    void PrintSortareTopologica()
    {
        QString filename = "C:\\Users\\Magda\\Documents\\TemaAG4\\SortareText.txt";
            QFile file(filename);
            if (file.open(QIODevice::ReadWrite))
            {
                file.resize(0);
                QTextStream stream(&file);
                int numberOfNodes = (int)nodes.size();
                for(int i = 0; i < numberOfNodes; i++)
                {
                    stream << SortareaTopologica[i];
                }
                stream.flush();
                file.close();
            }
            else
            {
                qDebug() << "Couldn't open file";
            }
    }

    void DFS()
    {
        int numberOfNodes = (int)nodes.size();
        Node s = nodes[0];
        vector<Node> u = nodes;
        u.erase(u.begin());
        stack<Node> v;
        v.push(s);
        vector<Node> w;
        vector<int> predecesor;
        vector<int> t1(numberOfNodes);
        vector<int> t2(numberOfNodes);

        for(int i = 0;i<numberOfNodes;i++)
        {
            predecesor.push_back(0);
        }
        int t = 1;
        t1[s.getInfo()-1] = 1;
        t2[s.getInfo()-1] = 999999999;

        for(int i = 0; i<(int)u.size();i++)
        {
            t1[i] = 999999999;
            t2[i] = 999999999;
        }

        while(w.size() != nodes.size())
        {
            while(!v.empty())
            {
                Node x = v.top();
                bool ok = 0;
                for(int j=0;j<(int)edges.size();j++)
                {
                    if(edges[j].getFirstNode().getInfo()-1 == x.getInfo()-1)
                    {

                        for(int i = 0; i< (int)u.size();i++)
                        {
                            if(edges[j].getSecondNode().getInfo()-1 == u[i].getInfo()-1)
                            {
                                ok = 1;
                                v.push(u[i]);
                                u.erase(u.begin() + i);
                                predecesor[u[i].getInfo() - 1] = x.getInfo() - 1;
                                t=t+1;
                                t1[u[i].getInfo() - 1] = t;
                            }
                        }

                    }
                }
                if(ok==0)
                {
                    v.pop();
                    w.push_back(x);
                    t=t+1;
                    t2[x.getInfo() - 1] = t;
                }
            }
            if(u.size()!=0)
            {
                s=u[0];
                u.erase(u.begin());
                v.push(s);
                t=t+1;
                t1[s.getInfo() - 1] = t;
            }
        }
        hasCycles = false;
        for(int i = 0; i < (int)edges.size(); i++)
            {
                if(t1[edges[i].getSecondNode().getInfo()-1] < t1[edges[i].getFirstNode().getInfo()-1]
                        && t1[edges[i].getFirstNode().getInfo()-1]  < t2[edges[i].getFirstNode().getInfo()-1]
                        && t2[edges[i].getFirstNode().getInfo()-1] < t2[edges[i].getSecondNode().getInfo()-1])
                {
                    hasCycles = true;
                }
            }
        for(int i = 0; i < (int)w.size();i++)
        {
            qDebug() << w[i].getInfo();
        }
    }

    bool ExistsSortedEdgeForxNode(Node x)
    {
        for (int i = 0; i < (int)MuchiiSortate.size(); i++)
        {
            if(MuchiiSortate[i].getSecondNode().getInfo() == x.getInfo())
            {
                return true;
            }
        }
        return false;
    }

    void SortareTopologica()
    {
       list<Node> Sortate;
       int numberOfNodes = (int)nodes.size();
       Node s = nodes[0];
       vector<Node> u = nodes;
       u.erase(u.begin());
       stack<Node> v;
       v.push(s);
       vector<Node> w;
       vector<int> predecesor;
       vector<int> t1(numberOfNodes);
       vector<int> t2(numberOfNodes);

       for(int i = 0;i<numberOfNodes;i++)
       {
           predecesor.push_back(0);
       }
       int t = 1;
       t1[s.getInfo()-1] = 1;
       t2[s.getInfo()-1] = 999999999;

       for(int i = 0; i<(int)u.size();i++)
       {
           t1[i] = 999999999;
           t2[i] = 999999999;
       }

       while(w.size() != nodes.size())
       {
           while(!v.empty())
           {
               Node x = v.top();
               bool ok = 0;
               for(int j=0;j<(int)edges.size();j++)
               {
                   if(edges[j].getFirstNode().getInfo()-1 == x.getInfo()-1)
                   {

                       for(int i = 0; i< (int)u.size();i++)
                       {
                           if(edges[j].getSecondNode().getInfo()-1 == u[i].getInfo()-1)
                           {
                               ok = 1;
                               v.push(u[i]);
                               u.erase(u.begin() + i);
                               predecesor[u[i].getInfo() - 1] = x.getInfo() - 1;
                               t=t+1;
                               t1[u[i].getInfo() - 1] = t;
                           }
                       }
                   }
               }
               if(ok==0)
               {
                   v.pop();
                   w.push_back(x);
                   t=t+1;
                   t2[x.getInfo() - 1] = t;
                   Sortate.push_front(x);
               }
           }
           if(u.size()!=0)
           {
               s=u[0];
               u.erase(u.begin());
               v.push(s);
               t=t+1;
               t1[s.getInfo() - 1] = t;
           }
       }

       QString filename = "C:\\Users\\Magda\\Documents\\TemaAG4\\SortareText.txt";
           QFile file(filename);
           if (file.open(QIODevice::ReadWrite))
           {
               file.resize(0);
               QTextStream stream(&file);
               for(Node n : Sortate)
               {
                   stream << n.getInfo() << " ";
               }
               stream.flush();
               file.close();
           }
           else
           {
               qDebug() << "Couldn't open file";
           }
           for(Node n : Sortate)
           {
               for(Node b : Sortate)
               {
                   if(Matrice[n.getInfo()-1][b.getInfo()-1] == 1 && ExistsSortedEdgeForxNode(b) == false)
                   {
                       MuchiiSortate.push_back(Edge(n,b));
                       //qDebug() << "ar";
                   }
               }
           }
    }

    int Conexe()
    {
       Node s = nodes[0];
       vector<Node> u = nodes;
       u.erase(u.begin());
       stack<Node> v;
       v.push(s);
       vector<Node> w;
       vector<Node> nprim;
       int nrComponenteConexe = 1;
       nprim.push_back(s);

       while(w.size() != nodes.size())
       {
           while(!v.empty())
           {
               Node x = v.top();
               bool ok = 0;
               for(int j=0;j<(int)edges.size();j++)
               {
                   if(edges[j].getFirstNode().getInfo()-1 == x.getInfo()-1)
                   {

                       for(int i = 0; i< (int)u.size();i++)
                       {
                           if(edges[j].getSecondNode().getInfo()-1 == u[i].getInfo()-1)
                           {
                               ok = 1;
                               v.push(u[i]);
                               nprim.push_back(u[i]);
                               u.erase(u.begin() + i);
                           }
                       }
                   }
               }
               if(ok==0)
               {
                   v.pop();
                   w.push_back(x);
               }
           }
           if(u.size()!=0)
           {
               s=u[0];
               nrComponenteConexe++;
               nprim.push_back(s);
               u.erase(u.begin());
               v.push(s);
           }
       }
       return nrComponenteConexe;
    }
};

#endif // GRAPH_H
