#include <vector>
#include <random>
#include <iostream>

void show_vector(const std::vector<int> a)
{
    for (std::vector<int>::const_iterator it = a.begin(); it != a.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

int rand_ab(int a, int b)
{
    if (a > b)
        return -1;

    return a + rand() % (b - a + 1);
}