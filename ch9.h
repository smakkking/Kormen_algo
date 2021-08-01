#ifndef CH9
#define CH9

#include <vector>
#include "vector_use.h"
#include "ch7.h"

using namespace std;

struct t_min_max
{
    int min, max;
};

t_min_max min_and_max(vector<int> A) // O(3*N/2)
{
    int min = A[0], max = A[0];
    for (int i = 1; i <= A.size() / 2; i++)
        if (A[i] > A[A.size() - i])
        {
            if (A[i] > max)
                max = A[i];
            if (A[A.size() - i] < min)
                min = A[A.size() - i];
        }
        else
        {
            if (A[A.size() - i] > max)
                max = A[A.size() - i];
            if (A[i] < min)
                min = A[i];
        }
    t_min_max S;
    S.min = min;
    S.max = max;
    return S;
}

int randomized_select(vector<int> A, int p, int r, int i) // O(N)
{
    if (p == r)
        return A[p];

    int q = rand_quick_sort::partition(A, p, r);
    int k = q - p + 1;

    if (i == k)
        return A[q];
    else if (i < k)
        return randomized_select(A, p, q - 1, i);
    else
        return randomized_select(A, q + 1, r, i - k);
}

#endif