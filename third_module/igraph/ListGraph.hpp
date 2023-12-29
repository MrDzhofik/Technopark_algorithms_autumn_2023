#pragma once
#include "IGraph.hpp"

struct Rebro
{
    int index;
    Rebro *next;

    Rebro() : next(nullptr) {}
    Rebro(int number) : index(number), next(nullptr){};
};

// Массив списков смежностей
class ListGraph : public IGraph
{
public:
    ListGraph(int size)
        : adjacencyLists(size)
    {
    }

    ListGraph(const IGraph &graph);

    ~ListGraph();

    void AddEdge(int from, int to) override;

    int VerticesCount() const override
    {
        return static_cast<int>(adjacencyLists.size());
    }

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<Rebro *> adjacencyLists;
};
