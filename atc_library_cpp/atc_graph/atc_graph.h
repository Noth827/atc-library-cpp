#pragma once
#include <vector>

using namespace std;
using graph = vector<vector<int>>;

struct atc_graph
{
    // @brief seenを書き換えながらDFSをする
    // @param g: graph, seen[]: 探索済みかどうか, v: vertex, c: color
    static void dfs_basic(const graph& g, bool seen[], const int v)
    {
        seen[v] = true;

        for (const int next_v : g[v])
        {
            if (seen[next_v])
            {
                continue;
            }

            dfs_basic(g, seen, next_v);
        }
    }

    // @brief colorを2色で書き換えながらDFSをする
    // @param g: graph, colors[]: 色(-1: 未探索, 0: 白, 1: 黒), v: vertex, c: color
    static void dfs_color(const graph& g, int colors[], const int v, const int c)
    {
        colors[v] = c;

        for (const int next_v : g[v])
        {
            if (colors[next_v] != -1)
            {
                if (colors[next_v] == c)
                {
                    //res = false;
                }

                continue;
            }

            dfs_color(g, colors, next_v, 1 - c);
        }
    }
};
