#include <iostream>
#include <vector>

#include "ch11.h"

int h1(int k) {
    return k;
}

int main(void)
{
    QuadroOpenHashTable<int, std::string, 11> T(h1, 1, 3);

    std::string s1 = "sdgdgg", s2 = "sdgs4y75i65";
    T.insert(4, s1);
    T.show_table();
    

    return 0;
}