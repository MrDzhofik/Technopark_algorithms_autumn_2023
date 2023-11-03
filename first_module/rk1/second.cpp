#include <iostream>
#include <string>

class Stack
{
public:
    Stack()
    {
        arr = nullptr;
        size = 0;
        pos = 0;
    }
    Stack(int size)
    {
        size = size;
        arr = new char[size];
        pos = 0;
    };
    char get()
    {
        if (pos < 0)
        {
            return 1;
        }
        return arr[pos];
    }
    int pushBack(char sym);
    char popBack();

private:
    char *arr;
    int size;
    int pos;
};

int Stack::pushBack(char sym)
{
    arr[++pos] = sym;
    return 0;
}

char Stack::popBack()
{
    char tmp = arr[pos--];
    return tmp;
}

int main()
{
    std::string first = "";
    std::string second = "";
    std::cin >> first >> second;
    int idx_f = 0;
    int size_f = first.size();
    int size_s = second.size();
    int res = 0;
    Stack *stack = new Stack(size_f);
    for (int i = 0; i < size_s; ++i)
    {
        if (i > 0)
        {
            while (second[i] != stack->get())
            {
                stack->pushBack(first[idx_f++]);
                if (i > size_f)
                {
                    break;
                }
            }
        }
        else
        {
            stack->pushBack(first[idx_f++]);
        }
        if (i > 0 && stack->get() == second[i])
        {
            stack->popBack();
            ++res;
        }
    }
    if (res == size_f)
    {
        std::cout << "YES" << std::endl;
    }
    std::cout << (res == size_f ? "YES" : "NO") << std::endl;
    return 0;
}