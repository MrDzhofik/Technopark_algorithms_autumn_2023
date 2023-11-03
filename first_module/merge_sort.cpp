// #include <iostream>

// void MergeSort(int *arr, int aLen)
// {
//     if (aLen <= 1)
//     {
//         return;
//     }
//     int firstLen = aLen / 2;
//     int secondLen = aLen - firstLen;
//     MergeSort(arr, firstLen);
//     MergeSort(arr + firstLen, secondLen);
//     int *c = new int[aLen];
//     // Merge( a, firstLen, a + firstLen, secondLen, c );
//     // memcpy( a, c, sizeof( int ) * aLen );
//     // for (int i = 0; i < aLen; ++i)
//     // {
//     //     a[i] = c[i];
//     // }
//     delete[] c;
// }

// int main()
// {
//     int arr[9] = {99, 12, 324, 88, 85, 14, 9, 16, 22};
//     MergeSort(arr, 9);
//     for (int i = 0; i < 9; ++i)
//     {
//         std::cout << arr[i] << " ";
//     }
//     std::cout << std::endl;
//     return 0;
// }

#include <iostream>
#include <vector>

void merge(std::vector<int> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> leftArr(n1);
    std::vector<int> rightArr(n2);

    for (int i = 0; i < n1; i++)
    {
        leftArr[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++)
    {
        rightArr[i] = arr[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (leftArr[i] <= rightArr[j])
        {
            arr[k] = leftArr[i];
            i++;
        }
        else
        {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int> &arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

int main()
{
    std::vector<int> arr = {99, 12, 324, 88, 85, 14, 9, 16, 22};
    int arrSize = arr.size();

    std::cout << "Original array: ";
    for (int i = 0; i < arrSize; i++)
    {
        std::cout << arr[i] << " ";
    }

    mergeSort(arr, 0, arrSize - 1);

    std::cout << "\nSorted array: ";
    for (int i = 0; i < arrSize; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}