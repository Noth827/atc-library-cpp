#pragma once
#include <atcoder/all>

using namespace std;
using namespace atcoder;

namespace atc_library_graph
{
    constexpr long long INF = 1LL << 60;

    // 辺の情報
    struct Edge
    {
        int to;
        long long cost;
    };

    using costed_graph = vector<vector<Edge>>;

    // { distance, from }
    using Pair = pair<long long, int>;

    // @remarks: distances は頂点数と同じサイズ, 全要素 INF で初期化しておく
    // @order: O((N + M) log N) (N: 頂点数, M: 辺数)
    void dijkstra(const costed_graph& graph, vector<long long>& distances, int start_index)
    {
        for (const long long distance : distances) assert(distance == INF);
    
        // 「現時点での最短距離, 頂点」の順に取り出す priority_queue
        priority_queue<Pair, vector<Pair>, greater<>> q;
        q.emplace(distances[start_index] = 0, start_index);

        while (!q.empty())
        {
            const long long distance = q.top().first;
            const int from = q.top().second;
            q.pop();

            // 最短距離でなければ処理しない
            if (distances[from] < distance)
            {
                continue;
            }

            for (const auto& edge : graph[from])
            {
                // to までの新しい距離
                const long long d = distances[from] + edge.cost;

                // d が現在の記録より小さければ更新
                if (d < distances[edge.to])
                {
                    q.emplace(distances[edge.to] = d, edge.to);
                }
            }
        }
    }
};
