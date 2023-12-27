#pragma once
#include <vector>
#include <assert.h>
#include <iostream>
#include <string>
#include "IGraph.hpp"

// Массив хэш-таблиц

inline const size_t DEFAULT_SIZE = 8;
inline int DELETED = -1;
inline int EMPTY = -2;

class StringHasher
{
public:
    StringHasher(size_t prime);

    size_t operator()(const int number);

private:
    size_t prime;
};

template <typename T, typename Hasher>
class HashTable
{
public:
    HashTable(size_t initial_size = DEFAULT_SIZE)
        : size(0), table(initial_size, EMPTY), tableSize(initial_size)
    {
    }

    T get_elem(int i) const
    {
        return table[i];
    }

    int get_size() const
    {
        return tableSize;
    }

    // Adding
    bool Add(const T &key);

    // Finding
    bool Has(const T &key);

    // Deleting
    bool Delete(const T &key);

private:
    // rehash
    void grow();

    std::vector<T> table;
    size_t size;
    size_t tableSize;
    Hasher hasherOne{71};
    Hasher hasherTwo{37};
};

// Массив HashTable
class SetGraph : public IGraph
{
public:
    SetGraph(int size)
        : adjacencyLists(size)
    {
    }

    SetGraph(const IGraph &graph);

    ~SetGraph(){};

    void AddEdge(int from, int to) override;

    int VerticesCount() const override
    {
        return static_cast<int>(adjacencyLists.size());
    }

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<HashTable<int, StringHasher>> adjacencyLists; // поменять
};