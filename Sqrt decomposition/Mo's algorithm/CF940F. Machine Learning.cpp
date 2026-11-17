/**
 * Codeforces Round 466 (Div. 2)
 *
 * => F. Machine Learning ( @c 2600 )
 *
 * -> https://codeforces.com/contest/940/problem/F
 *
 * Submissions ~> https://codeforces.com/contest/940/submission/342150934 By huanhuanonly
 *
 * @b Mo's-algorithm ( @a with-updates )
 *
 * ----October 06, 2025 [11h:39m:48s]----
*/

#include <bits/stdc++.h>

using int8 = signed char;
using int16 = short;
using int32 = int;
using int64 = long long;

using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;

#ifdef __GNUC__
using int128 = __int128;
using uint128 = unsigned __int128;
#endif

using real32 = float;
using real64 = double;
using real128 = long double;

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int n, q;
    std::cin >> n >> q;

    std::vector<int> v(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> v[i];
    }

    auto s = v;

    auto $ = [&](int i) -> int
    {
        return std::ranges::lower_bound(s, i) - s.begin();
    };

    struct query
    {
        int l, r, t;
        int i;
    };

    std::vector<query> queries;
    queries.reserve(q);

    std::vector<std::pair<int, int>> ts(1);
    ts.reserve(q + 1);

    std::vector<int> ans(q, -1);

    for (int i = 0, opt; i < q; ++i)
    {
        std::cin >> opt;

        if (opt == 1)
        {
            int l, r;
            std::cin >> l >> r;

            queries.emplace_back(l, r, int(ts.size()) - 1, i);
        }
        else
        {
            int p, x;
            std::cin >> p >> x;

            ts.emplace_back(p, x);
            s.push_back(x);
        }
    }

    std::ranges::sort(s | std::views::drop(1));
    s.erase(std::ranges::unique(s | std::views::drop(1)).begin(), s.end());

    std::ranges::transform(v, v.begin(), $);
    std::ranges::transform(ts | std::views::values, (ts | std::views::values).begin(), $);


    const int block_size = std::pow(n, 2.0 / 3.0);

    std::ranges::sort(queries, [&](const auto& fv, const auto& sv) -> bool
    {
        if (int fb = (fv.l + block_size - 1) / block_size, sb = (sv.l + block_size - 1) / block_size; fb != sb)
        {
            return fb < sb;
        }
        else if (fb = (fv.r + block_size - 1) / block_size, sb = (sv.r + block_size - 1) / block_size; fb != sb)
        {
            return fb < sb;
        }
        else
        {
            return fv.t < sv.t;
        }
    });

    std::vector<int> cnt(s.size() + 1);
    std::vector<int> mex(s.size() + 2);

    mex[0] = std::numeric_limits<int>::max() / 2;

    int curmex = 1;

    auto add = [&](int value) -> void
    {
        if (--mex[cnt[value]] == 0)
        {
            curmex = std::min(curmex, cnt[value]);
        }

        ++cnt[value];

        if (mex[cnt[value]]++ == 0)
        {
            for (; mex[curmex]; ++curmex);
        }
    };

    auto remove = [&](int value) -> void
    {
        if (--mex[cnt[value]] == 0)
        {
            curmex = std::min(curmex, cnt[value]);
        }

        --cnt[value];

        if (mex[cnt[value]]++ == 0)
        {
            for (; mex[curmex]; ++curmex);
        }
    };

    for (int i = 0, l = 1, r = 0, t = 0; i < queries.size(); ++i)
    {
        for (; l > queries[i].l; add(v[--l]));
        for (; r > queries[i].r; remove(v[r--]));

        for (; r < queries[i].r; add(v[++r]));
        for (; l < queries[i].l; remove(v[l++]));

        for (; t < queries[i].t; )
        {
            ++t;

            if (queries[i].l <= ts[t].first and ts[t].first <= queries[i].r)
            {
                add(ts[t].second);
                remove(v[ts[t].first]);
            }

            std::swap(ts[t].second, v[ts[t].first]);
        }

        for (; t > queries[i].t; )
        {
            if (queries[i].l <= ts[t].first and ts[t].first <= queries[i].r)
            {
                add(ts[t].second);
                remove(v[ts[t].first]);
            }

            std::swap(ts[t].second, v[ts[t].first]);

            --t;
        }

        ans[queries[i].i] = curmex;
    }

    for (int i = 0; i < q; ++i)
    {
        if (~ans[i])
        {
            std::cout << ans[i] << '\n';
        }
    }

    return 0;
}