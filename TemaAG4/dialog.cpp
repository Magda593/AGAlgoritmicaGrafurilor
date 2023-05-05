#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
#include <QMouseEvent>
#include <QPainter>
#include<QLineF>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    grafSortat.setEdges(graph.getEdgesSorted());
    grafSortat.setNodes(graph.getNodes());
}

void Dialog::SetGrafSortat(Graph grafSortat)
{
    this->grafSortat = grafSortat;
}

void Dialog::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    vector<Node> nodes = grafSortat.getNodes();
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
    vector<Edge> edges = grafSortat.getEdges();
    for(Edge& e:edges)
    {
        if(grafSortat.getEOrientat() == true)
        {
            Arrow(e.getFirstNode().getCoordinate(), e.getSecondNode().getCoordinate(), p);
        }
        else
        {
            p.drawLine(e.getFirstNode().getCoordinate(), e.getSecondNode().getCoordinate());
        }

    }

}

void Dialog::Arrow(QPointF start, QPointF end, QPainter& painter)
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

Dialog::~Dialog()
{
    delete ui;
}
