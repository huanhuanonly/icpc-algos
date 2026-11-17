/**
 * Yandex.Algorithm 2011: Round 2
 *
 * => D. Powerful array ( @c 2200 )
 *
 * -> https://codeforces.com/contest/86/problem/D
 *
 * Submissions ~> https://codeforces.com/contest/86/submission/342002442 By huanhuanonly
 *
 * @b Mo's-algorithm
 *
 * ----October 05, 2025 [19h:58m:19s]----
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

    std::vector<uint64> v(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> v[i];
    }

    struct query
    {
        int l, r;
        int i;
    };

    std::vector<query> queries(q);
    std::vector<uint64> ans(q);

    for (int i = 0; i < q; ++i)
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

    constexpr int maxv = 1e6;
    std::vector<uint64> cnt(maxv + 1);

    uint64 sum = 0;

    auto add = [&](uint64 value) -> void
    {
        sum -= cnt[value] * cnt[value] * value;
        ++cnt[value];
        sum += cnt[value] * cnt[value] * value;
    };

    auto remove = [&](uint64 value) -> void
    {
        sum -= cnt[value] * cnt[value] * value;
        --cnt[value];
        sum += cnt[value] * cnt[value] * value;
    };

    for (int i = 0, l = 1, r = 0; i < q; ++i)
    {
        for (; l > queries[i].l; add(v[--l]));
        for (; r > queries[i].r; remove(v[r--]));

        for (; l < queries[i].l; remove(v[l++]));
        for (; r < queries[i].r; add(v[++r]));

        ans[queries[i].i] = sum;
    }

    for (int i = 0; i < q; ++i)
    {
        std::cout << ans[i] << '\n';
    }

    return 0;
}