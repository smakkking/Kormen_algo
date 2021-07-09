#include <vector>
#include <iostream>
using namespace std;

namespace basic_merge_sort
{
    void merge(vector<int> &A, int p, int q, int r)
    {
        int n1 = q - p + 1, n2 = r - q;
        vector<int> L(n1), R(n2);
        for (int i = 0; i < n1; i++)
            L[i] = A[p + i];
        for (int i = 0; i < n2; i++)
            R[i] = A[q + i + 1];

        int i = 0, j = 0;

        for (int k = p; k <= r; k++)
            if ((i < n1 && L[i] <= R[j]) || j >= n2)
                A[k] = L[i++];
            else
                A[k] = R[j++];
    }

    void sort(vector<int> &A, int p, int r)
    {
        if (p < r)
        {
            int q = (p + r) / 2;
            sort(A, p, q);
            sort(A, q + 1, r);
            merge(A, p, q, r);
        }
    }
};

namespace invertions
{
    int count = 0;

    void merge(vector<int> &A, int p, int q, int r)
    {
        int n1 = q - p + 1, n2 = r - q;
        vector<int> L(n1), R(n2);
        for (int i = 0; i < n1; i++)
            L[i] = A[p + i];
        for (int i = 0; i < n2; i++)
            R[i] = A[q + i + 1];

        int i = 0, j = 0;

        for (int k = p; k <= r; k++)
            if ((i < n1 && L[i] <= R[j]) || j >= n2)
            {
                count += abs(k - (p + i));
                A[k] = L[i++];
            }
            else
            {
                count += abs(q + j + 1 - k);
                A[k] = R[j++];
            }
        //cout << count;
    }

    void sort(vector<int> &A, int p, int r)
    {
        if (p < r)
        {
            int q = (p + r) / 2;
            sort(A, p, q);
            sort(A, q + 1, r);
            merge(A, p, q, r);
        }
    }

    int calc_inv(const vector<int> A)
    {
        vector<int> S = A;
        count = 0;
        sort(S, 0, S.size() - 1);
        return count / 2;
    }
}

void show_vector(const vector<int> a)
{
    for (vector<int>::const_iterator it = a.begin(); it != a.end(); ++it)
        cout << *it << " ";
    cout << endl
         << endl;
}

void insert_sort(vector<int> &A)
{
    for (int j = 1; j < A.size(); j++)
    {
        int key = A[j];
        int i = j - 1;
        // to change the order of sort invert the compare sign
        for (; i >= 0 && A[i] < key; i--)
            A[i + 1] = A[i];
        A[i + 1] = key;
    }
}

void choose_sort(vector<int> &A)
{
    for (int i = 0; i < A.size() - 1; i++)
    {
        int min = A[i], min_j = i;
        for (int j = i + 1; j < A.size(); j++)
            if (A[j] <= min)
            {
                min = A[j];
                min_j = j;
            }

        swap(A[i], A[min_j]);
    }
}

int lineal_search(const vector<int> A, int value)
{
    for (int i = 0; i < A.size(); i++)
        if (A[i] == value)
            return i;

    return 0;
}

int binary_find(const vector<int> A, int p, int r, int value)
{
    if (r < p)
        return -1;
    int q = (r + p) / 2;
    if (value > A[q])
        return binary_find(A, q + 1, r, value);
    if (value < A[q])
        return binary_find(A, p, q - 1, value);

    return q;
}

bool task237(vector<int> &A, int x)
{
    basic_merge_sort::sort(A, 0, A.size() - 1);
    for (int i = 0; i < A.size(); i++)
    {
        int j = binary_find(A, 0, A.size() - 1, x - A[i]);
        if (j != -1 && i != j)
            return true;
    }

    return false;
}

void bubble_sort(vector<int> &A)
{
    for (int i = 0; i < A.size() - 1; i++)
        for (int j = A.size() - 1; j >= i + 1; j--)
            if (A[j - 1] > A[j])
            {
                int tmp = A[j - 1];
                A[j - 1] = A[j];
                A[j] = tmp;
            }
}

int main(void)
{
    vector<int> T = {2, 3, 1, 6, 4, 5, 7};
    bubble_sort(T);
    show_vector(T);
    return 0;
}