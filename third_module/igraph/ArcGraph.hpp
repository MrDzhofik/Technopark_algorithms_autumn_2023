#pragma once
#include "IGraph.hpp"
#include <utility>

class ArcGraph : public IGraph
{
public:
    ArcGraph(int size)
        : adjacencyLists(size)
    {
    }

    ArcGraph(const IGraph &graph);

    ~ArcGraph(){};

    void AddEdge(int from, int to) override;

    int VerticesCount() const override
    {
        return static_cast<int>(adjacencyLists.size());
    }

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::pair<int, int>> adjacencyLists;
};