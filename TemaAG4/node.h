#ifndef NODE_H
#define NODE_H

#include <QPoint>
class Node
{
    int info;
    QPointF coord;
public:
    Node(int inf = -1);
    Node(QPointF cood, int inf = -1);
    void setInfo(int inf){info = inf;}
    void setCoord(QPointF coord) {this->coord = coord;}
    QPointF getCoordinate(){return coord;}
    int getInfo(){return info;}
};

#endif // NODE_H
