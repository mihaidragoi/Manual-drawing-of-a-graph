#include "graph.h"
#include <QString>
#include <QFile>
#include <QTextStream>

Graph::Graph(): m_nodes(nullptr), m_edges(nullptr), matrix(nullptr), m_numberNodes(0),
    m_numberEdges(0), m_oriented(false){
}

Graph::~Graph()
{
    delete []m_nodes;
    delete []m_edges;

    for(int i=0;i<m_numberNodes;i++)
        delete []matrix[i];
    delete []matrix;
}

void Graph::addNode(QPoint p)
{
    int ok = 0;
    for (int i = 0; i < m_numberNodes; i++)
        if (m_nodes[i].getCoord() == p ||
            (abs(m_nodes[i].getX() - p.x()) < 20 && abs(m_nodes[i].getY() - p.y()) < 20))
            ok = 1;

    if (ok == 0)
    {
        int* idx1 = new int[m_numberEdges];
        int* idx2 = new int[m_numberEdges];
        for (int i = 0; i < m_numberEdges; i++)
        {
            idx1[i] = m_edges[i].getFirst()->getIndex() - 1;
            idx2[i] = m_edges[i].getSecond()->getIndex() - 1;
        }

        Node* aux = new Node[m_numberNodes + 1];
        for (int i = 0; i < m_numberNodes; i++)
            aux[i] = m_nodes[i];
        aux[m_numberNodes].setIndex(m_numberNodes + 1);
        aux[m_numberNodes].setCoord(p);
        delete [] m_nodes;
        m_nodes = aux;
        m_numberNodes++;

        for (int i = 0; i < m_numberEdges; i++)
        {
            m_edges[i].setFirst(&m_nodes[idx1[i]]);
            m_edges[i].setSecond(&m_nodes[idx2[i]]);
        }
        delete [] idx1;
        delete [] idx2;

        int** auxMatrix = new int*[m_numberNodes];
        for (int i = 0; i < m_numberNodes; i++)
            auxMatrix[i] = new int[m_numberNodes];

        if (matrix == nullptr)
        {
            for (int i = 0; i < m_numberNodes; i++)
                for (int j = 0; j < m_numberNodes; j++)
                    auxMatrix[i][j] = 0;
        }
        else
        {
            for (int i = 0; i < m_numberNodes - 1; i++)
                for (int j = 0; j < m_numberNodes - 1; j++)
                    auxMatrix[i][j] = matrix[i][j];

            for (int i = 0; i < m_numberNodes; i++)
            {
                auxMatrix[i][m_numberNodes - 1] = 0;
                auxMatrix[m_numberNodes - 1][i] = 0;
            }

            for (int i = 0; i < m_numberNodes - 1; i++)
                delete [] matrix[i];
            delete [] matrix;
        }

        matrix = auxMatrix;

        AdjustMatrix(matrix, "Matrix.txt");
    }
}


void Graph::addEgde(Node f, Node s)
{
    Node *first=&m_nodes[f.getIndex()-1];
    Node *second=&m_nodes[s.getIndex()-1];
    int ok=0;
    for(int i=0;i<m_numberEdges;i++)
    {
        if(m_edges[i].getFirst()==first && m_edges[i].getSecond()==second)
        {
            ok=1;
            break;
        }
    }
    if(ok==0)
    {
        Edge e(first, second);
        Edge* rez= new Edge[m_numberEdges+1];
        for(int i=0;i<m_numberEdges;i++)
            rez[i]=m_edges[i];
        rez[m_numberEdges].setFirst(first);
        rez[m_numberEdges].setSecond(second);
        delete[] m_edges;
        m_edges=rez;
        m_numberEdges++;
        
        int i=first->getIndex()-1;
        int j=second->getIndex()-1;
        matrix[i][j]=1;
        if(!m_oriented)
            matrix[j][i]=1;
        AdjustMatrix(matrix, "Matrix.txt");
    }
}

Node *Graph::getNodes()
{
    return m_nodes;
}

Edge *Graph::getEdges()
{
    return m_edges;
}  

void Graph::AdjustMatrix(int **matrix, QString filename)
{
    QFile fin(filename);
    if(!fin.open(QIODeviceBase::WriteOnly|QIODeviceBase::Text))
        throw std::runtime_error("Cannot opne the file! Please try again later");
    QTextStream out(&fin);
    out<<m_numberNodes<<"\n";
    for(int i=0;i<m_numberNodes;i++)
    {
        for(int j=0;j<m_numberNodes;j++)
            out<<matrix[i][j]<<" ";
        out<<"\n";
    }
}

void Graph::setOriented(bool value)
{
    m_oriented=value;
}

bool Graph::getOriented()
{
    return m_oriented;
}

int Graph::getNumberNodes()
{
    return m_numberNodes;
}

int Graph::getNumberEdges()
{
    return m_numberEdges;
}
