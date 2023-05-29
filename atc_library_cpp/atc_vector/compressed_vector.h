#pragma once
#include <atcoder/all>

using namespace std;
using namespace atcoder;

namespace atc_library_vector
{
    template <class T>
    vector<T> compressed_vector(const vector<T>& v)
    {
        vector<T> copy = v;
        sort(copy.begin(), copy.end());
        copy.erase(unique(copy.begin(), copy.end()), copy.end());

        vector<T> res(v.size());
        for (T i = 0; i < v.size(); ++i)
        {
            res[i] = lower_bound(copy.begin(), copy.end(), v[i]) - copy.begin();
        }

        return res;
    }
}
