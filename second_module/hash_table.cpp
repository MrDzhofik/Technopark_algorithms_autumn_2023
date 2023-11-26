// Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
// Хранимые строки непустые и состоят из строчных латинских букв.
// Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
// Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае,
// когда коэффициент заполнения таблицы достигает 3/4.
// Структура данных должна поддерживать операции добавления строки в множество,
// удаления строки из множества и проверки принадлежности данной строки множеству.

// 1_2. Для разрешения коллизий используйте двойное хеширование.

#include <iostream>
#include <vector>
#include <sstream>
#include <assert.h>

const size_t DEFAULT_SIZE = 8;
std::string DELETED = "DEL";
std::string EMPTY = "NIL";

// Хеширование методом Горнера
class StringHasher
{
public:
    StringHasher(size_t prime = 71)
        : prime(prime)
    {
    }

    size_t operator()(const std::string &str)
    {
        size_t hash = 0;
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

    // Adding
    bool Add(const T &key)
    {
        if (4 * size >= tableSize * 3)
        {
            grow();
        }

        size_t first = hasherOne(key);
        bool del = true;
        int index = -1;
        size_t second = 0;
        int i = 0;
        size_t hash = first % tableSize;

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
    bool Has(const T &key)
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
    bool Delete(const T &key)
    {
        size_t first = hasherOne(key);
        size_t hash = first % tableSize;

        if (table[hash] == key)
        {
            table[hash] = DELETED;
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
                    table[hash] = DELETED;
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

private:
    // rehash
    void grow()
    {
        tableSize *= 2;
        std::vector<T> newTable(tableSize, EMPTY);

        for (int i = 0; i < tableSize / 2; ++i)
        {
            if (table[i] != EMPTY)
            {
                if (table[i] == DELETED)
                {
                    --size;
                    break;
                }
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
                        hash = (firstHash + j * secondHash) % tableSize;
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

void doLogic(std::istream &in, std::ostream &out)
{
    Hashtable<std::string, StringHasher> table;

    char op;
    std::string key;

    while (in >> op >> key)
    {
        switch (op)
        {
        case '?':
        {
            out << (table.Has(key) ? "OK" : "FAIL") << std::endl;
            break;
        }
        case '+':
        {
            out << (table.Add(key) ? "OK" : "FAIL") << std::endl;
            break;
        }
        case '-':
        {
            out << (table.Delete(key) ? "OK" : "FAIL") << std::endl;
            break;
        }
        case '!':
        {
            return;
        }
        }
    }
    return;
}

void testLogic()
{
    // first test
    {
        std::stringstream in;
        in << "+ hello + bye ? bye + bye - bye ? bye ? hello ";

        std::stringstream out;
        doLogic(in, out);
        assert(out.str() == "OK\nOK\nOK\nFAIL\nOK\nFAIL\nOK\n");
    }

    // double resize
    {
        std::stringstream in;
        in << "+ hello + bye + good + afternoon + day + night + minecraft + football + messi + ok + lol + alg + cobol + fortran + popo - hello - bye ? day ";

        std::stringstream out;
        doLogic(in, out);
        assert(out.str() == "OK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\n");
    }

    // empty table
    {
        std::stringstream in;
        in << "? day - hello - bye + day ?day ";

        std::stringstream out;
        doLogic(in, out);
        assert(out.str() == "FAIL\nFAIL\nFAIL\nOK\nOK\n");
    }

    // add existing element
    {
        std::stringstream in;
        in << "+ hello + hello - bye ? day ";

        std::stringstream out;
        doLogic(in, out);
        assert(out.str() == "OK\nFAIL\nFAIL\nFAIL\n");
    }

    // find after deleting
    {
        std::stringstream in;
        in << "+ hello  + messi ? hello - hello ? hello ";

        std::stringstream out;
        doLogic(in, out);
        assert(out.str() == "OK\nOK\nOK\nOK\nFAIL\n");
    }

    // double resize and deleting
    {
        std::stringstream in;
        in << "+ hello + bye + good + afternoon + day + night + minecraft + football + messi + ok + lol + alg + cobol + fortran + popo - hello - bye ? day - good - afternoon - day - night - minecraft - football - messi - ok - lol - alg - cobol - fortran - popo";

        std::stringstream out;
        doLogic(in, out);
        // std::cout << out.str();
        assert(out.str() == "OK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\n");
    }

    // triple resize and delete
    {
        std::stringstream in;
        in << "+ a + b + c + d + e + f + g + h + i + j + k + l + m + n + o + p + q + r + s + t + u + v + w + x + y + z - a - b - c - d - e - f - g - h - i - j - k - l - m - n - o - p - q - r - s - t - u - v - w - x - y - z";

        std::stringstream out;
        doLogic(in, out);
        // std::cout << out.str();
    }

    {
        std::stringstream in;
        in << "+ abcdefghijklmnopqrstuvwxyz + abcdefghijklmnopqrstuvwxyzzyxwvutsrqponmlkjihgfedcba - abcdefghijklmnopqrstuvwxyzzyxwvutsrqponmlkjihgfedcba + abcdefghijklmnopqrstuvwxyzzyxwvutsrqponmlkjihgfedcba ? abcdefghijklmnopqrstuvwxyz";

        std::stringstream out;
        doLogic(in, out);
        // std::cout << out.str();
        assert(out.str() == "OK\nOK\nOK\nOK\nOK\n");
    }

    {
        std::stringstream in;
        in << "+ cat + rat + bat + hat + mat + pat + sat + vat + fat + gat + hat + iat + jat + kat + lat + mat + nat + oat + pat + qat + rat + sat + tat + uat + vat + wat + xat + yat + zat - vat - wat - xat - yat - zat ? cat ? rat ? bat ? hat ? mat";

        std::stringstream out;
        doLogic(in, out);
        std::cout << out.str();
        assert(out.str() == "OK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nFAIL\nOK\nOK\nOK\nOK\nFAIL\nOK\nOK\nFAIL\nOK\nFAIL\nFAIL\nOK\nOK\nFAIL\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\nOK\n");
    }
}

int main()
{
    testLogic();
    std::cout << "Test OK" << std::endl;

    Hashtable<std::string, StringHasher> table;

    char op;
    std::string key;

    while (std::cin >> op >> key)
    {
        switch (op)
        {
        case '?':
        {
            std::cout << (table.Has(key) ? "OK" : "FAIL") << std::endl;
            break;
        }
        case '+':
        {
            std::cout << (table.Add(key) ? "OK" : "FAIL") << std::endl;
            break;
        }
        case '-':
        {
            std::cout << (table.Delete(key) ? "OK" : "FAIL") << std::endl;
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
