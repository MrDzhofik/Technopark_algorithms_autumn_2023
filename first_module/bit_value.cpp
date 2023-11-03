// Задача 1.2 Вернуть значение бита в числе N по его номеру K.

#include <iostream>
#include <assert.h>
#include <sstream>

void get_value(std::istream &in, std::ostream &out)
{
    unsigned int number = 0;
    unsigned short k = 0;
    in >> number >> k;
    number = number >> k;
    out << (number & 1) << std::endl;
}

void testLogic()
{
    {
        std::stringstream in;
        in << "1 0" << std::endl;

        std::stringstream out;
        get_value(in, out);
        assert(out.str() == "1\n");
    }
    {
        std::stringstream in;
        in << "1 1" << std::endl;

        std::stringstream out;
        get_value(in, out);
        assert(out.str() == "0\n");
    }
    {
        std::stringstream in;
        in << "31 4" << std::endl;

        std::stringstream out;
        get_value(in, out);
        assert(out.str() == "1\n");
    }
    {
        std::stringstream in;
        in << "4 2" << std::endl;

        std::stringstream out;
        get_value(in, out);
        assert(out.str() == "1\n");
    }
    {
        std::stringstream in;
        in << "32 1" << std::endl;

        std::stringstream out;
        get_value(in, out);
        assert(out.str() == "0\n");
    }

    std::cout << "OK" << std::endl;
}

int main()
{
    get_value(std::cin, std::cout);
    return 0;
}