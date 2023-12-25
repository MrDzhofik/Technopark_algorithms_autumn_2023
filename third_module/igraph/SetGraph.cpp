#include "SetGraph.hpp"

SetGraph::SetGraph(const IGraph &graph)
    : adjacencyLists(graph.VerticesCount())
{
    for (int i = 0; i < graph.VerticesCount(); i++)
    {
        std::vector<int> elems = graph.GetNextVertices(i);
        int size = elems.size();
        for (int j = 0; j < size; ++j)
        {
            adjacencyLists[i]->insert(elems[j], elems[j]);
        }
    }
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const
{
    assert(0 <= vertex && vertex < adjacencyLists.size());
    std::vector<int> result;
    result = adjacencyLists[vertex]->biuld_array_from_root(result);
    return result;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const
{
    assert(0 <= vertex && vertex < adjacencyLists.size());
    std::vector<int> prevVertices;

    for (int from = 0; from < adjacencyLists.size(); from++)
    {
        std::vector<int> result;
        result = adjacencyLists[from]->biuld_array_from_root(result);
        for (int j = 0; j < result.size(); ++j)
        {
            if (result[j] == vertex)
            {
                prevVertices.push_back(from);
            }
        }
    }
    return prevVertices;
}

void SetGraph::AddEdge(int from, int to)
{
    assert(0 <= from && from < adjacencyLists.size());
    assert(0 <= to && to < adjacencyLists.size());
    adjacencyLists[from]->insert(to, to);
}
