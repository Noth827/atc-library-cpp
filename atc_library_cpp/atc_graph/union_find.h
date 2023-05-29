#pragma once
#include <atcoder/all>

using namespace std;

namespace atc_library_graph
{
    // @brief Union-Find木
    // @original https://github.com/atcoder/ac-library/blob/master/atcoder/dsu
    class union_find
    {
    public:
        explicit union_find(const int n) : _n(n), parent_or_size(n, -1)
        {
            assert(n >= 1);
        }

        // @brief aとbをマージする
        // @return マージ後の親
        int merge(const int a, const int b)
        {
            assert(0 <= a && a < _n);
            assert(0 <= b && b < _n);
            int x = root(a), y = root(b);
            if (x == y) return x;
            if (-parent_or_size[x] < -parent_or_size[y]) swap(x, y);
            parent_or_size[x] += parent_or_size[y];
            parent_or_size[y] = x;
            return x;
        }

        bool is_in_same_group(const int a, const int b)
        {
            assert(0 <= a && a < _n);
            assert(0 <= b && b < _n);
            return root(a) == root(b);
        }

        int root(const int a)
        {
            assert(0 <= a && a < _n);
            if (parent_or_size[a] < 0) return a;
            return parent_or_size[a] = root(parent_or_size[a]);
        }

        int size(const int a)
        {
            assert(0 <= a && a < _n);
            return -parent_or_size[root(a)];
        }

        // @brief グループ分けした結果を返す
        vector<vector<int>> groups()
        {
            vector<int> leader_buf(_n), group_size(_n);
            for (int i = 0; i < _n; i++)
            {
                leader_buf[i] = root(i);
                group_size[leader_buf[i]]++;
            }
            vector<vector<int>> result(_n);
            for (int i = 0; i < _n; i++)
            {
                result[i].reserve(group_size[i]);
            }
            for (int i = 0; i < _n; i++)
            {
                result[leader_buf[i]].push_back(i);
            }
            result.erase(
                remove_if(result.begin(), result.end(),
                          [&](const vector<int>& v) { return v.empty(); }),
                result.end());
            return result;
        }

        int group_count()
        {
            int count = 0;
            for (int i = 0; i < _n; i++)
            {
                if (i == root(i)) count++;
            }
            return count;
        }

    private:
        int _n;
        // root node: -1 * component size
        // otherwise: parent
        vector<int> parent_or_size;
    };
}
