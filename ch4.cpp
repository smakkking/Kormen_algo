#include <iostream>
#include <vector>

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
             << summ;
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

Solve find_max_subarray(const vector<int> A, int low, int high) // O(N*lgN)
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

int main(void)
{
    vector<int> T = {4, 2, -10, -5, 5};

    find_max_subarray(T, 0, T.size() - 1).show();

    return 0;
}