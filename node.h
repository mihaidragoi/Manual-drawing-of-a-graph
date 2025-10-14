#ifndef NODE_H
#define NODE_H
#include <QPoint>

class Node
{
protected:
    int m_index;
    QPoint m_coord;
public:
    Node(int index=0, QPoint p=QPoint(0,0));
    int getIndex();
    QPoint getCoord();
    void setIndex(int index);
    void setCoord(QPoint p);
    int getX();
    int getY();
};

#endif // NODE_H
