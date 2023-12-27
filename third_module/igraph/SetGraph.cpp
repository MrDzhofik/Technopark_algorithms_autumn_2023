#include "SetGraph.hpp"

StringHasher::StringHasher(size_t prime) : prime(prime)
{
}

size_t StringHasher::operator()(const int number)
{
    size_t hash = 0;
    int num = number;
    while (num != 0)
    {
        hash = hash * prime + num % 10;
        num = num / 10;
    }
    return hash;
}

template <typename T, typename Hasher>
bool HashTable<T, Hasher>::Add(const T &key)
{
    // если коэффициент заполнения >  3/4
    if (4 * size >= tableSize * 3)
    {
        grow();
    }

    size_t first = hasherOne(key);
    bool del = true;
    int index = -1;
    size_t second = hasherTwo(key) * 2 + 1; // h2 должна возвращать нечетные значения
    size_t hash = first % tableSize;

    // поиск добавляемой ячейки
    for (int i = 1; i <= tableSize; ++i)
    {
        if (table[hash] == key)
        {
            return false;
        }
        if (table[hash] == DELETED && del)
        {
            del = false;
            index = hash; // запоминаем первую удаленную ячейку
        }
        if (table[hash] == EMPTY)
        {
            break;
        }
        hash = (first + i * second) % tableSize; // двойное хэширование
    }
    // eсли не нашли удаленных ячеек, то записываем в пустую
    if (index == -1)
    {
        index = hash;
    }
    // если ячейка не удаленная и не пустая, мы сделали кол-во пробирований = количество ячеек в таблице
    if (table[index] != DELETED && table[index] != EMPTY)
    {
        grow();
        int i = 0;
        index = first % tableSize;
        while (table[index] != DELETED && table[index] != EMPTY && i < tableSize)
        {
            ++i;
            index = (first + i * second) % tableSize; // пробирование двойным хэшированием
        }
    }
    table[index] = key;
    if (del)
    {
        ++size;
    }
    return true;
}

template <typename T, typename Hasher>
bool HashTable<T, Hasher>::Delete(const T &key)
{
    size_t first = hasherOne(key);
    size_t hash = first % tableSize;

    size_t second = hasherTwo(key) * 2 + 1; // h2 должна возвращать нечетные значения
    for (int i = 1; i <= tableSize; ++i)
    {
        if (table[hash] == key)
        {
            table[hash] = DELETED;
            return true;
        }
        if (table[hash] == EMPTY)
        {
            break;
        }
        hash = (first + i * second) % tableSize;
    }
    return false;
}

template <typename T, typename Hasher>
bool HashTable<T, Hasher>::Has(const T &key)
{
    size_t first = hasherOne(key);
    size_t hash = first % tableSize;

    size_t second = hasherTwo(key) * 2 + 1; // h2 должна возвращать нечетные значения
    for (int i = 1; i <= tableSize; ++i)
    {
        if (table[hash] == key)
        {
            return true;
        }
        if (table[hash] == EMPTY)
        {
            return false;
        }
        hash = (first + i * second) % tableSize; // двойное хэширование
    }
    return false;
}

template <typename T, typename Hasher>
void HashTable<T, Hasher>::grow()
{
    tableSize *= 2;
    std::vector<T> newTable(tableSize, EMPTY);

    for (int i = 0; i < tableSize / 2; ++i)
    {
        if (table[i] != EMPTY)
        {
            // удаленные ячейки не заносим в новую таблицу, поэтому уменьшаем размер
            if (table[i] == DELETED)
            {
                --size;
            }
            // иначе ищем место для ячейки в новой таблице
            else
            {
                size_t firstHash = hasherOne(table[i]);
                size_t hash = firstHash % tableSize;
                if (newTable[hash] != EMPTY)
                {
                    int j = 0;
                    size_t secondHash = hasherTwo(table[i]) * 2 + 1;
                    while (newTable[hash] != EMPTY)
                    {
                        ++j;
                        hash = (firstHash + j * secondHash) % tableSize;
                    }
                }
                newTable[hash] = table[i];
            }
        }
    }

    table = std::move(newTable);
}

SetGraph::SetGraph(const IGraph &graph)
    : adjacencyLists(graph.VerticesCount())
{
    for (int i = 0; i < graph.VerticesCount(); i++)
    {
        std::vector<int> elems = graph.GetNextVertices(i);
        int size = elems.size();
        for (int j = 0; j < size; ++j)
        {
            adjacencyLists[i].Add(elems[j]);
        }
    }
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const
{
    assert(0 <= vertex && vertex < adjacencyLists.size());
    std::vector<int> result;
    int size = adjacencyLists[vertex].get_size();
    for (int i = 0; i < size; ++i)
    {
        int elem = adjacencyLists[vertex].get_elem(i);
        if (elem != DELETED && elem != EMPTY)
        {
            result.push_back(elem);
        }
    }
    return result;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const
{
    assert(0 <= vertex && vertex < adjacencyLists.size());
    std::vector<int> prevVertices;

    int size = adjacencyLists.size();

    for (int from = 0; from < size; from++)
    {
        std::vector<int> result;
        result = GetNextVertices(from);
        int arr_size = result.size();
        for (int j = 0; j < arr_size; ++j)
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
    adjacencyLists[from].Add(to);
}
