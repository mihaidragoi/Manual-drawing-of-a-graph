#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>

#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void mouseReleaseEvent(QMouseEvent *m) override;
    void paintEvent(QPaintEvent *e) override;

private:
    Ui::MainWindow *ui;
    Graph m_graph;
    Node m_firstNode;
};
#endif // MAINWINDOW_H
