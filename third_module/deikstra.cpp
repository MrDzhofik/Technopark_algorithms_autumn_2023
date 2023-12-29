// Дан невзвешенный неориентированный граф.
// В графе может быть несколько кратчайших путей между какими - то вершинами.
// Найдите количество различных кратчайших путей между заданными вершинами.
// Требования : сложность O(V + E).Формат ввода.v : кол - во вершин(макс.50000),
//     n : кол - во ребер(макс.200000),
//     n пар реберных вершин,
//     пара вершин u, w для запроса.Формат вывода.Количество кратчайших путей от u к w.

#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <cassert>

const int INF = 10000000;

struct WeightedEdge
{
    int to;
    int weight;

    WeightedEdge(int to, int weight) : to(to), weight(weight) {}
};

class WeightedGraph
{
public:
    WeightedGraph(int vertices) : vertices(vertices), adjacencyList(vertices) {}

    void addEdge(int from, int to, int weight)
    {
        WeightedEdge tmp(to, weight);
        adjacencyList[from].push_back(tmp);
    }

    std::vector<int> deikstra(int start)
    {
        std::vector<int> distance(vertices, INF);
        distance[start] = 0;

        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
        pq.push({0, start});

        while (!pq.empty())
        {
            int u = pq.top().second;
            int dist_u = pq.top().first;
            pq.pop();

            // Пропускаем вершины, которые уже обработаны
            if (dist_u > distance[u])
            {
                continue;
            }

            for (const WeightedEdge &edge : adjacencyList[u])
            {
                int v = edge.to;
                int weight_uv = edge.weight;

                if (distance[u] + weight_uv < distance[v])
                {
                    distance[v] = distance[u] + weight_uv;
                    pq.push({distance[v], v});
                }
            }
        }

        return distance;
    }

private:
    int vertices;
    std::vector<std::vector<WeightedEdge>> adjacencyList;
};

void doLogic(std::istream &in, std::ostream &out)
{
    int towns = 0;
    std::cin >> towns;
    WeightedGraph weightedGraph(towns);

    int roads = 0;
    std::cin >> roads;
    int from = 0, to = 0, weight = 0;
    for (int i = 0; i < roads; ++i)
    {
        std::cin >> from >> to >> weight;
        weightedGraph.addEdge(from, to, weight);
        weightedGraph.addEdge(to, from, weight);
    }

    int start = 0, finish = 0;
    std::cin >> start >> finish;
    std::vector<int> distances = weightedGraph.deikstra(start);

    std::cout << distances[finish] << std::endl;
}

void testLogic()
{
    // first test
    {
        std::stringstream in;
        in << "6 9 0 3 1 0 4 2 1 2 7 1 3 2 1 4 3 1 5 3 2 5 3 3 4 4 3 5 6 0 2 ";

        std::stringstream out;
        doLogic(in, out);
        assert(out.str() == "9\n");
    }

    // start vertex is not 0
    // first test
    {
        std::stringstream in;
        in << "6 9 0 3 1 0 4 2 1 2 7 1 3 2 1 4 3 1 5 3 2 5 3 3 4 4 3 5 6 1 4 ";

        std::stringstream out;
        doLogic(in, out);
        assert(out.str() == "3\n");
    }

    // finsih vertex is smaller
    // first test
    {
        std::stringstream in;
        in << "6 9 0 3 1 0 4 2 1 2 7 1 3 2 1 4 3 1 5 3 2 5 3 3 4 4 3 5 6 4 2 ";

        std::stringstream out;
        doLogic(in, out);
        assert(out.str() == "9\n");
    }
}

int main()
{
    int towns = 0;
    std::cin >> towns;
    WeightedGraph weightedGraph(towns);

    int roads = 0;
    std::cin >> roads;
    int from = 0, to = 0, weight = 0;
    for (int i = 0; i < roads; ++i)
    {
        std::cin >> from >> to >> weight;
        weightedGraph.addEdge(from, to, weight);
        weightedGraph.addEdge(to, from, weight);
    }

    int start = 0, finish = 0;
    std::cin >> start >> finish;
    std::vector<int> distances = weightedGraph.deikstra(start);

    std::cout << distances[finish] << std::endl;

    return 0;
}
