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
    void mousePressEvent(QMouseEvent *m) override;
    void mouseMoveEvent(QMouseEvent *m) override;

private slots:
    void on_checkBox_checkStateChanged(const Qt::CheckState &arg1);

private:
    Ui::MainWindow *ui;
    Graph m_graph;
    Node m_firstNode;
    bool m_dragged=false;
    Node* m_draggedNode=nullptr;
};
#endif // MAINWINDOW_H
