#include <iostream>
#include <vector>
#include <iterator>
#include "vector_use.cpp"

using namespace std;

int sort_op_counter = 0;

int parent(int idx)
{
    if (idx % 2)
        return idx / 2;
    else
        return (idx - 1) / 2;
}

int left(int idx)
{
    return 2 * idx + 1;
}

int right(int idx)
{
    return 2 * idx + 2;
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

namespace heapmax
{
    bool is_pyramid(vector<int> A, int idx)
    {
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

    int max_heapify(vector<int> &A, int i, int heap_size) // O(lgN)
    {
        sort_op_counter++;
        int l = left(i), r = right(i);
        int largest = i;
        if (l < heap_size && A[l] > A[largest])
            largest = l;
        if (r < heap_size && A[r] > A[largest])
            largest = r;
        if (largest != i)
        {
            swap(A[i], A[largest]);
            return max_heapify(A, largest, heap_size);
        }
        else
            return i;
    }

    void build_max_heap(vector<int> &A) // O(n)
    {
        for (int i = A.size() / 2 - 1; i >= 0; i--)
            max_heapify(A, i, A.size());
    }

    void heapsort(vector<int> &A) // O(N*lgN)
    {
        build_max_heap(A);

        for (int i = A.size() - 1; i >= 1; i--)
        {
            swap(A[0], A[i]);
            max_heapify(A, 0, i);
        }
    }

    class PriorityQueueMAX
    {
        vector<int> A;

    public:
        PriorityQueueMAX(vector<int> data)
        {
            for (auto it = data.begin(); it != data.end(); it++)
                A.push_back(*it);
            build_max_heap(A);
        }

        PriorityQueueMAX()
        {
            A = {};
        }

        int max() // O(1)
        {
            return A[0];
        }

        int extract_max() // O(lgN)
        {
            if (A.size() < 1)
                return -1;
            int max = A[0];
            A[0] = A[A.size() - 1];
            A.pop_back();
            max_heapify(A, 0, A.size());
            return max;
        }

        void increase_key(int i, int key) // O(lgN)
        {
            if (key < A[i])
                return;
            A[i] = key;
            while (i > 0 && A[parent(i)] < A[i])
            {
                swap(A[i], A[parent(i)]);
                i = parent(i);
            }
        }

        void insert(int key) // O(lgN)
        {
            A.push_back(key);
            this->increase_key(A.size() - 1, key);
        }

        void h_delete(int i) // O(lgN)
        {
            if (i >= A.size())
                return;
            swap(A[i], A[A.size() - 1]);
            A.pop_back();
            max_heapify(A, i, A.size());
        }

        void show()
        {
            show_vector(A);
        }
    };

};

namespace heapmin
{
    bool is_pyramid(vector<int> A, int idx)
    {
        bool left_i = true, right_i = true;
        if (left(idx) < A.size())
        {
            if (A[idx] <= A[left(idx)])
                left_i = is_pyramid(A, left(idx));
            else
                left_i = false;
        }
        if (right(idx) < A.size())
        {
            if (A[idx] <= A[right(idx)])
                right_i = is_pyramid(A, right(idx));
            else
                right_i = false;
        }
        return left_i && right_i;
    }

    void min_heapify(vector<int> &A, int i, int heap_size) // O(lgN)
    {
        sort_op_counter++;
        int l = left(i), r = right(i);
        int smallest = i;
        if (l < heap_size && A[l] < A[smallest])
            smallest = l;
        if (r < heap_size && A[r] < A[smallest])
            smallest = r;
        if (smallest != i)
        {
            swap(A[i], A[smallest]);
            min_heapify(A, smallest, heap_size);
        }
    }

    void build_min_heap(vector<int> &A) // O(n)
    {
        for (int i = A.size() / 2 - 1; i >= 0; i--)
            min_heapify(A, i, A.size());
    }

    void heapsort(vector<int> &A) // O(N*lgN)
    {
        build_min_heap(A);

        for (int i = A.size() - 1; i >= 1; i--)
        {
            swap(A[0], A[i]);
            min_heapify(A, 0, i);
        }
    }

    class PriorityQueueMIN
    {
        vector<int> A;

    public:
        PriorityQueueMIN(vector<int> data)
        {
            for (auto it = data.begin(); it != data.end(); it++)
                A.push_back(*it);
            build_min_heap(A);
        }

        int min()
        {
            return A[0];
        }

        int extract_min()
        {
            if (A.size() < 1)
                return -1;
            int min = A[0];
            A[0] = A[A.size() - 1];
            A.pop_back();
            min_heapify(A, 0, A.size());
            return min;
        }

        void decrease_key(int i, int key)
        {
            if (key > A[i])
                return;
            A[i] = key;
            while (i > 0 && A[parent(i)] > A[i])
            {
                swap(A[i], A[parent(i)]);
                i = parent(i);
            }
        }

        void insert(int key)
        {
            A.push_back(key);
            this->decrease_key(A.size() - 1, key);
        }

        void show()
        {
            show_vector(A);
        }
    };

};

namespace D_ary_pyramid
{
    // представлена невозрастающая пирамида
    int d = 4;

    int parent(int i)
    {
        return (i - 1) / d;
    }

    int child(int i, int k)
    {
        return d * i + k + 1;
    }

    bool is_pyramid(vector<int> A, int idx) // O(lgN / lgd)
    {
        bool result = true;

        for (int j = 0; j < d; j++)
            if (child(idx, j) < A.size())
            {
                if (A[idx] >= A[child(idx, j)])
                    result &= is_pyramid(A, child(idx, j));
                else
                    result = false;
            }
        return result;
    }

    int max_heapify(vector<int> &A, int i) // O(lgN / lgd)
    {
        sort_op_counter++;
        int largest = i;

        for (int j = 0; j < d; j++)
            if (child(i, j) < A.size() && A[child(i, j)] > A[largest])
                largest = child(i, j);

        if (largest != i)
        {
            swap(A[i], A[largest]);
            return max_heapify(A, largest);
        }
        else
            return i;
    }

    void build_max_heap(vector<int> &A) // O(n)
    {
        // беру избыточное число листьев, но это и не важно, поск они ниже порядком
        for (int i = A.size() / d; i >= 0; i--)
            max_heapify(A, i);
    }
};

int main(void)
{
    vector<int> B = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}, C = B;
    D_ary_pyramid::build_max_heap(B);

    show_vector(B);

    return 0;
}
