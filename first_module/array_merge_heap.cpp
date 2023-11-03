// Напишите программу, которая использует кучу для слияния K отсортированных массивов суммарной длиной N.

// Требования:

//     Время работы O(N * logK)
//     Куча должна быть реализована в виде шаблонного класса.
//     Решение должно поддерживать передачу функции сравнения снаружи.
//     Куча должна быть динамической.

#include <iostream>
#include <assert.h>
#include <sstream>

// Типы данных
template <class T>
struct DefaultComparator
{
    bool operator()(const T &l, const T &r) const
    {
        return l > r;
    }
};

struct ArrayDesc
{
    int *array;
    int size, currPos;
    ArrayDesc() : array(nullptr), size(0), currPos(0)
    {
    }
    ArrayDesc(const int *arr, int size) : size(size), currPos(0)
    {
        array = new int[size];
        for (int i = 0; i < size; ++i)
        {
            array[i] = arr[i];
        }
    }
    int get()
    {
        return array[currPos];
    }
    void inc()
    {
        currPos++;
    }
    bool checked()
    {
        return currPos >= size;
    }
};

std::ostream &operator<<(std::ostream &output, ArrayDesc &d)
{
    output << "[ ";
    for (int i = 0; i < d.size; i++)
    {
        output << d.array[i] << " ";
    }
    output << "]";
    return output;
}

class ArrayDescComparator
{
public:
    ArrayDescComparator()
    {
    }

    bool operator()(const ArrayDesc &l, const ArrayDesc &r)
    {
        return l.array[l.currPos] > r.array[r.currPos];
    }
};

template <typename T, typename Comparator = DefaultComparator<T>>
class Heap
{
public:
    Heap()
    {
        size = 8;
        actualSize = 0;
        arr = new T[8];
    };
    Heap(const T *array, int siz);
    ~Heap()
    {
        delete[] arr;
    };
    const int &top()
    {
        return arr[0].get();
    };
    int extractTop();
    void PrintForTest(std::ostream &out = std::cout);
    void Print();
    // Функция изменения размера кучи
    void grow();
    void add(const T &elem);
    int getActualSize()
    {
        return actualSize;
    };

private:
    int size;
    int actualSize;
    T *arr;
    void buildHeap();
    void siftDown(int index);
    void siftUp(int index);
    Comparator cmp;
};

