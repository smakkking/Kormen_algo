#include <vector>
#include <iostream>
using namespace std;

void show_vector(const vector<int> a)
{
    for (vector<int>::const_iterator it = a.begin(); it != a.end(); ++it)
        cout << *it << " ";
    cout << endl;
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

void merge_sort(vector<int> &A, int p, int r)
{
    if (p < r)
    {
        int q = (p + r) / 2;
        merge_sort(A, p, q);
        merge_sort(A, q + 1, r);
        merge(A, p, q, r);
    }
}

int main(void)
{
    vector<int> T = {3, 41, 52, 26, 38, 57, 9, 49};
    show_vector(T);
    std::cout << endl;
    merge_sort(T, 0, T.size() - 1);
    std::cout << endl;
    show_vector(T);
}