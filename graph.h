#ifndef GRAPH_H
#define GRAPH_H
#include "node.h"
#include "edge.h"

class Graph
{
protected:
    Node* m_nodes;
    int m_numberNodes;
    Edge* m_edges;
    int m_numberEdges;
    int **matrix;
    bool m_oriented;


public:
    Graph();
    ~Graph();

    void addNode(QPoint p);
    void addEgde(Node f, Node s);
    Node* getNodes();
    Edge* getEdges();
    void AdjustMatrix(int **matrix, QString filename);
    void setOriented(bool value);
    bool getOriented();
};

#endif // GRAPH_H
