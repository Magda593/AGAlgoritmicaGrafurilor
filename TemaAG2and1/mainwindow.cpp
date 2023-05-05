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
    graph.createNodes();
    for(int i = 0; i<graph.getNrPaths();i++)
    {
        graph.generatePath();
        qDebug() << '\n';
    }
    for(int i = 0; i<graph.getNrCycles();i++)
    {
        graph.generateCycle();
        qDebug() << '\n';
    }
    graph.PrintMatrice();
    graph.MatriceInLista();
    graph.printLista();
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


MainWindow::~MainWindow()
{
    delete ui;
}




