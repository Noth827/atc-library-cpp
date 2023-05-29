#pragma once
#include <assert.h>
#include <iostream>
#include <vector>
#include <numeric>
#include <utility>

/// @brief 重み付き Union-Find 木
/// @original https://zenn.dev/reputeless/books/standard-cpp-for-competitive-programming/viewer/weighted-union-find
template <class T>
class weighted_union_find
{
public:
    explicit weighted_union_find(size_t n) : m_parents(n), m_sizes(n, 1), m_diff_weights(n)
    {
        assert(n >= 1);
        std::iota(m_parents.begin(), m_parents.end(), 0);
    }

    int root(int i)
    {
        if (m_parents[i] == i) return i;

        const int root = root(m_parents[i]);
        m_diff_weights[i] += m_diff_weights[m_parents[i]];
        return m_parents[i] = root;
    }

    /// @param a @param b index
    /// @param w bとaの重みの差分
    void merge(int a, int b, T w)
    {
        w += weight(a);
        w -= weight(b);

        a = root(a);
        b = root(b);

        if (a == b) return;

        // union by size (sizeが小さいほうが子）
        if (m_sizes[a] < m_sizes[b])
        {
            std::swap(a, b);
            w *= -1;
        }

        m_sizes[a] += m_sizes[b];
        m_parents[b] = a;
        m_diff_weights[b] = w;
    }

    /// @return (bの重み)-(aの重み)
    /// @remark aとbが同じグループでない場合は不定
    T diff(const int a, const int b)
    {
        return weight(b) - weight(a);
    }

    bool is_in_same_group(const int a, const int b)
    {
        return root(a) == root(b);
    }
    
    int size(const int i)
    {
        return m_sizes[root(i)];
    }

private:
    // m_parents[i] は i の 親,
    // root の場合は自身が親
    std::vector<int> m_parents;

    // グループの要素数 (root 用)
    // i が root のときのみ, m_sizes[i] はそのグループに属する要素数を表す
    std::vector<int> m_sizes;

    // 重み
    std::vector<T> m_diff_weights;

    T weight(int i)
    {
        root(i); // 経路圧縮
        return m_diff_weights[i];
    }
};
