#include "ArcGraph.hpp"

ArcGraph::ArcGraph(const IGraph &graph)
{
    for (int i = 0; i < graph.VerticesCount(); ++i)
    {
        std::vector<int> elems = graph.GetNextVertices(i);
        int from = i;
        int size = elems.size();
        for (int j = 0; j < size; ++j)
        {
            std::pair<int, int> tmp;
            tmp.first = from;
            tmp.second = elems[j];
            adjacencyLists.push_back(tmp);
        }
    }
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const
{
    assert(0 <= vertex && vertex < adjacencyLists.size());
    std::vector<int> result;
    for (int i = 0; i < adjacencyLists.size(); ++i)
    {
        if (adjacencyLists[i].first == vertex)
        {
            result.push_back(adjacencyLists[i].second);
        }
    }
    return result;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const
{
    assert(0 <= vertex && vertex < adjacencyLists.size());
    std::vector<int> prevVertices;

    for (int i = 0; i < adjacencyLists.size(); ++i)
    {
        if (adjacencyLists[i].second == vertex)
        {
            prevVertices.push_back(adjacencyLists[i].first);
        }
    }
    return prevVertices;
}

void ArcGraph::AddEdge(int from, int to)
{
    assert(0 <= from && from < adjacencyLists.size());
    assert(0 <= to && to < adjacencyLists.size());
    std::pair<int, int> tmp;
    tmp.first = from;
    tmp.second = to;
    adjacencyLists.push_back(tmp);
}
