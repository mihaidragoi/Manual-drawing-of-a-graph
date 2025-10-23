#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qpainter.h>
#include <QPainter>
#include <cmath>
#include <QPoint>

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
    if(m->button() == Qt::RightButton)
    {
        if(m_dragged)
        {
            m_dragged=false;
            m_draggedNode=nullptr;
        }
        else
        {
            m_graph.addNode(m->pos());
            m_firstNode.setIndex(0);
            m_firstNode.setCoord(QPoint(0,0));
            update();
        }
        return;
    }
    else
        if (m->button() == Qt::LeftButton)
    {
        if(m_dragged)
        {
            m_dragged = false;
            m_draggedNode = nullptr;
            return;
        }

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
            else
            {
                if(m_firstNode.getIndex()!=selected.getIndex())
                    m_graph.addEgde(m_firstNode, selected);

                m_firstNode.setIndex(0);
                m_firstNode.setCoord(QPoint(0,0));
                update();
            }
        }
        return;
    }
    m_firstNode.setIndex(0);
    m_firstNode.setCoord(QPoint(0,0));
}

void MainWindow::paintEvent(QPaintEvent *e)
{

    QPainter p(this);

    Node* nodes= m_graph.getNodes();
    int numberNodes=m_graph.getNumberNodes();
    int radius = 10;
    for(int i=0;i<numberNodes;i++){
        QRect r(nodes[i].getX()-radius, nodes[i].getY()-radius, 2*radius, 2*radius);
        p.drawEllipse(r);
        QString s=QString::number(nodes[i].getIndex());
        p.drawText(r, Qt::AlignCenter, s);
    }

    Edge* edges = m_graph.getEdges();
    int numberEdges=m_graph.getNumberEdges();
    for(int i=0;i<numberEdges;i++)
    {
        Node *first=edges[i].getFirst();
        Node *second=edges[i].getSecond();
        int distanceX=second->getX()-first->getX();
        int distanceY=second->getY()-first->getY();
        double angle=atan2(distanceY, distanceX);
        p.drawLine(first->getX()+radius*cos(angle), first->getY()+radius*sin(angle), second->getX()-radius*cos(angle), second->getY()-radius*sin(angle));

        if(m_graph.getOriented()==true)
        {
            int arrowSize=10;
            QPointF arrowEnd(second->getX()- radius * cos(angle), second->getY()- radius * sin(angle));

            QPointF arrow1 = arrowEnd - QPointF(arrowSize * cos(angle - M_PI / 6), arrowSize * sin(angle - M_PI / 6));
            QPointF arrow2 = arrowEnd - QPointF(arrowSize * cos(angle + M_PI / 6), arrowSize * sin(angle + M_PI / 6));

            p.drawLine(arrowEnd, arrow1);
            p.drawLine(arrowEnd, arrow2);
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *m)
{
    if(m->button()==Qt::RightButton)
    {
        Node *nodes=m_graph.getNodes();
        int numberNodes=m_graph.getNumberNodes();
        for(int i=0;i<numberNodes;i++)
        {
            if(abs(m->pos().x()-nodes[i].getX())<10 && abs(m->pos().y()-nodes[i].getY())<10)
            {
                m_dragged=true;
                m_draggedNode=&nodes[i];
                return;
            }
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *m)
{
    if(m_dragged && m_draggedNode!=nullptr)
    {
        QPoint newPosition=m->pos();
        Node* nodes=m_graph.getNodes();
        int ok=0;
        int numberNodes=m_graph.getNumberNodes();
        for(int i=0;i<numberNodes;i++)
        {
            if(&nodes[i]==m_draggedNode)
                continue;
            int distanceX=newPosition.x()-nodes[i].getX();
            int distanceY=newPosition.y()-nodes[i].getY();
            int distance=std::sqrt(distanceX*distanceX+distanceY*distanceY);
            if(distance<20)
            {
                ok=1;
                break;
            }
        }
        if(!ok)
        {
            m_draggedNode->setCoord(m->pos());
            update();
        }
    }
}



void MainWindow::on_checkBox_checkStateChanged(const Qt::CheckState &arg1)
{
    m_graph.setOriented(!m_graph.getOriented());
    m_graph.rebuildMatrix();
    m_graph.AdjustMatrix(m_graph.getMatrix(), "Matrix.txt");
    update();
}

