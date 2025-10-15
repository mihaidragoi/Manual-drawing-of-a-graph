#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qpainter.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *m)
{
    if(m->button() == Qt::RightButton){
        m_graph.addNode(m->pos());
        update();
    }
    else if (m->button() == Qt::LeftButton){
        Node* nodes = m_graph.getNodes();
        int numberNodes = m_graph.getNumberNodes();
        Node selected;
        for(int i=0;i<numberNodes;i++){
            if(abs(m->pos().x()-nodes[i].getX()) < 10 && abs(m->pos().y()-nodes[i].getY()) < 10){
                selected = nodes[i];
                break;
            }
        }
        if(selected.getIndex()!=0){
            if(m_firstNode.getIndex() == 0)
                m_firstNode = selected;
            else{
                m_graph.addEgde(m_firstNode, selected);
                m_firstNode.setIndex(0);
                update();
            }
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    Node* nodes= m_graph.getNodes();
    int numberNodes=m_graph.getNumberNodes();
    for(int i=0;i<numberNodes;i++){
        QRect r(nodes[i].getX()-10, nodes[i].getY()-10, 20, 20);
        p.drawEllipse(r);
        QString s=QString::number(nodes[i].getIndex());
        p.drawText(r, Qt::AlignCenter, s);
    }
    Edge* edges = m_graph.getEdges();
    int numberEdges=m_graph.getNumberEdges();
    for(int i=0;i<numberEdges;i++){
        Node *first=edges[i].getFirst();
        Node *second=edges[i].getSecond();
        p.drawLine(first->getX(), first->getY(), second->getX(), second->getY());
    }
}
