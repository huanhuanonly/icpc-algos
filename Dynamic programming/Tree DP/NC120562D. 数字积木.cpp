/**
 * 2026牛客寒假算法基础集训营2
 * 
 * => D-数字积木 ( @c 2400 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/120562/D
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=82714781 By huanhuanonly
 * 
 * @b Tree-DP and @b Combinatorics ( @a contribution-technique )
 * 
 * ----March 12, 2026 [15h:25m:21s]----
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

inline namespace huanhuanonly {
    inline namespace math
{
template<typename _Tp>
[[nodiscard]] constexpr _Tp binary_exponentiation(_Tp __lhs, _Tp __rhs, _Tp __mod)
{
    auto res = static_cast<_Tp>(1);

    for (__lhs %= __mod; __rhs; __lhs = (__lhs * __lhs) % __mod, __rhs >>= 1)
    {
        if (__rhs & 1)
        {
            res = (res * __lhs) % __mod;
        }
    }

    return res;
}
}} // namespace huanhuanonly::math

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    constexpr uint64 mod = 1e9 + 7;

    struct mint64
    {
        uint64 value;
        int count_zero;

        mint64(uint64 x) : value(x % mod), count_zero(value == 0) { }

        operator uint64() const { return count_zero ? uint64{} : value; }

        mint64& operator*=(const mint64& rhs)
        {
            if (rhs.value)
            {
                (value *= rhs.value) %= mod;
            }

            count_zero += rhs.count_zero;

            return *this;
        }

        mint64& operator/=(const mint64& rhs)
        {
            if (rhs.value)
            {
                (value *= binary_exponentiation(rhs.value, mod - 2, mod)) %= mod;
            }

            count_zero -= rhs.count_zero;
            
            return *this;
        }
    };
    
    do
    {
        int n;
        std::cin >> n;

        std::vector<int> w(n + 1);

        for (int i = 1; i <= n; ++i)
        {
            std::cin >> w[i];
            ++w[i];
        }

        std::vector<std::vector<int>> e(n + 1);
        e[0].push_back(1);

        for (int i = 0; i < n - 1; ++i)
        {
            int u, v;
            std::cin >> u >> v;

            u = w[u];
            v = w[v];

            e[u].push_back(v);
            e[v].push_back(u);
        }

        std::vector<mint64> dp(n + 1, 1);
        std::vector<int> fa(n + 1);

        auto dfs = [&](const auto& self, int u) -> void
        {
            for (const auto& i : e[u] | std::views::filter([&](int i) -> bool { return i != fa[u]; }))
            {
                fa[i] = u;
                self(self, i);
                dp[u] *= dp[i] + 1;
            }
        };

        dfs(dfs, 0);

        std::vector<bool> vis(n + 1);
        vis[0] = true;

        mint64 product = dp[0];

        uint64 ans = 0;

        for (int x = 1; x <= n; ++x)
        {
            if (not vis[x])
            {
                std::vector<int> que;

                for (int u = x; not vis[u]; u = fa[u])
                {
                    vis[u] = true;
                    que.push_back(u);
                }
                
                product /= dp[fa[que.back()]];
                product *= dp[x];

                for (const auto& u : que | std::views::reverse)
                {
                    product *= dp[fa[u]] /= dp[u] + 1;
                }
            }

            (ans += product) %= mod;
        }

        std::cout << ans << '\n';

    } while (false);

    return 0;
}