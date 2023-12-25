#include <vector>
#include <assert.h>
#include <iostream>
#include <string>

inline const size_t DEFAULT_SIZE = 8;
inline std::string DELETED = "DEL";
inline std::string EMPTY = "NIL";

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
    HashTable(size_t initial_size = DEFAULT_SIZE);

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