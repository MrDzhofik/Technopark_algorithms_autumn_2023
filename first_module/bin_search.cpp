// 2_3. Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию.A[0..n - 1] и B[0..m - 1].n >> m.
// Найдите их пересечение.Требования : Время работы : O(m *log k), где k - позиция элемента B[m - 1] в массиве A..В
// процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска элемента B[i - 1].
// Внимание !В этой задаче для каждого B[i] сначала нужно определить диапазон
// для бинарного поиска размером порядка k с помощью экспоненциального поиска,
//     а потом уже в нем делать бинарный поиск.

#include <iostream>
#include <sstream>
#include <assert.h>

int binary_search(const int *arr, unsigned int size, const int num, int lef, int rig)
{
    int left = lef, right = rig, mid = 0;
    right = size < right ? size - 1 : right;
    while (left <= right)
    {
        mid = (left + right) / 2;
        if (arr[mid] > num)
        {
            right = mid - 1;
        }
        else if (arr[mid] < num)
        {
            left = mid + 1;
        }
        else
        {
            return arr[mid];
        }
    }
    return -1;
}

int exp_search(const int *arr, unsigned int size, const int num, int &ex)
{
    while (ex < size && arr[ex] < num)
    {
        ex *= 2;
    }
    return binary_search(arr, size, num, ex / 2, ex);
}

int iter_arr(const int *arr, const int *arr2, int size, int size2, int &ex)
{
    for (int i = 0; i < size2; i++)
    {
        int a = exp_search(arr, size, arr2[i], ex);
        if (a != -1)
        {
            std::cout << a << " ";
        }
    }
    return 0;
}

// void testLogic()
// {
// int a[5] = {1, 2, 3, 4, 5};
// assert(exp_search(a, 5, 4) == 3);
// int *arr = new int[10000];
// int size = 10000;
// for (int i = 0; i < size; i++)
// {
//     arr[i] = i + 1;
// }
// assert(exp_search(arr, size, 1) == 0);
// assert(exp_search(arr, size, 10000) == 9999);
// assert(exp_search(arr, size, 0) == -1);
// assert(exp_search(arr, 10000, 4673) == 4672);
// int *arr2 = new int[2000];
// int size2 = 2000;
// for (int i = 0, j = 0; i < size2; i++, j + 9999)
// {
//     arr2[i] = j + 1;
// }
// int ex = 1;
// std::stringstream out;
// iter_arr(arr, arr2, size, size2, ex, out);
// assert(out.str() == "1 10000 ");
//     std::cout << "Test OK" << std::endl;
// }

int main()
{
    int n = 0, m = 0;
    std::cin >> n;
    std::cin >> m;
    int *arr = new int[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }

    int *arr2 = new int[m];
    for (int i = 0; i < m; i++)
    {
        std::cin >> arr2[i];
    }
    int ex = 1;
    iter_arr(arr, arr2, n, m, ex);
    delete[] arr;
    delete[] arr2;
    return 0;
}
