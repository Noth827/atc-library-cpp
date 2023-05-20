#pragma once
#include <vector>
#include <atcoder/all>

using namespace std;
using lint = long long;

namespace atc_library_grid
{
    struct search
    {
        // 全方向
        vector<lint> dx_all = {-1, -1, -1, 0, 0, 1, 1, 1};
        vector<lint> dy_all = {-1, 0, 1, -1, 1, -1, 0, 1};

        // 縦、横、斜めのみ（下から上の方向のみ）
        vector<lint> dx_3 = {1, 0, 1};
        vector<lint> dy_3 = {0, 1, 1};

        // 縦、横のみ
        vector<lint> dx_4 = {-1, 0, 1, 0};
        vector<lint> dy_4 = {0, -1, 0, 1};


        // @brief 特定の文字列が存在する位置を判定
        // @return 位置のlist,なければ空list
        vector<pair<lint, lint>> find_string_in_grid(const vector<string>& s, const string& target,
                                                   const lint direction_amount = 8)
        {
            lint x = 0;
            lint y = 0;
            const lint h = s.size();
            const lint w = s[0].length();
            const lint target_length = target.length();

            vector<lint> dx;
            vector<lint> dy;

            switch (direction_amount)
            {
            case 3:
                dx = dx_3;
                dy = dy_3;
                break;
            case 4:
                dx = dx_4;
                dy = dy_4;
                break;
            case 8:
                dx = dx_all;
                dy = dy_all;
                break;
            default: break;
            }
            
            vector<pair<lint, lint>> res;
            for (int i = 0; i < h; i++)
            {
                for (int j = 0; j < w; j++)
                {
                    for (int k = 0; k < direction_amount; k++)
                    {
                        string cur;
                        for (int t = 0; t < target_length; t++)
                        {
                            x = i + t * dx[k];
                            y = j + t * dy[k];
                            if ((x < 0) || (x >= h) || (y < 0) || (y >= w)) break;
                            cur += s[x][y];
                        }

                        if (cur == target)
                        {
                            for (int t = 0; t < target_length; t++)
                            {
                                x = i + t * dx_all[k] + 1;
                                y = j + t * dy_all[k] + 1;
                                res.emplace_back(x, y);
                            }
                            return res;
                        }
                    }
                }
            }

            return {};
        }
    };
}
