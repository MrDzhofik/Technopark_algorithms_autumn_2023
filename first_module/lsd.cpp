// Дан массив неотрицательных целых 64-битных чисел. Количество чисел не больше 106.
//  Отсортировать массив методом поразрядной сортировки LSD по байт
#include <iostream>
#include <assert.h>
#include <sstream>

void counting_sort(unsigned long long *arr, int n, int raz)
{
    assert(arr != nullptr);
    assert(n > 0);

    int countBufSize = 256;
    int *countBuf = new int[countBufSize]();

    for (int j = 0; j < n; ++j)
    {
        int byte = (arr[j] >> (8 * raz)) & 0xff;
        countBuf[byte]++;
    }

    unsigned long long *tmpBuf = new unsigned long long[n]();

    for (int i = 1; i < countBufSize; i++)
    {
        countBuf[i] += countBuf[i - 1];
    }

    for (int i = n - 1; i >= 0; i--)
    {
        int countBufPos = (arr[i] >> (8 * raz)) & 0xff;
        countBuf[countBufPos]--;
        tmpBuf[countBuf[countBufPos]] = arr[i];
    }

    for (int i = 0; i < n; i++)
    {
        arr[i] = tmpBuf[i];
    }

    delete[] countBuf;
    delete[] tmpBuf;
}

void radix_lsd(unsigned long long *arr, int n)
{
    for (int i = 0; i < 8; ++i)
    {
        counting_sort(arr, n, i);
    }
}

void doLogic(std::istream &in, std::ostream &out)
{
    int n = 0;
    in >> n;

    unsigned long long *arr = new unsigned long long[n];
    for (int i = 0; i < n; i++)
    {
        in >> arr[i];
    }

    if (n == 0)
    {
        out << 0 << std::endl;
        return;
    }

    radix_lsd(arr, n);

    for (int i = 0; i < n; i++)
    {
        out << arr[i] << " ";
    }
    out << std::endl;

    delete[] arr;
}

void testLogic()
{
    {
        // Обычный случай
        std::stringstream in;
        in << "3 ";
        in << "4 10000 7";

        std::stringstream out;
        doLogic(in, out);
        assert(out.str() == "4 7 10000 \n");
    }
    {
        // Упорядоченный массив
        std::stringstream in;
        in << "5 ";
        in << "1 2 3 4 5 ";

        std::stringstream out;
        doLogic(in, out);
        assert(out.str() == "1 2 3 4 5 \n");
    }
    {
        // Упорядоченный массив в обратном порядке
        std::stringstream in;
        in << "5 ";
        in << "5 4 3 2 1";

        std::stringstream out;
        doLogic(in, out);
        assert(out.str() == "1 2 3 4 5 \n");
    }
    {
        // Дубликаты
        std::stringstream in;
        in << "10 ";
        in << "1 2 3 4 5 4 3 2 1 9 ";

        std::stringstream out;
        doLogic(in, out);
        assert(out.str() == "1 1 2 2 3 3 4 4 5 9 \n");
    }
    {
        // Степени 16
        std::stringstream in;
        in << "7 ";
        in << "1 1048576 16777216 256 65536 4096 16";

        std::stringstream out;
        doLogic(in, out);
        assert(out.str() == "1 16 256 4096 65536 1048576 16777216 \n");
    }
    std::cout << "Test OK" << std::endl;
}

int main()
{
    // testLogic();
    int n = 0;
    std::cin >> n;

    unsigned long long *arr = new unsigned long long[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }

    radix_lsd(arr, n);

    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    delete[] arr;
    return 0;
}
