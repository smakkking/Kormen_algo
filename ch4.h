#ifndef CH4
#define CH4

#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>

using namespace std;

class Solve
{
public:
    int left_idx, right_idx;
    int summ;

    Solve()
    {
        this->left_idx = this->right_idx = this->summ = 0;
    }
    Solve(int l, int r, int s)
    {
        this->left_idx = l;
        this->right_idx = r;
        this->summ = s;
    }
    void show()
    {
        cout << left_idx << endl
             << right_idx << endl
             << summ << endl;
    }
};

Solve find_max_crossing_subarray(const vector<int> A, int low, int mid, int high) // O(N)
{
    int left_sum = A[mid], right_sum = A[mid + 1];
    int left_idx = mid, right_idx = mid + 1;

    for (int i = mid - 1; i >= low; i--)
        if (left_sum + A[i] > left_sum)
        {
            left_sum += A[i];
            left_idx = i;
        }

    for (int i = mid + 2; i <= high; i++)
        if (right_sum + A[i] > right_sum)
        {
            right_sum += A[i];
            right_idx = i;
        }

    return Solve(left_idx, right_idx, left_sum + right_sum);
}

Solve find_max_subarray(const vector<int> &A, int low, int high) // O(N*lgN)
{
    if (low == high)
        return Solve(low, high, A[low]);
    else
    {
        int mid = (low + high) / 2;
        Solve s_left = find_max_subarray(A, low, mid);
        Solve s_right = find_max_subarray(A, mid + 1, high);
        Solve s_cross = find_max_crossing_subarray(A, low, mid, high);

        if (s_left.summ >= s_right.summ && s_left.summ >= s_cross.summ)
            return s_left;
        else if (s_right.summ >= s_left.summ && s_right.summ >= s_cross.summ)
            return s_right;
        else
            return s_cross;
    }
}

Solve brute_force_max_subarray(const vector<int> &A)
{
    int max_sum = A[0];
    int left_idx = 0, right_idx = 0;

    for (int i = 0; i < A.size(); i++)
        for (int j = i; j < A.size(); j++)
        {
            int sum = 0;
            for (int k = i; k <= j; k++)
                sum += A[k];

            if (sum > max_sum)
            {
                max_sum = sum;
                left_idx = i;
                right_idx = j;
            }
        }
    return Solve(left_idx, right_idx, max_sum);
}

Solve find_max_subarray_lineal(const vector<int> &A) // O(N)
{
    int max_sum = A[0];
    int left_idx = 0, right_idx = 0;

    int max_sum_lastI = A[0];
    int left_idx_lastI = 0, right_idx_lastI = 0;

    for (int i = 1; i < A.size(); i++)
    {
        if (0 > max_sum_lastI)
        {
            left_idx_lastI = i;
            max_sum_lastI = 0;
        }
        max_sum_lastI += A[i];
        if (max_sum < max_sum_lastI)
        {
            max_sum = max_sum_lastI;

            left_idx = left_idx_lastI;
            right_idx = i;
        }
    }

    return Solve(left_idx, right_idx, max_sum);
}

void task413()
{
    const int N = 1300;
    vector<int> T(N);
    for (int i = 1; i <= N; i++)
        T.push_back(i);

    int start, delta;

    start = clock();

    find_max_subarray(T, 0, T.size() - 1);

    delta = (clock() - start);
    cout << double(delta) / CLOCKS_PER_SEC << endl;

    start = clock();
    brute_force_max_subarray(T);

    delta = (clock() - start);
    cout << double(delta) / CLOCKS_PER_SEC << endl;
}

template <typename T>
class MATRIX
{
private:
    T **M; // матрица
    int m; // количество строк
    int n; // количество столбцов

    void mini_copy(MATRIX &A, int i_off, int j_off) const
    {
        for (int i = i_off; i < m / 2 + i_off; i++)
            for (int j = j_off; j < n / 2 + j_off; j++)
                A.SetMij(i - i_off, j - j_off, M[i][j]);
    }

    void mini_rev_copy(MATRIX &A, int i_off, int j_off)
    {
        for (int i = i_off; i < m / 2 + i_off; i++)
            for (int j = j_off; j < n / 2 + j_off; j++)
                M[i][j] = A.GetMij(i - i_off, j - j_off);
    }

public:
    MATRIX()
    {
        n = m = 0;
        M = nullptr; // необязательно
    }

    MATRIX(int _m, int _n)
    {
        m = _m;
        n = _n;

        // Выделить память для матрицы
        M = (T **)new T *[m];
        for (int i = 0; i < m; i++)
            M[i] = (T *)new T[n];

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                M[i][j] = 0;
    }

    MATRIX(const MATRIX &_M)
    {
        m = _M.m;
        n = _M.n;

        // Выделить память для M
        M = (T **)new T *[m];
        for (int i = 0; i < m; i++)
            M[i] = (T *)new T[n];

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                M[i][j] = _M.M[i][j];
    }

