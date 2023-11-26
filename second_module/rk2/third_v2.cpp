// Нужно кастомизировать std::unordered_set для операций со структурой данных
// struct Node {
// std::string product_name;
// int color;
// int size;
// };

#include <iostream>
#include <unordered_set>

const size_t DEFAULT_SIZE = 8;

struct Node
{
    Node()
        : color(0), size(0), product_name("NIL")
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

namespace std
{
    template <>
    struct hash<Node>
    {
        std::size_t operator()(const Node &obj) const
        {
            StringHasher hasher;
            return hasher(obj);
        }
    };
}

struct MyComparator
{
    bool operator()(const Node &obj1, const Node &obj2) const
    {
        return ((obj1.color == obj2.color) && (obj1.size == obj2.size) && (obj1.product_name == obj2.product_name));
    }
};

using HashSet = std::unordered_set<Node, std::hash<Node>, MyComparator>;

int main()
{
    HashSet table;

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
            bool a = table.find(temp) != table.end();
            std::cout << ((table.find(temp) != table.end()) ? "OK" : "FAIL") << std::endl;
            break;
        }
        case '+':
        {
            std::cout << (table.insert(temp).second ? "OK" : "FAIL") << std::endl;
            break;
        }
        case '-':
        {
            std::cout << ((table.erase(temp) > 0) ? "OK" : "FAIL") << std::endl;
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