template <typename T, typename Comparator>
Heap<T, Comparator>::Heap(const T *array, int siz)
{
    size = siz;
    arr = new T[size];
    for (int i = 0; i < siz; ++i)
    {
        arr[i] = array[i];
    }
    actualSize = size;
    buildHeap();
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::siftDown(int index)
{
    int largest = index;
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    if (left < actualSize && cmp(arr[largest], arr[left]))
    {
        largest = left;
    }
    if (right < actualSize && cmp(arr[largest], arr[right]))
    {
        largest = right;
    }
    if (largest != index)
    {
        T tmp = arr[index];
        arr[index] = arr[largest];
        arr[largest] = tmp;
        siftDown(largest);
    }
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::buildHeap()
{
    for (int i = actualSize / 2 - 1; i >= 0; --i)
    {
        siftDown(i);
    }
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::siftUp(int index)
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;
        if (parent >= 0 && (cmp(arr[index], arr[parent])))
            return;
        T tmp = arr[index];
        arr[index] = arr[parent];
        arr[parent] = tmp;
        index = parent;
    }
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::PrintForTest(std::ostream &output)
{
    for (int i = 0; i < size; ++i)
    {
        output << arr[i] << " ";
    }
    output << std::endl;
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::Print()
{
    for (int i = 0; i < actualSize; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T, typename Comparator>
int Heap<T, Comparator>::extractTop()
{
    int tmp = arr[0].get();
    arr[0].inc();
    if (arr[0].checked())
    {
        ArrayDesc tmp = arr[0];
        arr[0] = arr[actualSize - 1];
        arr[actualSize - 1] = tmp;
        --actualSize;
    }
    siftDown(0);
    return tmp;
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::grow()
{
    size *= 2;
    T *tmp = new T[size];
    for (int i = 0; i < actualSize; ++i)
    {
        tmp[i] = arr[i];
    }
    delete[] arr;
    arr = tmp;
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::add(const T &elem)
{
    if (actualSize == size - 1)
    {
        grow();
    }
    arr[actualSize++] = elem;
    siftUp(actualSize - 1);
}

// Основная часть
template <typename T, typename Comparator>
int *JustDoIt(Heap<T, Comparator> &heap, int finalSize)
{
    int *answer = new int[finalSize];
    int i = 0;
    while (heap.getActualSize() != 0)
    {
        answer[i++] = heap.extractTop();
    }
    return answer;
}

// Тесты

void doLogic(std::istream &in, std::ostream &out)
{
    int n = 0;
    in >> n;
    ArrayDesc *array = new ArrayDesc[n];
    for (int i = 0; i < n; ++i)
    {
        int k = 0;
        in >> k;
        int *arr = new int[k];
        for (int j = 0; j < k; ++j)
        {
            in >> arr[j];
        }
        ArrayDesc tmp(arr, k);
        array[i] = tmp;
    }
    Heap<ArrayDesc, ArrayDescComparator> heap(array, n);
    heap.PrintForTest(out);
}

void testLogic()
{
    {
        // Проверка на то, что строится правильная куча из 3 элементов
        std::stringstream in;
        in << "3 ";
        in << "1 ";
        in << "6 ";
        in << "2 ";
        in << "50 90 ";
        in << "3 ";
        in << "1 10 70 ";

        std::stringstream out;
        doLogic(in, out);
        std::cout << out.str();
        assert(out.str() == "[ 1 10 70 ] [ 50 90 ] [ 6 ] \n");
    }
    {
        // Проверка на то, что строится правильная куча из 4 элементов
        std::stringstream in;
        in << "4 ";
        in << "1 ";
        in << "6 ";
        in << "2 ";
        in << "50 90 ";
        in << "3 ";
        in << "1 10 70 ";
        in << "4 ";
        in << "0 10 23 44";

        std::stringstream out;
        doLogic(in, out);
        std::cout << out.str();
        assert(out.str() == "[ 0 10 23 44 ] [ 6 ] [ 1 10 70 ] [ 50 90 ] \n");
    }
    {
        // Проверка на то, что строится правильная куча из 6 элементов
        std::stringstream in;
        in << "6 ";
        in << "1 ";
        in << "6 ";
        in << "2 ";
        in << "50 90 ";
        in << "3 ";
        in << "1 10 70 ";
        in << "1 ";
        in << "5 ";
        in << "2 ";
        in << "44 99 ";
        in << "3 ";
        in << "4 12 66 ";

        std::stringstream out;
        doLogic(in, out);
        std::cout << out.str();
        assert(out.str() == "[ 1 10 70 ] [ 5 ] [ 4 12 66 ] [ 50 90 ] [ 44 99 ] [ 6 ] \n");
    }
    {
        // Проверка на то, что строится правильная куча из 8 элементов
        std::stringstream in;
        in << "6 ";
        in << "1 ";
        in << "6 ";
        in << "2 ";
        in << "50 90 ";
        in << "3 ";
        in << "1 10 70 ";
        in << "1 ";
        in << "5 ";
        in << "3 ";
        in << "4 12 66 ";
        in << "4 ";
        in << "22 33 44 99 ";
        in << "5 ";
        in << "2 7 12 66 75 ";
        in << "2 ";
        in << "44 99 ";

        std::stringstream out;
        doLogic(in, out);
        std::cout << out.str();
        assert(out.str() == "[ 1 10 70 ] [ 4 12 66 ] [ 6 ] [ 5 ] [ 50 90 ] [ 22 33 44 99 ] \n");
    }
    std::cout << "Test OK" << std::endl;
}

int main()
{
    // ввод
    // testLogic();
    int n = 0;
    std::cin >> n;
    // old but gold
    ArrayDesc *array = new ArrayDesc[n];
    int ansSize = 0;
    for (int i = 0; i < n; ++i)
    {
        int k = 0;
        std::cin >> k;
        ansSize += k;
        int *arr = new int[k];
        for (int j = 0; j < k; ++j)
        {
            std::cin >> arr[j];
        }
        ArrayDesc tmp(arr, k);
        array[i] = tmp;
    }
    Heap<ArrayDesc, ArrayDescComparator> heap(array, n);

    int *ans = JustDoIt(heap, ansSize);
    for (int i = 0; i < ansSize; ++i)
    {
        std::cout << ans[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}
