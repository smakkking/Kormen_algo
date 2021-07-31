#include <vector>
#include <random>
#include <iostream>

template <typename T>
void show_vector(const std::vector<T> a)
{
    for (auto it = a.begin(); it != a.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

int rand_ab(int a, int b)
{
    if (a > b)
        return -1;

    return a + rand() % (b - a + 1);
}