#include "vector_use.cpp"
#include <vector>
#include <iostream>
#include <math.h>

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

    int get_i_digit(int x, int i) // O(1)
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
    void sort(vector<int> &A) // O(d*(n + k))
    {
        for (int i = 0; i < d; i++)
            state_sort(A, i);
    }
};

namespace bucket_sort
{
    void insert_sort(vector<double> &A)
    {
        for (int j = 1; j < A.size(); j++)
        {
            double key = A[j];
            int i = j - 1;
            // to change the order of sort invert the compare sign
            for (; i >= 0 && A[i] > key; i--)
                A[i + 1] = A[i];
            A[i + 1] = key;
        }
    }

    void bucket_sort(vector<double> &A) // O(n)
    {
        int n = A.size();
        vector<double> *B = new vector<double>[n];

        for (int i = 0; i < n; i++)
            B[i] = {};

        for (int i = 0; i < n; i++)
            B[int(n * A[i])].push_back(A[i]);

        for (int i = 0; i < n; i++)
            insert_sort(B[i]);

        A = {};

        for (int i = 0; i < n; i++)
            for (int j = 0; j < B[i].size(); j++)
                A.push_back(B[i][j]);

        delete[] B;
    }
};

namespace task_8_3
{
    struct t
    {
        int array_pos, digit, num_pos;
    };

    void counting_sort_digit(vector<t> &A, int k)
    {
        vector<t> B(A.size());
        vector<int> C(k + 1);

        for (int i = 0; i <= k; i++)
            C[i] = 0;

        for (int j = 0; j < A.size(); j++)
            C[A[j].digit]++;

        for (int i = 1; i <= k; i++)
            C[i] += C[i - 1];

        for (int j = A.size() - 1; j >= 0; j--)
            B[--C[A[j].digit]] = A[j];

        for (int i = 0; i < A.size(); i++)
            A[i] = B[i];
    }

    void counting_sort_pos(vector<t> &A, int k)
    {
        vector<t> B(A.size());
        vector<int> C(k + 1);

        for (int i = 0; i <= k; i++)
            C[i] = 0;

        for (int j = 0; j < A.size(); j++)
            C[A[j].num_pos]++;

        for (int i = 1; i <= k; i++)
            C[i] += C[i - 1];

        for (int j = A.size() - 1; j >= 0; j--)
            B[--C[A[j].num_pos]] = A[j];

        for (int i = 0; i < A.size(); i++)
            A[i] = B[i];
    }

    void
    sort(vector<int> &A, int n) // n - all digits count
    {
        vector<t> S;
        for (int i = 0; i < A.size(); i++) // O(n)
        {
            int x = 0;
            while (A[i] > 0)
            {
                t R;
                R.array_pos = i;
                R.digit = A[i] % 10;
                R.num_pos = x++;
                S.push_back(R);
                A[i] /= 10;
            }
        }

        counting_sort_digit(S, 9); // O(n + 9) = O(n)
        counting_sort_pos(S, n);   // O(n + n) = O(n)

        vector<int> B(A.size());

        for (int i = 0; i < A.size(); i++) // O(n); becos A.size() <= n
        {
            B[i] = -1;
            A[i] = 0;
        }

        int x = A.size() - 1;
        for (int i = n - 1; i >= 0; i--) // O(n)
            if (B[S[i].array_pos] == -1)
            {
                B[S[i].array_pos] = x--;
            }

        for (int i = n - 1; i >= 0; i--)
            A[B[S[i].array_pos]] = A[B[S[i].array_pos]] * 10 + S[i].digit;
    }
};

int main(void)
{
    vector<int> T = {10, 9, 8, 7, 6, 5, 4};
    task_8_3::sort(T, 8);
    show_vector(T);
    return 0;
}