#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QPainter>
#include<QLineF>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    isFirstNode = false;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::RightButton)
    {
        Node n(ev->position());
        // verificare suprapunere noduri
        int ok = 1;
        vector<Node> nodes = graph.getNodes();
        for(Node n : nodes)
        {
            QPointF coord = n.getCoordinate();
            float dist = sqrt((ev->position().x() - coord.x())*(ev->position().x() - coord.x())+
                              (ev->position().y() - coord.y())*(ev->position().y() - coord.y()));
            if(dist < 2 * nodeRadius)
               {
                 ok=0;
                 break;
                }
        }
        if(ok==1)
        {
            n.setInfo(graph.getNumberOfNodes() + 1);
            graph.addNode(n);
            update();
        }

    }
    else if (ev->button() == Qt::LeftButton)
    {
        vector<Node> nodes = graph.getNodes();
        Node selected;
        bool ok = false;
        for(Node& n: nodes)
        {
            QPointF coord = n.getCoordinate();
            float dist = sqrt((ev->position().x() - coord.x())*(ev->position().x() - coord.x())+
                              (ev->position().y() - coord.y())*(ev->position().y() - coord.y()));

            if (dist <= nodeRadius)
            {
                selected = n;
                ok = true;
                break;
            }
        }

        if (ok)
        {
            if (!isFirstNode)
            {
                firstNode = selected;
                isFirstNode = true;
            }
            else
            {
                vector<vector<int>> Matrice = graph.getMatrice();
                if(Matrice[firstNode.getInfo()-1][selected.getInfo()-1]==0)
                {
                    graph.addEdge(Edge(firstNode, selected));
                    isFirstNode= false;
                    update();

                }

            }
        }
        else
        {
            isFirstNode = false;
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    vector<Node> nodes = graph.getNodes();
    for(Node& n:nodes)
    {
        QPointF coord = n.getCoordinate();
        QRect r(coord.x() - nodeRadius, coord.y()- nodeRadius,
                2*nodeRadius, 2*nodeRadius);
        QPen pen;
        pen.setColor(Qt::blue);
        p.setPen(pen);
        p.drawEllipse(r);
        QString num = QString::number(n.getInfo());
        p.drawText(r, Qt::AlignCenter, num);
    }
    vector<Edge> edges = graph.getEdges();
    for(Edge& e:edges)
    {
        if(graph.getEOrientat() == true)
        {
            Arrow(e.getFirstNode().getCoordinate(), e.getSecondNode().getCoordinate(), p);
        }
        else
        {
            p.drawLine(e.getFirstNode().getCoordinate(), e.getSecondNode().getCoordinate());
        }

    }

}

void MainWindow::Arrow(QPointF start, QPointF end, QPainter& painter)
{
    int arrowSize = 15;
    QLineF line(end, start);

    double angle = std::atan2(-line.dy(), line.dx());

    QPointF arrowP1 = line.p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                        cos(angle + M_PI / 3) * arrowSize);
    QPointF arrowP2 = line.p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                        cos(angle + M_PI - M_PI / 3) * arrowSize);
    painter.drawLine(line);
    painter.drawLine(line.p1(), arrowP2);
    painter.drawLine(line.p1(), arrowP1);
}

void MainWindow::mouseMoveEvent(QMouseEvent *ev)
{
    vector<Node> nodes = graph.getNodes();
    vector<Edge> edges = graph.getEdges();
    for (Node& n: nodes)
    {
        QPointF coord = n.getCoordinate();
        float dist = sqrt((ev->position().x() - coord.x())*(ev->position().x() - coord.x())+
                          (ev->position().y() - coord.y())*(ev->position().y() - coord.y()));
        if (dist <= nodeRadius)
        {
            n.setCoord(QPointF(ev->position().x(), ev->position().y()));
            graph.setNodes(nodes);
            for (Edge& e: edges)
            {
                if(e.getFirstNode().getInfo() == n.getInfo())
                {
                    e.setFirstNode(n);
                }
                if(e.getSecondNode().getInfo() == n.getInfo())
                {
                    e.setSecondNode(n);
                }
            }
            graph.setEdges(edges);
            update();
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_radioButton_released()
{
    vector<Edge> edges = graph.getEdges();
    if(graph.getEOrientat() == true)
    {
        graph.setEOrientat(false);
        for (Edge a: edges)
        {
            graph.addEdge(Edge(a.getSecondNode(), a.getFirstNode()));

        }
    }
    else
    {
        graph.setEOrientat(true);
        vector<vector<int>> Matrice = graph.getMatrice();
        int numberOfNodes = graph.getNumberOfNodes();
            for(int i = 0; i < numberOfNodes; i++)
            {
                for(int j = 0; j < numberOfNodes; j++)
                {
                    Matrice[i][j] = 0;
                }
            }

            for(Edge e : edges)
            {
                Matrice[e.getFirstNode().getInfo() - 1][e.getSecondNode().getInfo() - 1] = 1;
            }
            graph.PrintMatrice();
    }
    update();

}

