/**
 * Codeforces Round 136 (Div. 1)
 *
 * => B. Little Elephant and Array ( @c 1800 )
 *
 * -> https://codeforces.com/contest/220/problem/B
 *
 * Submissions ~> http://codeforces.com/contest/220/submission/341946191 By huanhuanonly
 *
 * @b Mo's-algorithm
 *
 * ----October 05, 2025 [13h:41m:50s]----
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

    int n, m;
    std::cin >> n >> m;

    std::vector<int> v(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> v[i];
    }

    struct query
    {
        int l, r;
        int i, a;
    };

    std::vector<query> queries(m);

    for (int i = 0; i < m; ++i)
    {
        std::cin >> queries[i].l >> queries[i].r;
        queries[i].i = i;
    }

    const int block_size = std::sqrt(n);

    std::ranges::sort(queries, [&](const auto& fv, const auto& sv) -> bool
    {
        if (const int fb = (fv.l + block_size - 1) / block_size, sb = (sv.l + block_size - 1) / block_size; fb != sb)
        {
            return fb < sb;
        }
        else
        {
            return fv.r < sv.r;
        }
    });

    std::vector<int> cnt(n + 1);
    int sum = 0;

    auto add = [&](int value) -> void
    {
        if (value <= n)
        {
            if (cnt[value] == value)
            {
                --sum;
            }

            if (++cnt[value] == value)
            {
                ++sum;
            }
        }
    };

    auto remove = [&](int value) -> void
    {
        if (value <= n)
        {
            if (cnt[value] == value)
            {
                --sum;
            }

            if (--cnt[value] == value)
            {
                ++sum;
            }
        }
    };

    add(v[1]);

    for (int i = 0, l = 1, r = 1; i < m; ++i)
    {
        for (; l > queries[i].l; add(v[--l]));
        for (; r > queries[i].r; remove(v[r--]));

        for (; l < queries[i].l; remove(v[l++]));
        for (; r < queries[i].r; add(v[++r]));

        queries[i].a = sum;
    }

    std::ranges::sort(queries, {}, &query::i);

    for (int i = 0; i < m; ++i)
    {
        std::cout << queries[i].a << '\n';
    }

    return 0;
}