/**
 * 牛客周赛 Round 161
 *
 * => F-小月的筹码 ( @c 1500 )
 *
 * -> https://ac.nowcoder.com/acm/contest/140235/F
 *
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=84711490 By huanhuanonly
 *
 * @b Meet-in-the-middle
 *
 * ----September 14, 2026 [09h:45m:29s]----
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

template<>
struct std::hash<std::pair<int, int>>
{
    uint64 operator()(const std::pair<int, int>& p) const noexcept
    {
        return uint64(p.first) << 32 | p.second;
    }
};

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int n, k, x;
    std::cin >> n >> k >> x;

    std::vector<int> v(n);

    for (int i = 0; i < n; ++i)
    {
        std::cin >> v[i];
    }

    constexpr uint64 mod = 1e9 + 7;
    uint64 ans = 0;

    std::unordered_map<std::pair<int, int>, uint64> record1, record2;

    auto dfs1 = [&](const auto& self, int u, int cnt, int sum) -> void
    {
        if (u >= n / 2)
        {
            ++record1[{cnt, sum}];
            return;
        }

        self(self, u + 1, cnt, sum);
        self(self, u + 1, cnt + 1, sum ^ v[u]);
    };

    auto dfs2 = [&](const auto& self, int u, int cnt, int sum) -> void
    {
        if (u < n / 2)
        {
            ++record2[{cnt, sum}];
            return;
        }

        self(self, u - 1, cnt, sum);
        self(self, u - 1, cnt + 1, sum ^ v[u]);
    };

    dfs1(dfs1, 0, 0, 0);
    dfs2(dfs2, n - 1, 0, 0);

    for (const auto& [key, value] : record1)
    {
        ans += value * record2[{k - key.first, key.second ^ x}];
        ans %= mod;
    }

    std::cout << ans << '\n';

    return 0;
}