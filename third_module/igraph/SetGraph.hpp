#pragma once
#include "IGraph.hpp"
#include "avl.hpp"

// Массив сбалансированных деревьев
class SetGraph : public IGraph
{
public:
    SetGraph(int size)
        : adjacencyLists(size)
    {
    }

    SetGraph(const IGraph &graph);

    ~SetGraph(){};

    void AddEdge(int from, int to) override;

    int VerticesCount() const override
    {
        return static_cast<int>(adjacencyLists.size());
    }

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<AVLTree<int, int> *> adjacencyLists; // поменять
};