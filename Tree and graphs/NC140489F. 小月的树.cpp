/**
 * 牛客周赛 Round 162
 *
 * => F-小月的树 ( @c 1700 )
 *
 * -> https://ac.nowcoder.com/acm/contest/140489/F
 *
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=84788321 By huanhuanonly
 *
 * @b Dfs on @a Trees
 *
 * ----September 23, 2026 [15h:01m:08s]----
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

    int n;
    std::cin >> n;

    std::string s;
    std::cin >> s;

    s.insert(s.begin(), ' ');

    std::vector<std::vector<int>> e(n + 1);

    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        std::cin >> u >> v;

        e[u].push_back(v);
        e[v].push_back(u);
    }

    std::vector<int> size(n + 1, 1), cntb(n + 1);

    auto build = [&](const auto& self, int u, int fa) -> void
    {
        cntb[u] = (s[u] == 'B');

        for (const auto& v : e[u])
        {
            if (v != fa)
            {
                self(self, v, u);

                size[u] += size[v];
                cntb[u] += cntb[v];
            }
        }
    };

    int ans = 0;

    auto dfs = [&](const auto& self, int u, int fa) -> bool
    {
        bool removed = false;
        int cnt = 0;

        for (const auto& v : e[u])
        {
            if (v != fa)
            {
                if (self(self, v, u) or s[u] != s[v])
                {
                    removed = true;
                    ++cnt;
                }
            }
        }

        if (cnt > 1)
        {
            ++ans;
            return true;
        }
        else if (cntb[1] - cntb[u] + (s[u] == 'B') == 0 or size[1] - size[u] + 1 == cntb[1] - cntb[u] + (s[u] == 'B'))
        {
            return false;
        }
        else
        {
            ans += removed;
            return removed;
        }
    };

    build(build, 1, 0);
    dfs(dfs, 1, 0);

    std::cout << std::max(ans, 1) << '\n';

    return 0;
}