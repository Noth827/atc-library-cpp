#pragma once
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;
using lint = long long;

namespace acl_library_math
{
    template <class T>
    bool chmin(T& a, T b) { return a > b ? (a = b, true) : false; }

    template <class T>
    bool chmax(T& a, T b) { return a < b ? (a = b, true) : false; }

    // @brief 約数列挙をする
    // @order O(sqrt(n))
    static vector<pair<lint, lint>> prime_factorize(lint n)
    {
        vector<pair<lint, lint>> res;

        for (lint p = 2; p * p <= n; ++p)
        {
            if (n % p != 0) continue;

            int e = 0;
            while (n % p == 0)
            {
                e++;
                n /= p;
            }

            res.emplace_back(p, e);
        }

        if (n != 1) res.emplace_back(n, 1);
        return res;
    }

    // @brief nまでの整数のうち、n=xyで表せるような(x,y)の個数を求める
    static vector<lint> counts_of_xy(const lint n)
    {
        vector<lint> num(n + 1, 0);
        for (lint x = 1; x <= n; x++)
        {
            for (lint y = 1; x * y <= n; y++)
            {
                num[x * y]++;
            }
        }
        return num;
    }

    // @brief 累乗を繰り返し二乗法を利用して計算する
    // @param a: base, b: exponent, mod: mod
    static lint power(const lint a, const lint b, const lint mod, const lint limit = 30)
    {
        lint p = a;
        lint res = 1;
        for (int i = 0; i < limit; i++)
        {
            const int divide = 1 << i;
            if (b & divide)
            {
                res *= p;
                res %= mod;
            }
            p *= p;
            p %= mod;
        }
        return res;
    }

    // @brief 最大公約数をユークリッドの互除法を利用して計算する
    // @order O(log max(a, b))
    static lint gcd(const lint a, const lint b)
    {
        if (b == 0) return a;
        return gcd(b, a % b);
    }

    // @brief 最小公倍数
    static lint lcm(const lint a, const lint b)
    {
        return a / gcd(a, b) * b;
    }

    // @brief 素数判定用ベクタをエラトステネスの篩を利用して作成する
    // @order O(n log log n)
    static vector<bool> make_eratosthenes(const lint n)
    {
        vector<bool> is_prime(n + 1, true);

        is_prime[0] = is_prime[1] = false;

        for (lint p = 2; p <= n / 2; p++)
        {
            if (!is_prime[p]) continue;

            for (lint q = p * 2; q <= n; q += p)
            {
                is_prime[q] = false;
            }
        }

        return is_prime;
    }

    // @brief フェルマーの小定理を利用して、逆元のmodを求める
    static lint get_division(const lint a, const lint b, const lint mod)
    {
        return a * power(b, mod - 2, mod) % mod;
    }

    // @brief nCr % modを求める
    static lint get_combination(const lint n, const lint r, const lint mod)
    {
        // 分子
        lint numerator = 1;
        for (int i = 1; i <= n; i++)
        {
            numerator *= i;
            numerator %= mod;
        }

        // 分母
        lint denominator = 1;
        for (int i = 1; i <= r; i++)
        {
            denominator *= i;
            denominator %= mod;
        }
        for (int i = 1; i <= n - r; i++)
        {
            denominator *= i;
            denominator %= mod;
        }

        return get_division(numerator, denominator, mod);
    }
}
