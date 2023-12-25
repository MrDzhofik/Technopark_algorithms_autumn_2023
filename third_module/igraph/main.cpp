#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include "IGraph.hpp"
#include "ListGraph.hpp"
#include "MatrixGraph.hpp"
#include "ArcGraph.hpp"
#include "SetGraph.hpp"
// #include <utility>

// struct IGraph
// {
//     virtual ~IGraph(){};

//     // Добавление ребра от from к to.
//     virtual void AddEdge(int from, int to) = 0;

//     virtual int VerticesCount() const = 0;

//     virtual std::vector<int> GetNextVertices(int vertex) const = 0;
//     virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
// };

// class ListGraph : public IGraph
// {
// public:
//     ListGraph(int size)
//         : adjacencyLists(size)
//     {
//     }

//     ListGraph(const IGraph &graph);

//     ~ListGraph(){};

//     void AddEdge(int from, int to) override;

//     int VerticesCount() const override
//     {
//         return static_cast<int>(adjacencyLists.size());
//     }

//     std::vector<int> GetNextVertices(int vertex) const override;

//     std::vector<int> GetPrevVertices(int vertex) const override;

// private:
//     std::vector<std::vector<int>> adjacencyLists;
// };

// ListGraph::ListGraph(const IGraph &graph)
//     : adjacencyLists(graph.VerticesCount())
// {
//     for (int i = 0; i < graph.VerticesCount(); i++)
//     {
//         adjacencyLists[i] = graph.GetNextVertices(i);
//     }
// }

// std::vector<int> ListGraph::GetNextVertices(int vertex) const
// {
//     assert(0 <= vertex && vertex < adjacencyLists.size());
//     return adjacencyLists[vertex];
// }

// std::vector<int> ListGraph::GetPrevVertices(int vertex) const
// {
//     assert(0 <= vertex && vertex < adjacencyLists.size());
//     std::vector<int> prevVertices;

//     for (int from = 0; from < adjacencyLists.size(); from++)
//     {
//         for (int to : adjacencyLists[from])
//         {
//             if (to == vertex)
//             {
//                 prevVertices.push_back(from);
//             }
//         }
//     }
//     return prevVertices;
// }

// void ListGraph::AddEdge(int from, int to)
// {
//     assert(0 <= from && from < adjacencyLists.size());
//     assert(0 <= to && to < adjacencyLists.size());
//     adjacencyLists[from].push_back(to);
// }

// struct Rebro
// {
//     int index;
//     Rebro *next;

//     Rebro() : next(nullptr) {}
//     Rebro(int number) : index(number), next(nullptr){};
// };

// // Массив списков смежностей
// class MatrixGraph : public IGraph
// {
// public:
//     MatrixGraph(int size)
//         : adjacencyLists(size)
//     {
//     }

//     MatrixGraph(const IGraph &graph);

//     ~MatrixGraph(){};

//     void AddEdge(int from, int to) override;

//     int VerticesCount() const override
//     {
//         return static_cast<int>(adjacencyLists.size());
//     }

//     std::vector<int> GetNextVertices(int vertex) const override;

//     std::vector<int> GetPrevVertices(int vertex) const override;

// private:
//     std::vector<Rebro *> adjacencyLists;
// };

// // Массив списков смежностей
// MatrixGraph::MatrixGraph(const IGraph &graph) : adjacencyLists(graph.VerticesCount())
// {
//     int size = graph.VerticesCount();
//     for (int i = 0; i < size; ++i)
//     {
//         Rebro *head = nullptr;
//         Rebro *curr = nullptr;
//         std::vector<int> elements = graph.GetNextVertices(i);
//         int size_elem = elements.size();
//         for (int j = 0; j < size_elem; ++j)
//         {
//             Rebro *newElement = new Rebro(elements[j]);
//             if (!head)
//             {
//                 // Если head еще не инициализирован, устанавливаем его на новый элемент
//                 head = newElement;
//                 curr = head;
//             }
//             else
//             {
//                 // Иначе добавляем новый элемент в конец списка
//                 curr->next = newElement;
//                 curr = curr->next;
//             }
//         }
//         adjacencyLists[i] = head;
//     }
// }

// std::vector<int> MatrixGraph::GetNextVertices(int vertex) const
// {
//     assert(0 <= vertex && vertex < adjacencyLists.size());
//     std::vector<int> result;
//     Rebro *curr = adjacencyLists[vertex];
//     while (curr)
//     {
//         result.push_back(curr->index);
//         curr = curr->next;
//     }
//     return result;
// }

// std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const
// {
//     assert(0 <= vertex && vertex < adjacencyLists.size());
//     std::vector<int> prevVertices;

//     for (int from = 0; from < adjacencyLists.size(); from++)
//     {
//         Rebro *curr = adjacencyLists[from];
//         while (curr)
//         {
//             if (curr->index == vertex)
//             {
//                 prevVertices.push_back(from);
//             }
//             curr = curr->next;
//         }
//     }
//     return prevVertices;
// }

// void MatrixGraph::AddEdge(int from, int to)
// {
//     assert(0 <= from && from < adjacencyLists.size());
//     assert(0 <= to && to < adjacencyLists.size());
//     Rebro *curr = adjacencyLists[from];
//     Rebro *parent = curr;
//     while (curr)
//     {
//         parent = curr;
//         curr = curr->next;
//     }
//     curr = new Rebro(to);
//     if (adjacencyLists[from] != nullptr)
//     {
//         parent->next = curr;
//     }
//     else
//     {
//         adjacencyLists[from] = curr;
//     }
// }

// class ArcGraph : public IGraph
// {
// public:
//     ArcGraph(int size)
//         : adjacencyLists(size)
//     {
//     }

