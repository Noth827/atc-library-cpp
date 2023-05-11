#pragma once
#include <assert.h>
#include <queue>
#include <vector>

using namespace std;
using graph = vector<vector<int>>;
using lint = long long;

// 大抵size == nになる
vector<lint> min_dist;

namespace acl_library_graph
{
    struct bfs
    {
        // @brief 幅優先探索(BFS)をして最短距離をdistに格納する
        static void bfs_min_dist(const graph& g, bool seen[], const int vertex)
        {
            assert(g.size() >= min_dist.size() && "graphのサイズがdistのサイズより小さいです");

            queue<lint> que;
            que.push(vertex);
            min_dist[vertex] = 0;
            while (!que.empty())
            {
                const lint v = que.front();
                que.pop();

                for (const auto nv : g[v])
                {
                    if (min_dist[nv] != -1) continue;
                    min_dist[nv] = min_dist[v] + 1;
                    que.push(nv);
                }
            }
        }
    };
}
