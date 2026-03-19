/**
 * 牛客周赛 Round 103
 * 
 * => E-新婚 ( @c 1700 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/114593/E
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=78623869 By huanhuanonly
 * 
 * @b Dfs on @a Trees
 * 
 * ----August 03, 2025 [20h:44m:04s]----
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

    std::string s;
    std::cin >> s;

    std::vector<std::vector<int>> e(n + 1);

    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        std::cin >> u >> v;

        e[u].push_back(v);
        e[v].push_back(u);
    }

    std::vector<bool> map((1 << 21) + 1);

    auto dfs = [&](const auto& self, int u, int fa, int x, int d) -> void
    {
        for (int i = 1; i <= 1 << 21; i <<= 1)
        {
            map[x & i - 1] = true;
        }

        for (int t = x, v = 0, i = 0; i < std::min(d, 21); t >>= 1, ++i)
        {
            v = v << 1 | (t & 1);
            map[v] = true;
        }

        for (int i : e[u] | std::views::filter([fa](int i) -> bool { return i != fa; }))
        {
            self(self, i, u, x << 1 | (s[i - 1] - '0') & (1 << 21) - 1, d + 1);
        }
    };

    dfs(dfs, 1, 0, s[0] - '0', 1);

    while (q--)
    {
        int x;
        std::cin >> x;

        if (map[x])
        {
            std::cout << "YES\n";
        }
        else
        {
            std::cout << "NO\n";
        }
    }

    return 0;
}