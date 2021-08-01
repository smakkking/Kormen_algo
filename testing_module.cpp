#include <iostream>
#include "ch9.h"

using namespace std;

int main(void)
{
    vector<int> T = {1, 2, 3, 4, 5, 6};
    cout << randomized_select(T, 0, T.size() - 1, 1);
    return 0;
}