#ifndef EDGE_H
#define EDGE_H
#include "node.h"

class Edge
{
protected:
    Node* m_first;
    Node* m_second;


public:
    Edge();
    Edge(Node* f, Node* s);
    Node* getFirst();
    Node* getSecond();
    void setFirst(Node *f);
    void setSecond(Node *s);
};


#endif // EDGE_H
