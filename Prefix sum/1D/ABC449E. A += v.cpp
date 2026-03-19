/**
 * AtCoder Beginner Contest 449
 * 
 * => E - A += v ( @c 475 )
 * 
 * -> https://atcoder.jp/contests/abc449/tasks/abc449_e
 * 
 * Submissions ~> https://atcoder.jp/contests/abc449/submissions/74135628 By huanhuanonly
 * 
 * @b Prefix-sum and @b Offline
 * 
 * ----March 15, 2026 [06h:36m:55s]----
*/

#include <bits/stdc++.h>
#include <bits/extc++.h>

namespace ext = __gnu_pbds;

using int8 = signed char;
using int16 = short;
using int32 = int;
using int64 = long long;

using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;

#if defined(__SIZEOF_INT128__)
using int128 = __int128;
using uint128 = unsigned __int128;
#endif

using real32 = float;
using real64 = double;

#if defined(__SIZEOF_FLOAT80__)
using real80 = __float80;
#endif

#if defined(__SIZEOF_FLOAT128__)
using real128 = __float128;
#endif

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    uint64 n, m;
    std::cin >> n >> m;

    std::vector<uint64> v(n + 1), cnt(m + 1);

    for (uint64 i = 1; i <= n; ++i)
    {
        std::cin >> v[i];
        ++cnt[v[i]];
    }
    
    int q;
    std::cin >> q;

    std::vector<uint64> ans(q);
    std::vector<std::pair<uint64, uint64>> queries(q);

    for (int i = 0; i < q; ++i)
    {
        std::cin >> queries[i].first;
        queries[i].second = i;
    }

    std::ranges::sort(queries);


    std::vector<std::pair<uint64, uint64>> vec(m);
    ext::tree<uint64, ext::null_type, std::ranges::less, ext::rb_tree_tag, ext::tree_order_statistics_node_update> set;

    for (uint64 i = 1; i <= m; ++i)
    {
        vec[i - 1] = {cnt[i], i};
    }

    std::ranges::sort(vec);

    std::vector<uint64> pre(m);
    pre[0] = n + 1;

    for (int i = 1; i < m; ++i)
    {
        pre[i] = pre[i - 1] + (vec[i].first - vec[i - 1].first) * i;
    }

    uint64 pos = 0;
    for (const auto& [x, id] : queries)
    {
        if (x <= n)
        {
            ans[id] = v[x];
        }
        else
        {
            for (; pos < m and pre[pos] <= x; set.insert(vec[pos].second), ++pos);
            
            ans[id] = *set.find_by_order((x - pre[pos - 1]) % pos);
        }
    }

    for (const auto& a : ans)
    {
        std::cout << a << '\n';
    }

    return 0;
}