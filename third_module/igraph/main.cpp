#include <iostream>
#include <vector>
#include <queue>
#include <cassert>
#include "IGraph.hpp"
#include "ListGraph.hpp"
#include "MatrixGraph.hpp"
#include "ArcGraph.hpp"
#include "SetGraph.hpp"

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
    MatrixGraph mgraph(5);
    mgraph.AddEdge(0, 1);
    mgraph.AddEdge(1, 0);

    // mgraph.AddEdge(1, 2);
    // mgraph.AddEdge(2, 1);

    mgraph.AddEdge(1, 3);

    // mgraph.AddEdge(2, 3);
    // mgraph.AddEdge(3, 2);

    // mgraph.AddEdge(2, 4);
    mgraph.AddEdge(4, 2);

    mgraph.AddEdge(3, 4);
    // mgraph.AddEdge(4, 3);

    // mgraph.AddEdge(1, 5);

    std::cout << "DFS MatrixGraph: ";
    dfs(mgraph, [](int v)
        { std::cout << v << " "; });
    std::cout << std::endl;

    std::cout << "BFS MatrixGraph: ";
    bfs(mgraph, [](int v)
        { std::cout << v << " "; });
    std::cout << std::endl;

    ListGraph lgraph(mgraph);

    std::cout << "DFS ListGraph: ";
    dfs(lgraph, [](int v)
        { std::cout << v << " "; });
    std::cout << std::endl;

    std::cout << "BFS ListGraph: ";
    bfs(lgraph, [](int v)
        { std::cout << v << " "; });
    std::cout << std::endl;

    SetGraph sgraph(mgraph);

    std::cout << "DFS SetGraph: ";
    dfs(sgraph, [](int v)
        { std::cout << v << " "; });
    std::cout << std::endl;

    std::cout << "BFS SetGraph: ";
    bfs(sgraph, [](int v)
        { std::cout << v << " "; });
    std::cout << std::endl;

    ArcGraph agraph(lgraph);

    std::cout << "DFS ArcGraph: ";
    dfs(agraph, [](int v)
        { std::cout << v << " "; });
    std::cout << std::endl;

    std::cout << "BFS ArcGraph: ";
    bfs(agraph, [](int v)
        { std::cout << v << " "; });
    std::cout << std::endl;

    std::cout << "OK" << std::endl;
}