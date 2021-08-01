#ifndef CH7
#define CH7

#include <iostream>
#include <vector>
#include "vector_use.h"

using namespace std;

namespace classic_quick_sort
{
    int partition(vector<int> &A, int p, int r) // O(N)
    {
        int x = A[r];
        int i = p - 1;
        for (int j = p; j < r; j++)
            // можно оставить и <= (для смены порядка сортировки поменять знак на противоположный)
            if (A[j] < x)
                swap(A[++i], A[j]);
        swap(A[++i], A[r]);
        return i;
    }
    void quicksort(vector<int> &A, int p, int r)
    {
        if (p < r)
        {
            int q = partition(A, p, r);
            quicksort(A, p, q - 1);
            quicksort(A, q + 1, r);
        }
    }
};

namespace rand_quick_sort
{
    int partition(vector<int> &A, int p, int r)
    {
        int i = rand_ab(p, r);
        swap(A[i], A[r]);
        return classic_quick_sort::partition(A, p, r);
    }
    void quicksort(vector<int> &A, int p, int r)
    {
        if (p < r)
        {
            int q = partition(A, p, r);
            quicksort(A, p, q - 1);
            quicksort(A, q + 1, r);
        }
    }
};

namespace hoare_quick_sort
{
    int partition(vector<int> &A, int p, int r)
    {
        int x = A[p];
        int i = p - 1, j = r + 1;
        while (true)
        {
            while (A[--j] > x)
                ;
            while (A[++i] < x)
                ;
            if (i < j)
                swap(A[i], A[j]);
            else
                return j;
        }
    }
    void quicksort(vector<int> &A, int p, int r)
    {
        if (p < r)
        {
            int q = partition(A, p, r);
            quicksort(A, p, q);
            quicksort(A, q + 1, r);
        }
    }
};

struct solve
{
    int q, t;
    void show()
    {
        cout << q << " " << t << endl;
    }
};

struct interval
{
    int a, b;
    interval(int m_a, int m_b)
    {
        a = m_a;
        b = m_b;
    }
    friend bool is_per(interval S1, interval S2)
    {
        return S2.b >= S1.a && S1.b >= S2.a;
    }
};

solve equal_partition(vector<interval> &A, int p, int r) // O(N)
{
    interval x = A[r];
    solve T;
    int i = p - 1;
    for (int j = p; j < r; j++)
        // можно оставить и <= (для смены порядка сортировки поменять знак на противоположный)
        if (A[j].a < x.a && !is_per(A[j], x))
            swap(A[++i], A[j]);
    swap(A[++i], A[r]);
    T.q = i;

    for (int j = T.q + 1; j <= r; j++)
        if (is_per(A[j], x))
            swap(A[++i], A[j]);
    T.t = i;

    return T;
}

void fuzzy_sort(vector<interval> &A, int p, int r)
{
    if (p < r)
    {
        solve S = equal_partition(A, p, r);
        fuzzy_sort(A, p, S.q - 1);
        fuzzy_sort(A, S.t + 1, r);
    }
}

#endif