#include <iostream>
#include <vector>
#include <queue>
#include <limits>

const int INF = std::numeric_limits<int>::max();

struct WeightedEdge
{
    int to;
    int weight;

    WeightedEdge(int _to, int _weight) : to(_to), weight(_weight) {}
};

class WeightedGraph
{
public:
    WeightedGraph(int _vertices) : vertices(_vertices), adjacencyList(_vertices) {}

    void addEdge(int from, int to, int weight)
    {
        adjacencyList[from].emplace_back(to, weight);
    }

    std::vector<int> dijkstra(int start)
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

    int startVertex = 0;
    std::vector<int> distances = weightedGraph.dijkstra(startVertex);

    // Вывод результатов
    std::cout << "Shortest distances from vertex " << startVertex << ":\n";
    for (int i = 0; i < towns; ++i)
    {
        if (distances[i] == INF)
        {
            std::cout << "Vertex " << i << ": unreachable\n";
        }
        else
        {
            std::cout << "Vertex " << i << ": " << distances[i] << "\n";
        }
    }

    // Осталось только добавить функцию поиска кратчайшего пути от одной точки до другой

    return 0;
}

// 6
// 9
// 0 3 1
// 0 4 2
// 1 2 7
// 1 3 2
// 1 4 3
// 1 5 3
// 2 5 3
// 3 4 4
// 3 5 6
// 0 2
