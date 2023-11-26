// Нужно кастомизировать std::unordered_set для операций со структурой данных
// struct Node {
// std::string product_name;
// int color;
// int size;
// };

#include <iostream>
#include <vector>

const size_t DEFAULT_SIZE = 8;

struct Node
{
    Node()
        : color(0), size(0), product_name(nullptr)
    {
    }

    Node(std::string data, int c, int size)
        : product_name(data), color(c), size(size)
    {
    }

    bool operator==(const Node &other) const
    {
        return ((this->color == other.color) && (this->size == other.size) && (this->product_name == other.product_name));
    }

    bool operator!=(const Node &other) const
    {
        return ((this->color != other.color) || (this->size != other.size) || (this->product_name != other.product_name));
    }

    bool operator!=(const std::string elem)
    {
        return this->product_name != elem;
    }

    bool operator==(const std::string elem)
    {
        return this->product_name == elem;
    }

    std::string product_name;
    int color;
    int size;
};

Node DELETED("DELETED", 0, 0);
Node EMPTY("NIL", 0, 0);

class StringHasher
{
public:
    StringHasher(size_t prime = 71)
        : prime(prime)
    {
    }

    size_t operator()(const Node elem)
    {
        size_t hash = 0;
        std::string str = elem.product_name;
        for (int i = 0; i < str.size(); i++)
        {
            hash = hash * prime + str[i];
        }
        return hash;
    }

private:
    size_t prime;
};

template <typename T, typename Hasher>
class Hashtable
{
public:
    Hashtable(size_t initial_size = DEFAULT_SIZE)
        : size(0), table(initial_size, EMPTY), tableSize(initial_size)
    {
    }

    ~Hashtable(){};

    // Adding
    bool Add(const Node &key)
    {
        size_t first = hasherOne(key);
        size_t hash = first % tableSize;
        bool del = true;
        int index = -1;
        size_t second = 0;
        int i = 0;

        if (4 * size >= tableSize * 3)
        {
            grow();
        }

        if (table[hash] == key)
        {
            return false;
        }
        else
        {
            second = hasherTwo(key);
            if (table[hash] != EMPTY)
            {
                for (; i < tableSize; ++i)
                {
                    hash = (first + i * second) % tableSize;
                    if (table[hash] == key)
                    {
                        return false;
                    }
                    if (table[hash] == DELETED && del)
                    {
                        del = false;
                        index = hash;
                    }
                    if (table[hash] == EMPTY)
                    {
                        break;
                    }
                }
            }
        }
        if (index == -1)
        {
            index = hash;
        }
        if (table[index] != DELETED && table[index] != EMPTY)
        {
            grow();
            i = 0;
            while (table[index] != DELETED && table[index] != EMPTY && i < tableSize)
            {
                index = (first + i * second) % tableSize;
            }
        }
        index = hash;
        table[index] = key;
        ++size;
        return true;
    }

    // Finding
    bool Has(const Node &key)
    {
        size_t first = hasherOne(key);
        size_t hash = first % tableSize;

        if (table[hash] == key)
        {
            return true;
        }
        else
        {
            size_t second = hasherTwo(key);
            for (int i = 0; i < tableSize; ++i)
            {
                hash = (first + i * second) % tableSize;
                if (table[hash] == key)
                {
                    return true;
                }
                if (table[hash] == EMPTY)
                {
                    return false;
                }
            }
            return false;
        }
    }

    // Deleting
    bool Delete(const Node &key)
    {
        size_t first = hasherOne(key);
        size_t hash = first % tableSize;

        if (table[hash] == key)
        {
            table[hash] = DELETED;
            --size;
            return true;
        }
        else
        {
            size_t second = hasherTwo(key);
            for (int i = 0; i < tableSize; ++i)
            {
                hash = (first + i * second) % tableSize;
                if (table[hash] == EMPTY)
                {
                    return false;
                }
                if (table[hash] == key)
                {
                    table[hash] = DELETED;
                    --size;
                    return true;
                }
            }
            return false;
        }
    }

private:
    // rehash
    void grow()
    {
        tableSize *= 2;
        std::vector<T> newTable(tableSize, EMPTY);

        for (int i = 0; i < tableSize / 2; ++i)
        {
            if (table[i] != DELETED && table[i] != EMPTY)
            {
                size_t firstHash = hasherOne(table[i]);
                size_t hash = firstHash % tableSize;
                if (newTable[hash] == EMPTY)
                {
                    newTable[hash] = table[i];
                }
                else
                {
                    int j = 1;
                    size_t secondHash = hasherTwo(table[i]);
                    hash = (firstHash + j * secondHash) % tableSize;
                    while (newTable[hash] != EMPTY)
                    {
                        ++j;
                        hash += secondHash;
                        hash %= tableSize;
                    }
                    newTable[hash] = table[i];
                }
            }
        }

        table = std::move(newTable);
    }

    std::vector<T> table;
    size_t size;
    size_t tableSize;
    Hasher hasherOne;
    Hasher hasherTwo{37};
};

int main()
{
    Hashtable<Node, StringHasher> table;

    char op;
    std::string key;
    int color = 0;
    int size = 0;

    while (std::cin >> op >> key >> color >> size)
    {
        Node temp(key, color, size);
        switch (op)
        {
        case '?':
        {
            std::cout << (table.Has(temp) ? "OK" : "FAIL") << std::endl;
            break;
        }
        case '+':
        {
            std::cout << (table.Add(temp) ? "OK" : "FAIL") << std::endl;
            break;
        }
        case '-':
        {
            std::cout << (table.Delete(temp) ? "OK" : "FAIL") << std::endl;
            break;
        }
        case '!':
        {
            return 0;
        }
        }
    }
    return 0;
}