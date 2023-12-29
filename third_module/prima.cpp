#include <iostream>
#include <vector>
#include <queue>

const int INF = 10000000;

struct WeightedEdge
{
    int to;
    int weight;

    WeightedEdge(int to, int weight) : to(to), weight(weight) {}

    bool operator<(const WeightedEdge &other) const
    {
        return weight > other.weight;
    }
};

class WeightedGraph
{
public:
    WeightedGraph(int vertices) : vertices(vertices), adjacencyList(vertices) {}

    void addEdge(int from, int to, int weight)
    {
        WeightedEdge tmp0(to, weight);
        adjacencyList[from].push_back(tmp0);
        WeightedEdge tmp1(from, weight);
        adjacencyList[to].push_back(tmp1);
    }

    std::vector<WeightedEdge> prima()
    {
        std::vector<WeightedEdge> result;
        std::vector<bool> visited(vertices, false);
        std::priority_queue<std::pair<int, WeightedEdge>, std::vector<std::pair<int, WeightedEdge>>, std::greater<>> pq;

        int startVertex = 0;
        visited[startVertex] = true;

        for (const WeightedEdge &edge : adjacencyList[startVertex])
        {
            pq.push({edge.weight, edge});
        }

        while (!pq.empty())
        {
            WeightedEdge currentEdge = pq.top().second;
            pq.pop();

            int currentVertex = currentEdge.to;

            if (visited[currentVertex])
            {
                continue;
            }

            visited[currentVertex] = true;
            result.push_back(currentEdge);

            for (const WeightedEdge &nextEdge : adjacencyList[currentVertex])
            {
                if (!visited[nextEdge.to])
                {
                    pq.push({nextEdge.weight, nextEdge});
                }
            }
        }

        return result;
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
        weightedGraph.addEdge(from - 1, to - 1, weight);
    }

    std::vector<WeightedEdge> res = weightedGraph.prima();

    int totalWeight = 0;
    for (const WeightedEdge &edge : res)
    {
        totalWeight += edge.weight;
    }

    std::cout << totalWeight << std::endl;
    return 0;
}

// 4 4
// 1 2 1
// 2 3 2
// 3 4 5
// 4 1 4
