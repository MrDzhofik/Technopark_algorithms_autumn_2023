// Дано множество целых чисел из [0..10^9] размера n.
// Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:
// 10%  перцентиль
// медиана
// 90%  перцентиль

// Реализуйте стратегию выбора опорного элемента “случайный элемент”.
// Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <sstream>
#include <assert.h>

template <typename T>
void swap(T &f, T &s)
{
    T tmp = f;
    f = s;
    s = tmp;
};

template <class T>
struct DefaultComparator
{
    bool operator()(const T &l, const T &r) const
    {
        return l >= r;
    }
};

template <typename T, typename Comparator = DefaultComparator<T>>
T Partition(T *arr, int l, int r, Comparator cmp = Comparator())
{
    if (r - l + 1 == 0)
    {
        return 0;
    }
    int pivot_idx = l + rand() % (r - l + 1);
    T pivot = arr[pivot_idx];
    T tmp = arr[r];
    arr[r] = pivot;
    arr[pivot_idx] = tmp;
    int i = r - 1;
    int j = r - 1;
    while (1)
    {
        while (j >= l && cmp(arr[j], pivot))
        {
            --j;
        }
        if (i > j)
        {
            i = j;
        }
        while (i >= l && !cmp(arr[i], pivot))
        {
            --i;
        }
        if (i < l)
        {
            swap(arr[++j], arr[r]);
            return j;
        }
        swap(arr[i--], arr[j--]);
    }
}

template <typename T, typename Comparator = DefaultComparator<T>>
T kth_statistic(T *arr, int k, int l, int r, Comparator cmp = Comparator())
{
    int pivot_pos = Partition(arr, l, r, cmp);

    while (pivot_pos != k)
    {
        if (pivot_pos > k)
        {
            r = pivot_pos - 1;
            pivot_pos = Partition(arr, l, r, cmp);
        }
        else
        {
            l = pivot_pos + 1;
            pivot_pos = Partition(arr, l, r, cmp);
        }
    }
    return arr[pivot_pos];
}

void doLogic(std::istream &in, std::ostream &out)
{
    int n = 0;
    in >> n;
    int *array = new int[n];
    int ten = n * 0.1;
    int ninty = n * 0.9;
    if (n == 0)
    {
        array[0] = 0;
    }
    for (int i = 0; i <= n - 1; ++i)
    {
        in >> array[i];
    }
    int mid = n / 2;
    DefaultComparator<int> cmp;
    int ans1 = kth_statistic(array, ten, 0, n - 1, cmp);
    int ans2 = kth_statistic(array, mid, 0, n - 1, cmp);
    int ans3 = kth_statistic(array, ninty, 0, n - 1, cmp);
    out << ans1 << std::endl;
    out << ans2 << std::endl;
    out << ans3 << std::endl;
    delete[] array;
}

void testLogic()
{
    // Обычный случай
    {
        std::stringstream in;
        in << "10 ";
        in << "1 2 3 4 5 6 7 8 9 10 ";

        std::stringstream out;
        doLogic(in, out);
        assert(out.str() == "2\n6\n10\n");
    }

    // мало элементов
    {
        std::stringstream in;
        in << "3 ";
        in << "4 5 2 ";

        std::stringstream out;
        doLogic(in, out);
        assert(out.str() == "2\n4\n5\n");
    }
    // все элементы одинаковые
    {
        std::stringstream in;
        in << "15 ";
        in << "4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 ";

        std::stringstream out;
        doLogic(in, out);
        assert(out.str() == "4\n4\n4\n");
    }
    // много элементов
    {
        std::stringstream in;
        in << "40008 ";
        for (int i = 0; i < 20004; ++i)
        {
            in << "4 ";
        }

        std::stringstream out;
        doLogic(in, out);
        assert(out.str() == "0\n4\n4\n");
    }
    // пустой массив
    {
        std::stringstream in;
        in << "0 ";
        std::stringstream out;
        doLogic(in, out);
        assert(out.str() == "0\n0\n0\n");
    }
    // выбросы
    {
        std::stringstream in;
        in << "10 ";
        in << "100000 4728382 47294 3 8 4 -47385 -12894 13 -100000 ";
        std::stringstream out;
        doLogic(in, out);
        std::cout << out.str();
        assert(out.str() == "-47385\n8\n4728382\n");
    }
    std::cout << "Test OK" << std::endl;
}

int main()
{
    srand(unsigned(time(0)));
    // testLogic();
    int n = 0;
    std::cin >> n;
    int *array = new int[n];
    int ten = n * 0.1;
    int ninty = n * 0.9;
    if (n == 0)
    {
        array[0] = 0;
    }
    for (int i = 0; i <= n - 1; ++i)
    {
        std::cin >> array[i];
    }
    int mid = n / 2;
    DefaultComparator<int> cmp;
    int ans1 = kth_statistic(array, ten, 0, n - 1, cmp);
    int ans2 = kth_statistic(array, mid, 0, n - 1, cmp);
    int ans3 = kth_statistic(array, ninty, 0, n - 1, cmp);
    std::cout << ans1 << std::endl;
    std::cout << ans2 << std::endl;
    std::cout << ans3 << std::endl;
    delete[] array;
    return 0;
}