    void Print(const char *ObjName)
    {
        cout << "Object: " << ObjName << endl;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
                cout << M[i][j] << "\t";
            cout << endl;
        }
        cout << "---------------------" << endl
             << endl;
    }

    MATRIX operator=(const MATRIX &_M)
    {
        if (n > 0)
        {
            for (int i = 0; i < m; i++)
                delete[] M[i];
        }

        if (m > 0)
        {
            delete[] M;
        }

        m = _M.m;
        n = _M.n;

        // Выделить память для M опять
        M = (T **)new T *[m];
        for (int i = 0; i < m; i++)
            M[i] = (T *)new T[n];

        // заполнить значениями
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                M[i][j] = _M.M[i][j];
        return *this;
    }

    ~MATRIX()
    {
        if (n > 0)
        {
            // освободить выделенную память для каждой строки
            for (int i = 0; i < m; i++)
                delete[] M[i];
        }

        if (m > 0)
            delete[] M;
    }
    // методы доступа
    T GetMij(int i, int j) const
    {
        if ((m > 0) && (n > 0))
            return M[i][j];
        else
            return 0;
    }

    void SetMij(int i, int j, T value)
    {
        if ((i < 0) || (i >= m))
            return;
        if ((j < 0) || (j >= n))
            return;
        M[i][j] = value;
    }

    friend MATRIX operator-(const MATRIX A, const MATRIX B)
    {
        MATRIX result(A.m, A.n);

        for (int i = 0; i < A.m; i++)
            for (int j = 0; j < A.n; j++)
                result.SetMij(i, j, A.GetMij(i, j) - B.GetMij(i, j));

        return result;
    }

    friend MATRIX operator+(const MATRIX A, const MATRIX B)
    {
        MATRIX result(A.m, A.n);

        for (int i = 0; i < A.m; i++)
            for (int j = 0; j < A.n; j++)
                result.SetMij(i, j, A.GetMij(i, j) + B.GetMij(i, j));

        return result;
    }

    friend MATRIX operator*(const MATRIX A, const MATRIX B)
    {
        MATRIX result(A.m, B.n);

        for (int i = 0; i < A.m; i++)
            for (int j = 0; j < B.n; j++)
            {
                int sum = 0;
                for (int k = 0; k < A.n; k++)
                    sum += A[i][k] * B[k][j];
                result.SetMij(i, j, sum);
            }

        return result;
    }

    void split(MATRIX &A11, MATRIX &A12, MATRIX &A21, MATRIX &A22)
    {
        if (m != n)
            return;

        this->mini_copy(A11, 0, 0);
        this->mini_copy(A12, 0, n / 2);
        this->mini_copy(A21, m / 2, 0);
        this->mini_copy(A22, m / 2, n / 2);
    }

    void unit(MATRIX &A11, MATRIX &A12, MATRIX &A21, MATRIX &A22)
    {
        this->mini_rev_copy(A11, 0, 0);
        this->mini_rev_copy(A12, 0, n / 2);
        this->mini_rev_copy(A21, m / 2, 0);
        this->mini_rev_copy(A22, m / 2, n / 2);
    }
};

MATRIX<int> Shtrassen_rec(MATRIX<int> A, MATRIX<int> B, int N)
{
    if (N == 1)
    {
        MATRIX<int> C(1, 1);
        C.SetMij(0, 0, A.GetMij(0, 0) * B.GetMij(0, 0));
        return C;
    }

    MATRIX<int> A11(N / 2, N / 2), A12(N / 2, N / 2), A21(N / 2, N / 2), A22(N / 2, N / 2),
        B11(N / 2, N / 2), B12(N / 2, N / 2), B21(N / 2, N / 2), B22(N / 2, N / 2);

    A.split(A11, A12, A21, A22);
    B.split(B11, B12, B21, B22);

    MATRIX<int> S1 = B12 - B22,
                S2 = A11 + A12,
                S3 = A21 + A22,
                S4 = B21 - B11,
                S5 = A11 + A22,
                S6 = B11 + B22,
                S7 = A12 - A22,
                S8 = B21 + B22,
                S9 = A11 - A21,
                S10 = B11 + B12;

    MATRIX<int> P1 = Shtrassen_rec(A11, S1, N / 2),
                P2 = Shtrassen_rec(S2, B22, N / 2),
                P3 = Shtrassen_rec(S3, B11, N / 2),
                P4 = Shtrassen_rec(A22, S4, N / 2),
                P5 = Shtrassen_rec(S5, S6, N / 2),
                P6 = Shtrassen_rec(S7, S8, N / 2),
                P7 = Shtrassen_rec(S9, S10, N / 2);

    MATRIX<int> C11 = P5 + P4 - P2 + P6,
                C12 = P1 + P2,
                C21 = P3 + P4,
                C22 = P5 + P1 - P3 - P7;

    MATRIX<int> C(N, N);
    C.unit(C11, C12, C21, C22);

    return C;
}

MATRIX<int> Shtrassen(MATRIX<int> A, MATRIX<int> B, int N)
{
    int t2 = int(log2(N)) + 1;
    int N2 = 1 << t2;

    if (N2 / 2 != N)
    {
        MATRIX<int> A2(N2, N2), B2(N2, N2);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
            {
                A2.SetMij(i, j, A.GetMij(i, j));
                B2.SetMij(i, j, B.GetMij(i, j));
            }

        MATRIX<int> C2 = Shtrassen_rec(A2, B2, N2);
        MATRIX<int> C(N, N);

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
            {
                C.SetMij(i, j, C2.GetMij(i, j));
            }

        return C;
    }
    else
    {
        return Shtrassen_rec(A, B, N);
    }
}

#endif