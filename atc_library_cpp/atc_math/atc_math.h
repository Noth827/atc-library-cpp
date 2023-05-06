#pragma once

using lint = long long;

struct atc_math
{
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
};
