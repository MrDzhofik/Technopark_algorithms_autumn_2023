#pragma once
#include "IGraph.hpp"

// Матрица смежности
class MatrixGraph : public IGraph
{
public:
    MatrixGraph(int size)
        : adjacencyLists(size)
    {
    }

    MatrixGraph(const IGraph &graph);

    ~MatrixGraph(){};

    void AddEdge(int from, int to) override;

    int VerticesCount() const override
    {
        return static_cast<int>(adjacencyLists.size());
    }

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<int>> adjacencyLists;
};