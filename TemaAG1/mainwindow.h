#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void mouseReleaseEvent(QMouseEvent* ev);
    void paintEvent(QPaintEvent* p);
    void Arrow(QPointF start, QPointF end, QPainter& painter);
    void mouseMoveEvent(QMouseEvent *event);
    ~MainWindow();

private slots:
    void on_radioButton_released();

private:

    Graph graph;
    Ui::MainWindow *ui;

    const int nodeRadius = 10;
    bool isFirstNode;
    Node firstNode;
};
#endif // MAINWINDOW_H
