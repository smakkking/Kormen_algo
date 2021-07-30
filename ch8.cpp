#include "vector_use.cpp"
#include <vector>
#include <iostream>

using namespace std;

void counting_sort(vector<int> &A, int k)
{
    vector<int> B(A.size());
    vector<int> C(k + 1);

    for (int i = 0; i <= k; i++)
        C[i] = 0;

    for (int j = 0; j < A.size(); j++)
        C[A[j]]++;

    for (int i = 1; i <= k; i++)
        C[i] += C[i - 1];

    for (int j = A.size() - 1; j >= 0; j--)
        B[--C[A[j]]] = A[j];

    for (int i = 0; i < A.size(); i++)
        A[i] = B[i];
}

class In
{
    int k;
    int *C;

public:
    In(vector<int> A, int m_k) // O(n + k)
    {
        k = m_k;
        C = new int[k + 1];

        for (int i = 0; i <= k; i++)
            C[i] = 0;
        for (int j = 0; j < A.size(); j++)
            C[A[j]]++;
        for (int i = 1; i <= k; i++)
            C[i] += C[i - 1];
    }
    int how_much_in_ab(int a, int b) // O(1)
    {
        int high, low;
        low = (a <= 0) ? 0 : C[a - 1];
        high = (b >= k) ? C[k] : C[b];
        return high - low;
    }
    ~In()
    {
        delete[] C;
    }
};

namespace radx_sort
{
    const int d = 32, k = 1;

    int get_i_digit(int x, int i)
    {
        return (x >> i) % 2;
    }
    void state_sort(vector<int> &A, int i) // O(n + k)
    {
        vector<int> B(A.size());
        vector<int> C(k + 1);

        for (int i = 0; i <= k; i++)
            C[i] = 0;

        for (int j = 0; j < A.size(); j++)
            C[get_i_digit(A[j], i)]++;

        for (int i = 1; i <= k; i++)
            C[i] += C[i - 1];

        for (int j = A.size() - 1; j >= 0; j--)
            B[--C[get_i_digit(A[j], i)]] = A[j];

        for (int i = 0; i < A.size(); i++)
            A[i] = B[i];
    }
    void sort(vector<int> &A)
    {
        for (int i = 0; i < d; i++)
            state_sort(A, i);
    }
};

int main(void)
{
    vector<int> T = {0, 4, 7, 145689, 3, 2, 3, 5, 1, 2, 2};
    radx_sort::sort(T);
    show_vector(T);
    return 0;
}