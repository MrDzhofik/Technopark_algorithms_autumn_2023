#pragma once
#include "IGraph.hpp"
#include <utility>
#include <vector>
#include <algorithm>

// Массив пар ребер
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
        int count = 0;
        std::vector<int> unique;
        int size = adjacencyLists.size();
        for (int i = 0; i < size; ++i)
        {
            if (std::count(unique.begin(), unique.end(), adjacencyLists[i].first) == 0)
            {
                unique.push_back(adjacencyLists[i].first);
            }
            if (std::count(unique.begin(), unique.end(), adjacencyLists[i].second) == 0)
            {
                unique.push_back(adjacencyLists[i].second);
            }
        }
        return static_cast<int>(unique.size());
    }

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::pair<int, int>> adjacencyLists;
};