/**
 * Codeforces Round 340 (Div. 2)
 *
 * => E. XOR and Favorite Number ( @c 2200 )
 *
 * -> https://codeforces.com/contest/617/problem/E
 *
 * Submissions ~> https://codeforces.com/contest/617/submission/341890948 By huanhuanonly
 *
 * @b Mo's-algorithm
 * @b Bitwise-XOR
 *
 * ----October 05, 2025 [01h:20m:24s]----
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

    constexpr int maxv = 1e7;

    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<int> v(n + 1);

    for (int& i : v | std::views::drop(1))
    {
        std::cin >> i;
    }

    std::partial_sum(v.begin(), v.end(), v.begin(), std::bit_xor());

    struct query
    {
        int l, r;
        int index;
        uint64 answer;
    };

    std::vector<query> queries(m);

    for (int i = 0; i < m; ++i)
    {
        std::cin >> queries[i].l >> queries[i].r;

        --queries[i].l;
        queries[i].index = i;
    }

    const int block_size = std::sqrt(n);

    std::ranges::sort(queries, [&](const auto& fv, const auto& sv) -> bool
    {
        if (const int lb = (fv.l + block_size - 1) / block_size, rb = (sv.l + block_size - 1) / block_size; lb != rb)
        {
            return lb < rb;
        }
        else
        {
            return fv.r < sv.r;
        }
    });

    std::vector<uint64> cnt(maxv + 1);
    uint64 sum = 0;

    auto add = [&](int value) -> void
    {
        sum += cnt[value ^ k];
        ++cnt[value];
    };

    auto remove = [&](int value) -> void
    {
        --cnt[value];
        sum -= cnt[value ^ k];
    };

    add(v[0]);

    for (int i = 0, l = 0, r = 0; i < m; ++i)
    {
        for (; l > queries[i].l; add(v[--l]));
        for (; r > queries[i].r; remove(v[r--]));

        for (; r < queries[i].r; add(v[++r]));
        for (; l < queries[i].l; remove(v[l++]));

        queries[i].answer = sum;
    }

    std::ranges::sort(queries, {}, &query::index);

    for (int i = 0; i < m; ++i)
    {
        std::cout << queries[i].answer << '\n';
    }

    return 0;
}