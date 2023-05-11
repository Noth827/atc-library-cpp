#pragma once
#include <vector>

using namespace std;
using graph = vector<vector<int>>;

namespace acl_library_graph
{
    struct dfs
    {
        // @brief seenを書き換えながらDFSをする
        // @param g: graph, seen[]: 探索済みかどうか, vertex: 頂点
        static void dfs_basic(const graph& g, bool is_seen[], const int vert)
        {
            is_seen[vert] = true;

            for (const int next_v : g[vert])
            {
                if (is_seen[next_v])
                {
                    continue;
                }

                dfs_basic(g, is_seen, next_v);
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
