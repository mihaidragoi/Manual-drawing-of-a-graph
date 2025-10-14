#include "edge.h"

Edge::Edge():m_first(nullptr), m_second(nullptr) {}

Edge::Edge(Node *f, Node *s):m_first(f), m_second(s)
{}

Node *Edge::getFirst()
{
    return m_first;
}

Node *Edge::getSecond()
{
    return m_second;
}

void Edge::setFirst(Node *f)
{
    m_first=f;
}

void Edge::setSecond(Node *s)
{
    m_second=s;
}
