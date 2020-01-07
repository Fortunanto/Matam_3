#include <iostream>

int main()
{
    int **a = new int *[10];
    for (size_t i = 0; i < 10; i++)
    {
        if(a[i])
        std::cout << a[i] << std::endl;
    }
}