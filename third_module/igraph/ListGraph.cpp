#include "ListGraph.hpp"

// Массив списков смежностей
ListGraph::ListGraph(const IGraph &graph) : adjacencyLists(graph.VerticesCount())
{
    int size = graph.VerticesCount();
    for (int i = 0; i < size; ++i)
    {
        Rebro *head = nullptr;
        Rebro *curr = nullptr;
        std::vector<int> elements = graph.GetNextVertices(i);
        int size_elem = elements.size();
        for (int j = 0; j < size_elem; ++j)
        {
            Rebro *newElement = new Rebro(elements[j]);
            if (!head)
            {
                // Если head еще не инициализирован, устанавливаем его на новый элемент
                head = newElement;
                curr = head;
            }
            else
            {
                // Иначе добавляем новый элемент в конец списка
                curr->next = newElement;
                curr = curr->next;
            }
        }
        adjacencyLists[i] = head;
    }
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const
{
    assert(0 <= vertex && vertex < adjacencyLists.size());
    std::vector<int> result;
    Rebro *curr = adjacencyLists[vertex];
    while (curr)
    {
        result.push_back(curr->index);
        curr = curr->next;
    }
    return result;
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const
{
    assert(0 <= vertex && vertex < adjacencyLists.size());
    std::vector<int> prevVertices;

    for (int from = 0; from < adjacencyLists.size(); from++)
    {
        Rebro *curr = adjacencyLists[from];
        while (curr)
        {
            if (curr->index == vertex)
            {
                prevVertices.push_back(from);
            }
            curr = curr->next;
        }
    }
    return prevVertices;
}

void ListGraph::AddEdge(int from, int to)
{
    assert(0 <= from && from < adjacencyLists.size());
    assert(0 <= to && to < adjacencyLists.size());
    Rebro *curr = adjacencyLists[from];
    Rebro *parent = curr;
    while (curr)
    {
        parent = curr;
        curr = curr->next;
    }
    curr = new Rebro(to);
    if (adjacencyLists[from] != nullptr)
    {
        parent->next = curr;
    }
    else
    {
        adjacencyLists[from] = curr;
    }
}