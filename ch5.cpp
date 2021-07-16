#include <random>
#include <iostream>
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

int rand_ab(int a, int b)
{
    if (a > b)
        return -1;

    return a + rand() % (b - a + 1);
}

void randomize_in_place(vector<int> &A)
{
    srand(time(NULL));
    for (int i = 0; i < A.size(); i++)
        swap(A[i], A[rand_ab(i, A.size() - 1)]);
}

void show_vector(const vector<int> a)
{
    for (vector<int>::const_iterator it = a.begin(); it != a.end(); ++it)
        cout << *it << " ";
    cout << endl;
}

void task531(vector<int> &A)
{
    srand(time(NULL));
    for (int i = 0; i < A.size(); i++)
        swap(A[i], A[rand_ab(0, i)]);
}

int main()
{
    vector<int> T = {1, 2, 3, 4, 5};
    task531(T);
    show_vector(T);
}
