#pragma once
#include <vector>

using namespace std;
using graph = vector<vector<int>>;

namespace acl_library_graph
{
    int n = 200000;
    bool is_seen[n + 10];
    graph g(n);

    struct dfs
    {
        // @brief seenを書き換えながらDFSをする
        // @param g: graph, seen[]: 探索済みかどうか, vertex: 頂点
        static void dfs_basic(const int v)
        {
            is_seen[v] = true;

            for (const int nv : g[v])
            {
                if (is_seen[nv]) continue;
                dfs_basic(nv);
            }
        }

        // @brief colorを2色で書き換えながらDFSをする
        // @param g: graph, colors[]: 色(-1: 未探索, 0: 白, 1: 黒)
        static void dfs_color(const graph& g, int colors[], const int vert, const int color)
        {
            colors[vert] = color;

            for (const int next_v : g[vert])
            {
                if (colors[next_v] != -1)
                {
                    if (colors[next_v] == color)
                    {
                        //res = false;
                    }

                    continue;
                }

                dfs_color(g, colors, next_v, 1 - color);
            }
        }
    };
}
