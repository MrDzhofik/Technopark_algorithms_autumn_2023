// Рику необходимо попасть на межвселенную конференцию.
//  За каждую телепортацию он платит бутылками лимонада, поэтому хочет потратить их на дорогу как можно меньше
//  (он же всё-таки на конференцию едет!). Однако после K перелетов подряд Рика начинает сильно тошнить,
//  и он ложится спать на день. Ему известны все существующие телепортации.
//  Теперь Рик хочет найти путь (наименьший по стоимости в бутылках лимонада), учитывая,
// что телепортация не занимает времени, а до конференции осталось 10 минут (то есть он может совершить не более K перелетов)!

#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <cassert>

const int INF = 1410065408;

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

    int deikstra(int start, int limit, int finish)
    {
        std::vector<int> distance(vertices, INF);
        distance[start] = 0;

        std::vector<int> route(vertices, 0);

        route[start] = -1;

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
                    route[v] = u;
                    pq.push({distance[v], v});
                }
            }
        }

        int curr = finish;
        for (int i = 0; i < limit; ++i)
        {
            curr = route[curr];
        }

        return (curr != start) ? -1 : distance[finish];
    }

private:
    int vertices;
    std::vector<std::vector<WeightedEdge>> adjacencyList;
};

int main()
{
    int university = 0;
    std::cin >> university;
    WeightedGraph weightedGraph(university);

    int teleportation = 0;
    std::cin >> teleportation;
    int from = 0, to = 0, weight = 0;

    int limit = 0;
    std::cin >> limit;

    int start = 0, finish = 0;
    std::cin >> start >> finish;

    for (int i = 0; i < teleportation; ++i)
    {
        std::cin >> from >> to >> weight;
        if (from != to)
        {
            weightedGraph.addEdge(from - 1, to - 1, weight);
            weightedGraph.addEdge(to - 1, from - 1, weight);
        }
    }

    int result = weightedGraph.deikstra(start - 1, limit, finish - 1);

    std::cout << ((result == INF) ? -1 : result) << std::endl;

    return 0;
}
