#include <iostream>
#include <vector>

using namespace std;
void show_vector(const vector<int> a)
{
    for (vector<int>::const_iterator it = a.begin(); it != a.end(); ++it)
        cout << *it << " ";
    cout << endl;
}

int parent(int idx)
{
    if (idx == 1 || idx == 2)
        return 0;
    else
        return idx / 2;
}

int left(int idx)
{
    return 2 * idx + 1;
}

int right(int idx)
{
    return 2 * idx + 2;
}

// для невозрастающих пирамид (для неубывающих поменять знаки сравнения на противоположные)
void max_heapify(vector<int> &A, int i) // O(lgN)
{
    int l = left(i), r = right(i);
    int largest = i;
    if (l < A.size() && A[l] > A[largest])
        largest = l;
    if (r < A.size() && A[r] > A[largest])
        largest = r;
    if (largest != i)
    {
        swap(A[i], A[largest]);
        max_heapify(A, largest);
    }
}

void build_max_heap(vector<int> &A) // O(n)
{
    for (int i = A.size() / 2 - 1; i >= 0; i--)
        max_heapify(A, i);
}

void task625(vector<int> &A, int i)
{
    int base_i = i, largest;
    while (true)
    {
        int l = left(base_i), r = right(base_i);
        largest = base_i;
        if (l < A.size() && A[l] > A[largest])
            largest = l;
        if (r < A.size() && A[r] > A[largest])
            largest = r;
        if (largest != base_i)
        {
            swap(A[i], A[largest]);
            base_i = largest;
        }
        else
            break;
    }
}

bool is_pyramid(vector<int> A, int idx)
{
    //cout << idx << endl;
    bool left_i = true, right_i = true;
    if (left(idx) < A.size())
    {
        if (A[idx] >= A[left(idx)])
            left_i = is_pyramid(A, left(idx));
        else
            left_i = false;
    }
    if (right(idx) < A.size())
    {
        if (A[idx] >= A[right(idx)])
            right_i = is_pyramid(A, right(idx));
        else
            right_i = false;
    }
    return left_i && right_i;
}

int main(void)
{
    vector<int> A = {5, 3, 17, 10, 84, 19, 6, 22, 9}, B = A;

    build_max_heap(A);
    show_vector(A);
    return 0;
}
