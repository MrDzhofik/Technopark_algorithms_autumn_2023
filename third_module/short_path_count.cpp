// Дан невзвешенный неориентированный граф.
// В графе может быть несколько кратчайших путей между какими-то вершинами.
// Найдите количество различных кратчайших путей между заданными вершинами.
// Требования: сложность O(V+E).
// Формат ввода.
// v: кол-во вершин (макс. 50000),
// n: кол-во ребер (макс. 200000),
// n пар реберных вершин,
// пара вершин u, w для запроса.
// Формат вывода.
// Количество кратчайших путей от u к w.

#include <vector>
#include <cassert>
#include <queue>
#include <iostream>
#include <sstream>

// Интерфейс графа
struct IGraph
{
    virtual ~IGraph(){};

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

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

MatrixGraph::MatrixGraph(const IGraph &graph)
    : adjacencyLists(graph.VerticesCount())
{
    for (int i = 0; i < graph.VerticesCount(); i++)
    {
        adjacencyLists[i] = graph.GetNextVertices(i);
    }
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const
{
    assert(0 <= vertex && vertex < adjacencyLists.size());
    return adjacencyLists[vertex];
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const
{
    assert(0 <= vertex && vertex < adjacencyLists.size());
    std::vector<int> prevVertices;

    for (int from = 0; from < adjacencyLists.size(); from++)
    {
        for (int to : adjacencyLists[from])
        {
            if (to == vertex)
            {
                prevVertices.push_back(from);
            }
        }
    }
    return prevVertices;
}

void MatrixGraph::AddEdge(int from, int to)
{
    assert(0 <= from && from < adjacencyLists.size());
    assert(0 <= to && to < adjacencyLists.size());
    adjacencyLists[from].push_back(to);
}

// Обход в ширину
void bfs_aux(int u, const IGraph &graph, std::vector<bool> &visited, std::vector<int> &distance, std::vector<int> &count)
{
    std::queue<int> q;
    q.push(u);
    while (!q.empty())
    {
        int v = q.front();
        q.pop();

        if (!visited[v])
        {
            std::vector<int> children = graph.GetNextVertices(v);
            for (int w : children)
            {
                if (distance[w] > distance[v] + 1)
                {
                    distance[w] = distance[v] + 1;
                    count[w] = count[v];
                }
                else if (distance[w] == distance[v] + 1)
                {
                    count[w] += count[v];
                }
                q.push(w);
            }
            visited[v] = true;
        }
    }
}

int bfs(const IGraph &graph, int start, int finish)
{
    int vertices_count = graph.VerticesCount();

    std::vector<bool> visited(vertices_count, false);
    std::vector<int> distance(vertices_count, 100000000);

    std::vector<int> count(vertices_count, 0);
    if (start < vertices_count)
    {
        count[start] = 1;
        distance[start] = 0;
    }

    bfs_aux(start, graph, visited, distance, count);
    int result = (finish < vertices_count) ? count[finish] : 0;
    return result;
}

void doLogic(std::istream &in, std::ostream &out)
{
    int number = 0;
    in >> number;
    int num = 0;
    in >> num;
    MatrixGraph mgraph(number);
    int from = 0, to = 0;
    for (int i = 0; i < num; ++i)
    {
        in >> from >> to;
        mgraph.AddEdge(from, to);
        mgraph.AddEdge(to, from);
    }

    int start = 0, finish = 0;
    in >> start >> finish;

    int ans = bfs(mgraph, start, finish);
    out << ans << std::endl;
}

void testLogic()
{
    // first test
    {
        std::stringstream in;
        in << "4 5 0 1 0 2 1 2 1 3 2 3 0 3 ";

        std::stringstream out;
        doLogic(in, out);
        assert(out.str() == "2\n");
    }

    // Граф с циклами
    {
        std::stringstream in;
        in << "5 8 0 1 0 3 0 4 1 2 1 3 3 2 3 4 4 2 0 2 ";

        std::stringstream out;
        doLogic(in, out);
        assert(out.str() == "3\n");
    }

    // Граф с началом не из 0
    {
        std::stringstream in;
        in << "5 6 0 1 0 3 0 4 1 2 1 3 3 4 4 2 ";

        std::stringstream out;
        doLogic(in, out);
        std::cout << out.str();
        assert(out.str() == "2\n");
    }
    // Пустой граф:
}

int main()
{
    // testLogic();
    // std::cout << "Test OK" << std::endl;
    int number = 0;
    std::cin >> number;
    int num = 0;
    std::cin >> num;
    MatrixGraph mgraph(number);
    int from = 0, to = 0;
    for (int i = 0; i < num; ++i)
    {
        std::cin >> from >> to;
        mgraph.AddEdge(from, to);
        mgraph.AddEdge(to, from);
    }

    int start = 0, finish = 0;
    std::cin >> start >> finish;

    int ans = bfs(mgraph, start, finish);
    std::cout << ans << std::endl;
}