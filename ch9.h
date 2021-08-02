#ifndef CH9
#define CH9

#include <vector>
#include "vector_use.h"
#include "ch7.h"
#include "ch2.h"

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

int find_med(vector<int> A, int p_A, int r_A, vector<int> B, int p_B, int r_B) // O(lgN)
{
    int q_A = (p_A + r_A) / 2, q_B = (p_B + r_B) / 2;

    if (p_A == q_A) // O(1)
    {
        vector<int> T(4);
        int j = 0;
        for (int i = p_A; i <= r_A; i++)
            T[j++] = A[i];
        for (int i = p_B; i <= r_B; i++)
            T[j++] = B[i];

        insert_sort(T);
        return T[1];
    }

    if (A[q_A] < B[q_B])
        return find_med(A, q_A, r_A, B, p_B, q_B);
    else
        return find_med(A, p_A, q_A, B, q_B, r_B);
}

namespace weight_mediana
{
    template <typename T>
    struct weight_int
    {
        T value;
        double w;
    };

    template <typename T>
    T mediana(vector<weight_int<T>> A) // A - sorted by value
    {
        T sum_first = 0, sum_last = 0;
        for (int i = 0; i < A.size(); i++)
            sum_last += A[i].w;

        int result_idx = -1;

        for (int i = 0; i < A.size(); i++)
        {
            sum_last -= A[i].w;

            if (sum_first < 0.5 && sum_last <= 0.5)
                result_idx = i;

            sum_first += A[i].w;
        }

        return A[result_idx].value;
    }
};

#endif