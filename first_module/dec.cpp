// Реализовать дек с динамическим зацикленным буфером (на основе динамического массива).
// Требования: Дек должен быть реализован в виде класса.

#include <iostream>
#include <assert.h>
#include <sstream>

class Dec
{
public:
    Dec() : size(0)
    {
        arr = new int[8];
        arr[0] = 0;
        front = 3;
        end = front - 1;
        actual_size = 0;
    };
    Dec(int capacity)
    {
        size = 8;
        front = 3;
        end = front - 1;
        actual_size = 0;
        arr = new int[size];
    };
    ~Dec()
    {
        delete[] arr;
    };
    Dec(const Dec &another)
    {
        size = another.size;
        front = another.front;
        end = another.end;
        arr = new int[size];
        for (int i = 0; i < end + 1; ++i)
        {
            arr[i] = another.arr[i];
        }
    }
    Dec &operator=(const Dec &another)
    {
        delete[] arr;

        size = another.size;
        front = another.front;
        end = another.end;
        arr = new int[size];

        for (int i = 0; i < end + 1; ++i)
        {
            arr[i] = another.arr[i];
        }

        return *this;
    }
    void grow()
    {
        int curr_front = size / 2;
        int curr_end = curr_front + end - front;
        size *= 2;
        int *tmp = new int[size];
        for (int i = curr_front, j = front; i <= curr_end; ++i, ++j)
        {
            tmp[i] = arr[j];
        }
        front = curr_front;
        end = curr_end;
        delete[] arr;
        arr = tmp;
    }
    bool isEmpty()
    {
        return end < front;
    }
    int pushFront(int data)
    {
        if (front - 1 < 0)
        {
            grow();
        }
        arr[--front] = data;
        return data;
    };
    int pushBack(int data)
    {
        if (end + 1 == size)
        {
            grow();
        }
        arr[++end] = data;
        return data;
    };
    int popFront()
    {
        int del = arr[front++];
        return del;
    };
    int popBack()
    {
        assert(end >= front);
        int tmp = arr[end];
        arr[end] = 0;
        --end;
        return tmp;
    };

private:
    int size;
    int *arr;
    int front;
    int end;
    int actual_size;
};

void doLogic(std::istream &in, std::ostream &out)
{
    int n = 0;
    in >> n;
    Dec *dec = new Dec(n);
    bool result = true;
    for (int i = 0; i < n; ++i)
    {
        int command = 0;
        int data = 0;
        in >> command >> data;
        switch (command)
        {
        case 1:
            result = (result && data == dec->pushFront(data));
            break;
        case 2:
            if (dec->isEmpty())
            {
                result = (data == -1);
            }
            else
            {
                result = (result && data == dec->popFront());
            }
            break;
        case 3:
            result = (result && data == dec->pushBack(data));
            break;
        case 4:
            if (dec->isEmpty())
            {
                result = (data == -1);
            }
            else
            {
                result = (result && data == dec->popBack());
            }
            break;
        default:
            assert(false);
        }
    }
    out << (result ? "YES" : "NO") << std::endl;
}

void testLogic()
{
    {
        // Обычный случай
        std::stringstream in;
        in << "3 ";
        in << "1 20 ";
        in << "3 50 ";
        in << "4 50 ";

        std::stringstream out;
        doLogic(in, out);
        assert(out.str() == "YES\n");
    }

    {
        // Вызов удаления из пустой очереди
        std::stringstream in;
        in << "1 ";
        in << "2 -1 ";

        std::stringstream out;
        doLogic(in, out);
        assert(out.str() == "YES\n");
    }

    {
        // Полное удаление
        std::stringstream in;
        in << "4 ";
        in << "1 20 ";
        in << "3 50 ";
        in << "2 20 ";
        in << "4 50 ";

        std::stringstream out;
        doLogic(in, out);
        assert(out.str() == "YES\n");
    }

    {
        // Полное удаление из увеличенного массива
        std::stringstream in;
        in << "28 ";
        in << "1 20 ";
        for (int i = 0; i < 13; ++i)
        {
            in << "3 50 ";
        }
        in << "2 20 ";
        for (int i = 0; i < 13; ++i)
        {
            in << "4 50 ";
        }

        std::stringstream out;
        doLogic(in, out);
        assert(out.str() == "YES\n");
    }

    {
        // Добавление в начало и удаление из начала & Добавление в конец и удаление из конца
        std::stringstream in;
        in << "5 ";
        in << "3 50 ";
        in << "1 20 ";
        in << "3 66 ";
        in << "2 20 ";
        in << "2 50 ";
        in << "1 40 ";
        in << "2 40 ";
        in << "4 66 ";

        std::stringstream out;
        doLogic(in, out);
        assert(out.str() == "YES\n");
    }

    {
        // Добавление в конец и удаление из начала & Добавление в начало и удаление из конца
        std::stringstream in;
        in << "4 ";
        in << "3 20 ";
        in << "2 20 ";
        in << "3 66 ";
        in << "4 66 ";

        std::stringstream out;
        doLogic(in, out);
        assert(out.str() == "YES\n");
    }

    {
        // Отрицательный ответ
        std::stringstream in;
        in << "4 ";
        in << "3 20 ";
        in << "3 44 ";
        in << "3 66 ";
        in << "2 66 ";

        std::stringstream out;
        doLogic(in, out);
        assert(out.str() == "NO\n");
    }

    {
        // Огромное добавление
        std::stringstream in;
        in << "1003 ";
        in << "3 10 ";
        for (int i = 0; i < 1000; ++i)
        {
            in << "1 20 ";
        }
        in << "4 10 ";
        in << "2 20 ";

        std::stringstream out;
        doLogic(in, out);
        assert(out.str() == "YES\n");
    }
    {
        std::stringstream in;
        in << "18 ";
        in << "1 47 ";
        in << "3 78 ";
        in << "3 9 ";
        in << "1 172 ";
        in << "3 139 ";
        in << "4 139 ";
        in << "2 172 ";
        in << "1 142 ";
        in << "3 132 ";
        in << "1 77 ";
        in << "3 58 ";
        in << "1 86 ";
        in << "2 86 ";
        in << "3 73 ";
        in << "1 26 ";
        in << "3 3 ";
        in << "3 65 ";
        in << "3 81 ";
        std::stringstream out;
        doLogic(in, out);
        assert(out.str() == "YES\n");
    }

    std::cout << "Test OK" << std::endl;
}

int main()
{
    // testLogic();
    int n = 0;
    std::cin >> n;
    Dec *dec = new Dec(n);
    bool result = true;
    for (int i = 0; i < n; ++i)
    {
        int command = 0;
        int data = 0;
        std::cin >> command >> data;
        switch (command)
        {
        case 1:
            result = (result && data == dec->pushFront(data));
            break;
        case 2:
            if (dec->isEmpty())
            {
                result = (data == -1);
            }
            else
            {
                result = (result && data == dec->popFront());
            }
            break;
        case 3:
            result = (result && data == dec->pushBack(data));
            break;
        case 4:
            if (dec->isEmpty())
            {
                result = (data == -1);
            }
            else
            {
                result = (result && data == dec->popBack());
            }
            break;
        default:
            assert(false);
        }
    }
    std::cout << (result ? "YES" : "NO") << std::endl;
    return 0;
}