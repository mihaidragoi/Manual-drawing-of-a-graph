#include "node.h"

Node::Node(int index, QPoint p):m_index(index), m_coord(p)
{}

int Node::getIndex()
{
    return m_index;
}

QPoint Node::getCoord()
{
    return m_coord;
}

void Node::setIndex(int index)
{
    m_index=index;
}

void Node::setCoord(QPoint p)
{
    m_coord=p;
}

int Node::getX()
{
    return m_coord.x();
}

int Node::getY()
{
    return m_coord.y();
}
