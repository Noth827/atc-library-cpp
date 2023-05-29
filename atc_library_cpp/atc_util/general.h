#pragma once
#include <atcoder/all>

using namespace std;
using namespace atcoder;

using lint = long long;

struct atc_library_util
{
    // @brief pairをsecondを基準に比較する
    // @example sort(a.begin(), a.end(), compare_by_second);
    static bool compare_by_second(pair<lint, lint> a, pair<lint, lint> b)
    {
        if (a.second != b.second) return a.second < b.second;
        return a.first < b.first;
    }
};
