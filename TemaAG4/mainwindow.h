#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog.h"
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
    ~MainWindow();

private slots:
    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:

    Graph graph;
    Ui::MainWindow *ui;
    Dialog *dialog;

    const int nodeRadius = 10;
    bool isFirstNode;
    Node firstNode;
};
#endif // MAINWINDOW_H
