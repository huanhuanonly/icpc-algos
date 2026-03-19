/**
 * AtCoder Beginner Contest 441 (Promotion of Engineer Guild Fes)
 * 
 * => D - Paid Walk ( @c 400 )
 * 
 * -> https://atcoder.jp/contests/abc441/tasks/abc441_d
 * 
 * Submissions ~> https://atcoder.jp/contests/abc441/submissions/72530587 By huanhuanonly
 * 
 * @b Dfs-enumeration
 * 
 * ----January 17, 2026 [21h:51m:25s]----
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

    int n, m, l, s, t;
    std::cin >> n >> m >> l >> s >> t;

    std::vector<std::vector<std::pair<int, int>>> e(n + 1);

    for (int i = 0; i < m; ++i)
    {
        int u, v, c;
        std::cin >> u >> v >> c;

        e[u].emplace_back(v, c);
    }

    std::set<int> ans;

    auto dfs = [&](const auto& self, int u, int cnt, uint64 sum) -> void
    {
        if (cnt == l)
        {
            if (s <= sum and sum <= t)
            {
                ans.insert(u);
            }

            return;
        }
        else if (sum > t)
        {
            return;
        }

        for (const auto& i : e[u])
        {
            self(self, i.first, cnt + 1, sum + i.second);
        }
    };

    dfs(dfs, 1, 0, 0);

    for (const auto& i : ans)
    {
        std::cout << i << ' ';
    }

    std::cout.put('\n');

    return 0;
}