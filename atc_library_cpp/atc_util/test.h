#pragma once
#include <chrono>
#include <random>

using namespace std;
using lint = long long;

namespace atc_library_util
{
    struct test
    {
        // @brief rondomテストケース生成例。この例では、1<=n<=10,1<=m<=100の制約で生成している
        static void make_random_example()
        {
            const int64_t seed = chrono::duration_cast<chrono::milliseconds>(
                chrono::system_clock::now().time_since_epoch()).count();
            mt19937_64 rnd(seed);

            uniform_int_distribution<lint> dist_n(1, 10);
            uniform_int_distribution<lint> dist_m(1, 100);

            const int n = dist_n(rnd);

            vector<int> a(n);
            for (int i = 0; i < n; i++) a[i] = dist_m(rnd);

            // cout << n << endl;
            // for (int i = 0; i < n; i++) cout << a[i] << " ";
            // cout << endl;
        }
    };
}
