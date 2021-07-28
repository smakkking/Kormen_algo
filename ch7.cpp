#include <iostream>
#include <vector>
#include "vector_use.cpp"

using namespace std;

int partition(vector<int> &A, int p, int r) // O(N)
{
    int x = A[r];
    int i = p - 1;
    for (int j = p; j < r; j++)
        // можно оставить и <= (для смены порядка сортировки поменять знак на противоположный)
        if (A[j] < x)
        {
            swap(A[++i], A[j]);
        }
    swap(A[++i], A[r]);
    return i;
}

int rand_partition(vector<int> &A, int p, int r)
{
    int i = rand_ab(p, r);
    swap(A[i], A[r]);
    return partition(A, p, r);
}

void rand_quicksort(vector<int> &A, int p, int r)
{
    if (p < r)
    {
        int q = rand_partition(A, p, r);
        rand_quicksort(A, p, q - 1);
        rand_quicksort(A, q + 1, r);
    }
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

int main(void)
{
    vector<int> T = {1, 1, 1, 1, 11, 1};
    cout << partition(T, 0, T.size() - 1) << endl;
    show_vector(T);
}