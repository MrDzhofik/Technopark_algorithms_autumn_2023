// Дан отсортированный по возрастанию массив попарно различных целых чисел A[0..n-1].
//  На вход также подается некоторое целое число k. Необходимо вернуть индекс элемента k в массиве A,
// если он там присутствует, либо вернуть позицию, куда его следовало бы вставить, чтобы массив остался отсортированным.

// Требование: сложность O(logN)

#include <iostream>
#include <assert.h>

int bin_search(const int *arr, unsigned int size, const int num)
{
    int left = 0, right = size - 1, mid = 0;
    while (left <= right && arr[mid] != num)
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
    }
    if (right < 0)
    {
        right = 0;
    }
    if (num > arr[right])
    {
        ++mid;
    }
    return mid;
}

void testLogic()
{
    {
        int arr[4] = {1, 3, 5, 6};
        int a = bin_search(arr, 4, 5);
        assert(a == 2);
        std::cout << "1" << std::endl;
    }
    {
        int arr[4] = {1, 3, 5, 6};
        int a = bin_search(arr, 4, 2);
        assert(a == 1);
        std::cout << "2" << std::endl;
    }
    {
        int arr[8] = {0, 1, 2, 3, 4, 5, 6, 7};
        int a = bin_search(arr, 8, 9);
        assert(a == 8);
        std::cout << "3" << std::endl;
    }
    {
        int arr[8] = {0, 1, 2, 3, 4, 5, 6, 7};
        int a = bin_search(arr, 8, -1);
        assert(a == 0);
        std::cout << "4" << std::endl;
    }
    {
        int arr[8] = {0, 1, 2, 3, 4, 5, 6, 7};
        int a = bin_search(arr, 8, 3);
        assert(a == 3);
        std::cout << "5" << std::endl;
    }
    std::cout << "Test OK" << std::endl;
}

int main()
{
    testLogic();
    int n = 0, k = 0;
    std::cin >> n;
    int *arr = new int[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }
    std::cin >> k;
    int ex = 1;
    std::cout << bin_search(arr, n, k) << std::endl;
    delete[] arr;
    return 0;
}