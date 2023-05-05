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
    graph.ReadFromLabirint();
    graph.CreateGraph();
    //graph.getEdges();
    graph.Parcurgere();

}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    vector<Node> nodes = graph.getNodes();
    vector<vector<int>> Labirint = graph.getLabirint();
    for(Node& n:nodes)
    {
        QPointF coord = n.getCoordinate();
        QRect r(coord.x() - nodeRadius, coord.y()- nodeRadius,
                2*nodeRadius, 2*nodeRadius);
        QPen pen;
        if(n.getInfo() == 0)
        {
            pen.setColor(Qt::black);
            p.setPen(pen);
            p.drawPolygon(r);
        }
        if(n.getInfo() == 1)
        {
            pen.setColor(Qt::darkGray);
            p.setPen(pen);
            p.drawPolygon(r);
            update();
        }
        if(n.getInfo() == 2)
        {
            pen.setColor(Qt::red);
            p.setPen(pen);
            p.drawPolygon(r);
            update();
        }
        if(n.getInfo() == 3)
        {
            pen.setColor(Qt::blue);
            p.setPen(pen);
            p.drawPolygon(r);
            update();
        }
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

