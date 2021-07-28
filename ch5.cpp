#include <random>
#include <iostream>
#include "vector_use.cpp"

using namespace std;

int generate_bern_01(std::mt19937 &rng, std::bernoulli_distribution &d, double p)
{
    const int N = 10000;
    int sum = 0;
    for (std::size_t i = 0; i < N; ++i)
        sum += d(rng);

    if (double(sum) / N < 1 - p)
        return 0;
    else
        return 1;
}

void task512()
{
    random_device rd{}; // use to seed the rng
    mt19937 rng{rd()};  // rng

    double p = 0.3; // probability
    bernoulli_distribution d(1 - p);

    int count0 = 0, count1 = 0;
    const int N_run = 1000;
    for (int i = 0; i < N_run; i++)
    {
        int s = generate_bern_01(rng, d, p);
        count0 += (s == 0);
        count1 += (s == 1);
    }

    cout << "0 - " << count0 << endl
         << "1 - " << count1 << endl;
}

void randomize_in_place(vector<int> &A)
{
    srand(time(NULL));
    for (int i = 0; i < A.size(); i++)
        swap(A[i], A[rand_ab(i, A.size() - 1)]);
}

void task531(vector<int> &A)
{
    srand(time(NULL));
    for (int i = 0; i < A.size(); i++)
        swap(A[i], A[rand_ab(0, i)]);
}

void morris_counter()
{
    random_device rd{}; // use to seed the rng
    mt19937 rng{rd()};  // rng

    int i = 0, counter = 0;
    const int N = 9;
    vector<int> V; //= {0, 1, 2, 4, 8, 16, 32, 64, 128, 256};

    for (int i = 0; i < N + 1; i++)
        V.push_back(100 * i);

    while (i < N)
    {
        bernoulli_distribution d(double(1) / (V[i + 1] - V[i]));
        i += d(rng);
        counter++;
    }

    cout << "real number - " << counter << endl
         << "imagine number - " << V[N] << endl;
}

int random_search(const vector<int> V, int value)
{
    vector<bool> checked(V.size());
    for (int i = 0; i < V.size(); i++)
        checked[i] = false;

    int all = 0;

    while (all < V.size())
    {
        int idx = rand_ab(0, V.size() - 1);
        if (V[idx] == value)
            return idx;
        else if (!checked[idx])
            all++;
        else
            checked[idx] = true;
    }
    return -1;
}

int main()
{
    return 0;
}
