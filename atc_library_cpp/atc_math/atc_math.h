#pragma once
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;
using lint = long long;

struct atc_math
{
    // @brief 約数列挙をする
    static vector<pair<long long, long long>> prime_factorize(long long n)  
    {  
        vector<pair<long long, long long>> res;  
  
        for (long long p = 2; p * p <= n; ++p)  
        {  
            if (n % p != 0)  
            {  
                continue;  
            }  
  
            int e = 0;  
            while (n % p == 0)  
            {  
                e++;  
                n /= p;  
            }  
  
            res.emplace_back(p, e);  
        }  
  
        if (n != 1)  
        {  
            res.emplace_back(n, 1);  
        }  
        return res;  
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
    static lint gcd(const lint a, const lint b)
    {
        if (b == 0) return a;
        return gcd(b, a % b);
    }

    static lint lcm(const lint a, const lint b)
    {
        return a / gcd(a, b) * b;
    }

    // @brief 素数判定用ベクタをエラトステネスの篩を利用して作成する
    static vector<bool> make_eratosthenes(const long long n)
    {
        vector<bool> is_prime(n + 1, true);
 
        is_prime[0] = is_prime[1] = false;
 
        for (long long p = 2; p <= n / 2; p++)
        {
            if (!is_prime[p]) continue;
 
            for (long long q = p * 2; q <= n; q += p)
            {
                is_prime[q] = false;
            }
        }
 
        return is_prime;
    }
};
