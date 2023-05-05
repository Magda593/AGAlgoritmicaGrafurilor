#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "graph.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* p);
    void Arrow(QPointF start, QPointF end, QPainter& painter);
    void SetGrafSortat(Graph grafSortat);

    ~Dialog();

private:
    Ui::Dialog *ui;
    Graph graph;
    Graph grafSortat;
    const int nodeRadius = 10;
};

#endif // DIALOG_H
