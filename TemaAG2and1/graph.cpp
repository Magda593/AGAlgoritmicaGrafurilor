#include "graph.h"
#include<random>

Graph::Graph()
{
    eOrientat = true;
}

void Graph::generatePath()
{
    int s = 0;
    int t = nrNodes - 1;
    vector<bool> pathNode;
    for(int i=0; i<nrNodes; i++)
    {
        pathNode.push_back(false);
    }
    pathNode[s] = true;
    int u = s;
    int v;
    for(int j= 1; j<nrNodes;j++)
    {
        random_device rd;
        mt19937 eng(rd());
        uniform_int_distribution<> distr(0, nrNodes - j - 1);
        int k= distr(eng);
        int l=0;
        for(v=0; v<nrNodes; v++)
        {
            if(pathNode[v])
                continue;
            if(l==k)
                break;
            l=l+1;
        }
        Edge e(nodes[u], nodes[v]);
        addEdge(e);
        //edges.push_back(e);
        Matrice[u][v] = 1;
        pathNode[v] = true;
        if (v==t)
            break;
        u=v;
    }
    qDebug()<<"Path:";
    for(Edge a: edges)
    {
        qDebug() << a.getFirstNode().getInfo() << " "<<a.getSecondNode().getInfo();
    }
}

void Graph::generateCycle()
{
    vector<bool> cycleNode;
    random_device rd;
    mt19937 eng(rd());
    uniform_int_distribution<> distr(0, nrNodes - 1);
    int u0 = distr(eng);
    for(int i=0; i<nrNodes; i++)
    {
        cycleNode.push_back(false);
    }
    int u = u0;
    int v;
    for(int j= 0; j<nrNodes;j++)
    {
        random_device rd;
        mt19937 eng(rd());
        uniform_int_distribution<> distr(0, nrNodes - j - 1);
        int k = distr(eng);
        int l =0;
        for(v=0; v<nrNodes; v++)
        {
            if(cycleNode[v])
                continue;
            if(l==k)
                break;
            l=l+1;
        }
        if(u==v)
        {
            j=j-1;
        }
        else
        {
            Edge e(nodes[u], nodes[v]);
            //addEdge(e);
            edges.push_back(e);
            Matrice[u][v] = 1;
            cycleNode[v] = true;
        }

        if (v==u0)
            break;
        u=v;
    }
    qDebug()<<"Cycle:";
    for(Edge a: edges)
    {
        qDebug() << a.getFirstNode().getInfo() << " "<<a.getSecondNode().getInfo();
    }
}

void Graph::MatriceInLista()
{
    listaAdiacenta.clear();
    for(int i = 0; i < (int)Matrice.size(); i++)
    {
        vector<int> ListaAdiacentaNodCurent;
        for(int j = 0; j < (int)Matrice.size(); j++)
        {
            if(Matrice[i][j] == 1)
            {
                ListaAdiacentaNodCurent.push_back(j);
            }
        }
        listaAdiacenta.push_back(ListaAdiacentaNodCurent);
    }

}
