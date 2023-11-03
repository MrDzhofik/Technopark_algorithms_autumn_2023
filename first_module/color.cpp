// На числовой прямой окрасили N отрезков. Известны координаты левого и правого концов каждого отрезка (Li и Ri).
// Найти сумму длин частей числовой прямой, окрашенных ровно в один слой.

#include <iostream>

// Структуры данных

template <class T>
struct DefaultComparator
{
    bool operator()(const T &l, const T &r) const
    {
        return l < r;
    }
};

struct StartFinish
{
    int coord;
    short start;

    StartFinish()
    {
        coord = 0;
        start = 0;
    }
    StartFinish(int x, short y)
    {
        coord = x;
        start = y;
    }
};

std::ostream &operator<<(std::ostream &output, StartFinish elem)
{
    output << "( " << elem.coord << " " << elem.start << " ) ";
    return output;
}

struct StartFinishComparator
{
    bool operator()(const StartFinish &l, const StartFinish &r) const
    {
        return l.coord < r.coord;
    }
};

// Сортировка

template <class T, class Comp = DefaultComparator<T>>
void merge(T *arr, int left, int mid, int right, Comp cmp = DefaultComparator<T>())
{
    int size1 = mid - left + 1;
    int size2 = right - mid;

    T *firstHalf = new T[size1];
    T *secondHalf = new T[size2];

    for (int i = 0; i < size1; i++)
    {
        firstHalf[i] = arr[left + i];
    }
    for (int i = 0; i < size2; i++)
    {
        secondHalf[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;

    while (i < size1 && j < size2)
    {
        if (cmp(firstHalf[i], secondHalf[j]))
        {
            arr[k] = firstHalf[i];
            i++;
        }
        else
        {
            arr[k] = secondHalf[j];
            j++;
        }
        k++;
    }

    while (i < size1)
    {
        arr[k] = firstHalf[i];
        i++;
        k++;
    }

    while (j < size2)
    {
        arr[k] = secondHalf[j];
        j++;
        k++;
    }
}

template <typename T, class Comp = DefaultComparator<T>>
void mergeSort(T *arr, int left, int right, Comp cmp = DefaultComparator<T>())
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid, cmp);
        mergeSort(arr, mid + 1, right, cmp);

        merge(arr, left, mid, right, cmp);
    }
}

// Основная часть
template <typename T, class Comp = DefaultComparator<T>>
int count_one_layer(T *arr, int size, Comp cmp = DefaultComparator<T>())
{
    mergeSort(arr, 0, size - 1, cmp);
    int answer = 0;
    int layer = 0;
    for (int i = 0; i < size; ++i)
    {
        if (layer == 1 && i != 0)
        {
            answer += (arr[i].coord - arr[i - 1].coord);
        }
        layer += arr[i].start;
    }
    return answer;
}

// Ввод, вызов функции, вывод

int main()
{
    int n = 0;
    std::cin >> n;
    n *= 2;
    StartFinish *arr = new StartFinish[n];

    for (int i = 0; i < n; ++i)
    {
        int start = 0, finish = 0;
        std::cin >> start >> finish;
        StartFinish first(start, 1);
        StartFinish second(finish, -1);
        arr[i++] = first;
        arr[i] = second;
    }

    StartFinishComparator cmp;

    std::cout << count_one_layer(arr, n, cmp) << std::endl;

    delete[] arr;

    return 0;
}