//     ArcGraph(const IGraph &graph);

//     ~ArcGraph(){};

//     void AddEdge(int from, int to) override;

//     int VerticesCount() const override
//     {
//         return static_cast<int>(adjacencyLists.size());
//     }

//     std::vector<int> GetNextVertices(int vertex) const override;

//     std::vector<int> GetPrevVertices(int vertex) const override;

// private:
//     std::vector<std::pair<int, int>> adjacencyLists;
// };

// ArcGraph::ArcGraph(const IGraph &graph)
// {
//     for (int i = 0; i < adjacencyLists.size(); ++i)
//     {
//         std::vector<int> elems = graph.GetNextVertices(i);
//         int from = i;
//         int size = elems.size();
//         for (int j = 0; j < size; ++j)
//         {
//             std::pair<int, int> tmp;
//             tmp.first = from;
//             tmp.second = elems[j];
//             adjacencyLists.push_back(tmp);
//         }
//     }
// }

// std::vector<int> ArcGraph::GetNextVertices(int vertex) const
// {
//     assert(0 <= vertex && vertex < adjacencyLists.size());
//     std::vector<int> result;
//     for (int i = 0; i < adjacencyLists.size(); ++i)
//     {
//         if (adjacencyLists[i].first == vertex)
//         {
//             result.push_back(adjacencyLists[i].second);
//         }
//     }
//     return result;
// }

// std::vector<int> ArcGraph::GetPrevVertices(int vertex) const
// {
//     assert(0 <= vertex && vertex < adjacencyLists.size());
//     std::vector<int> prevVertices;

//     for (int i = 0; i < adjacencyLists.size(); ++i)
//     {
//         if (adjacencyLists[i].second == vertex)
//         {
//             prevVertices.push_back(adjacencyLists[i].first);
//         }
//     }
//     return prevVertices;
// }

// void ArcGraph::AddEdge(int from, int to)
// {
//     assert(0 <= from && from < adjacencyLists.size());
//     assert(0 <= to && to < adjacencyLists.size());
//     std::pair<int, int> tmp;
//     tmp.first = from;
//     tmp.second = to;
//     adjacencyLists.push_back(tmp);
// }

void dfs_aux(int u, const IGraph &graph, std::vector<bool> &visited, void (*callback)(int v))
{
    visited[u] = true;
    callback(u);

    std::vector<int> children = graph.GetNextVertices(u);

    for (int v : children)
    {
        if (!visited[v])
        {
            dfs_aux(v, graph, visited, callback);
        }
    }
}

int dfs(const IGraph &graph, void (*callback)(int v))
{
    int vertices_count = graph.VerticesCount();
    std::vector<bool> visited(vertices_count, false);

    for (int i = 0; i < vertices_count; ++i)
    {
        if (!visited[i])
        {
            dfs_aux(i, graph, visited, callback);
        }
    }
    return 0;
}

void bfs_aux(int u, const IGraph &graph, std::vector<bool> &visited, void (*callback)(int v))
{
    std::queue<int> q;
    q.push(u);
    visited[u] = true;
    while (!q.empty())
    {
        int v = q.front();
        q.pop();

        callback(v);

        std::vector<int> children = graph.GetNextVertices(u);
        for (int w : children)
        {
            if (!visited[w])
            {
                visited[w] = true;
                q.push(w);
            }
        }
    }
}

int bfs(const IGraph &graph, void (*callback)(int v))
{
    int vertices_count = graph.VerticesCount();

    std::vector<bool> visited(vertices_count, false);

    for (int i = 0; i < vertices_count; ++i)
    {
        if (!visited[i])
        {
            bfs_aux(i, graph, visited, callback);
        }
    }
    return 0;
}

int main()
{
    MatrixGraph mgraph(6);
    mgraph.AddEdge(0, 1);
    mgraph.AddEdge(1, 0);

    mgraph.AddEdge(1, 2);
    mgraph.AddEdge(2, 1);

    mgraph.AddEdge(2, 3);
    mgraph.AddEdge(3, 2);

    mgraph.AddEdge(2, 4);
    mgraph.AddEdge(4, 2);

    mgraph.AddEdge(3, 4);
    mgraph.AddEdge(4, 3);

    std::cout << "DFS MatrixGraph: ";
    dfs(mgraph, [](int v)
        { std::cout << v << " "; });
    std::cout << std::endl;

    std::cout << "DFS MatrixGraph: ";
    bfs(mgraph, [](int v)
        { std::cout << v << " "; });
    std::cout << std::endl;

    ListGraph lgraph(mgraph);

    std::cout << "DFS ListGraph: ";
    dfs(lgraph, [](int v)
        { std::cout << v << " "; });
    std::cout << std::endl;

    std::cout << "DFS ListGraph: ";
    bfs(lgraph, [](int v)
        { std::cout << v << " "; });
    std::cout << std::endl;

    SetGraph sgraph(mgraph);

    std::cout << "DFS SetGraph: ";
    dfs(lgraph, [](int v)
        { std::cout << v << " "; });
    std::cout << std::endl;

    std::cout << "DFS SetGraph: ";
    bfs(lgraph, [](int v)
        { std::cout << v << " "; });
    std::cout << std::endl;

    // ArcGraph agraph(lgraph);

    // std::cout << "DFS ArcGraph: ";
    // dfs(agraph, [](int v)
    //     { std::cout << v << " "; });
    // std::cout << std::endl;

    // std::cout << "DFS ArcGraph: ";
    // bfs(agraph, [](int v)
    //     { std::cout << v << " "; });
    // std::cout << std::endl;

    std::cout << "OK" << std::endl;
}