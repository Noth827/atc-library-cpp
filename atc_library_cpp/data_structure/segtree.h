#pragma once
#include <atcoder/all>

using namespace std;
using namespace atcoder;

namespace atc_library_data_structure
{
    // @brief セグメント木
    // @original https://atcoder.github.io/ac-library/document_ja/segtree.html
    // @param S: モノイドの型 op: 結合則を満たす二項演算 e: 単位元
    template <class S, S (*op)(S, S), S (*e)()>
    struct seg_tree
    {
    public:
        seg_tree() : seg_tree(0)
        {
        }

        // @brief n要素で初期化する
        // @require 0 <= n <= 100000000
        explicit seg_tree(int n) : seg_tree(std::vector<S>(n, e()))
        {
            assert(n >= 0);
            assert(n <= 100000000);
        }

        explicit seg_tree(const std::vector<S>& v) : _n(int(v.size()))
        {
            log = internal::ceil_pow2(_n);
            size = 1 << log;
            d = std::vector<S>(2 * size, e());
            for (int i = 0; i < _n; i++) d[size + i] = v[i];
            for (int i = size - 1; i >= 1; i--)
            {
                update(i);
            }
        }

        // @order O(log n)
        void set(int p, S x)
        {
            assert(0 <= p && p < _n);
            p += size;
            d[p] = x;
            for (int i = 1; i <= log; i++) update(p >> i);
        }

        // @order O(1)
        S get(const int p)
        {
            assert(0 <= p && p < _n);
            return d[p + size];
        }

        // @order O(log n)
        S prod(int l, int r)
        {
            assert(0 <= l && l <= r && r <= _n);
            S sml = e(), smr = e();
            l += size;
            r += size;

            while (l < r)
            {
                if (l & 1) sml = op(sml, d[l++]);
                if (r & 1) smr = op(d[--r], smr);
                l >>= 1;
                r >>= 1;
            }
            return op(sml, smr);
        }

        S all_prod() { return d[1]; }

        // @brief seg tree上でupper_boundする
        // @order O(log n)
        template <bool (*f)(S)>
        int max_right(int l)
        {
            return max_right(l, [](S x) { return f(x); });
        }

        template <class F>
        int max_right(int l, F f)
        {
            assert(0 <= l && l <= _n);
            assert(f(e()));
            if (l == _n) return _n;
            l += size;
            S sm = e();
            do
            {
                while (l % 2 == 0) l >>= 1;
                if (!f(op(sm, d[l])))
                {
                    while (l < size)
                    {
                        l = (2 * l);
                        if (f(op(sm, d[l])))
                        {
                            sm = op(sm, d[l]);
                            l++;
                        }
                    }
                    return l - size;
                }
                sm = op(sm, d[l]);
                l++;
            }
            while ((l & -l) != l);
            return _n;
        }

        // @brief seg tree上でlower_boundする
        // @order O(log n)
        template <bool (*f)(S)>
        int min_left(int r)
        {
            return min_left(r, [](S x) { return f(x); });
        }

        template <class F>
        int min_left(int r, F f)
        {
            assert(0 <= r && r <= _n);
            assert(f(e()));
            if (r == 0) return 0;
            r += size;
            S sm = e();
            do
            {
                r--;
                while (r > 1 && (r % 2)) r >>= 1;
                if (!f(op(d[r], sm)))
                {
                    while (r < size)
                    {
                        r = (2 * r + 1);
                        if (f(op(d[r], sm)))
                        {
                            sm = op(d[r], sm);
                            r--;
                        }
                    }
                    return r + 1 - size;
                }
                sm = op(d[r], sm);
            }
            while ((r & -r) != r);
            return 0;
        }

    private:
        int _n, size, log;
        std::vector<S> d;

        void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    };
}
