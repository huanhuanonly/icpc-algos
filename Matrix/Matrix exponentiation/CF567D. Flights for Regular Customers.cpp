/**
 * Codeforces Round 319 (Div. 1)
 *
 * => D. Flights for Regular Customers ( @c 2700 )
 *
 * -> https://codeforces.com/contest/576/problem/D
 *
 * Submissions ~> https://codeforces.com/contest/576/submission/384100753 By huanhuanonly
 *
 * @b Matrix-exponentiation ( @a bitset-optimization )
 * @b Breadth-first-search
 *
 * ----July 25, 2026 [00h:01m:10s]----
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
template<
    typename _Tp, std::unsigned_integral _Up, typename _Mp,
    typename _MulOp = std::multiplies<_Tp>, typename _ModOp = std::modulus<void>>
requires
    requires(_MulOp __op, _Tp __x) { { __op(__x, __x) } -> std::convertible_to<_Tp>; } and
    requires(_ModOp __op, _Tp __lhs, _Mp __rhs) { { __op(__lhs, __rhs) } -> std::convertible_to<_Tp>; }
[[nodiscard]] constexpr _Tp
binary_exponentiation(_Tp __lhs, _Up __rhs, _Mp __mod, _MulOp __mul_op = {}, _ModOp __mod_op = {})
{
    auto result = static_cast<_Tp>(1);

    for (__lhs = __mod_op(__lhs, __mod); __rhs; __lhs = __mod_op(__mul_op(__lhs, __lhs), __mod), __rhs >>= 1)
    {
        if (__rhs & 1)
        {
            result = __mod_op(__mul_op(result, __lhs), __mod);
        }
    }

    return result;
}

template<typename _Tp, std::unsigned_integral _Up, typename _MulOp = std::multiplies<_Tp>>
requires requires(_MulOp __op, _Tp __x) { { __op(__x, __x) } -> std::convertible_to<_Tp>; }
[[nodiscard]] constexpr _Tp
binary_exponentiation(_Tp __lhs, _Up __rhs, _MulOp __mul_op = {})
{
    auto result = static_cast<_Tp>(1);

    for (; __rhs; __lhs = __mul_op(__lhs, __lhs), __rhs >>= 1)
    {
        if (__rhs & 1)
        {
            result = __mul_op(result, __lhs);
        }
    }

    return result;
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

    int n, m;
    std::cin >> n >> m;

    std::map<uint32, std::vector<std::pair<int, int>>> e;

    for (int i = 0; i < m; ++i)
    {
        int u, v, d;
        std::cin >> u >> v >> d;

        e[d].emplace_back(--u, --v);
    }

    constexpr auto inf = std::numeric_limits<uint32>::max();

    auto bfs = [&](auto& que, const auto& g) -> uint32
    {
        std::vector<bool> vis(n);

        while (not que.empty())
        {
            const auto [u, dis] = que.front();
            que.pop();

            if (u == n - 1)
            {
                return dis;
            }

            if (vis[u])
            {
                continue;
            }

            vis[u] = true;

            for (auto i = g.m[u]._Find_first(); i < n; i = g.m[u]._Find_next(i))
            {
                que.emplace(i, dis + 1);
            }
        }

        return inf;
    };

    constexpr int maxn = 150;

    struct matrix
    {
        std::array<std::bitset<maxn>, maxn> m;

        matrix() = default;

        matrix(bool x)
        {
            for (int i = 0; i < maxn; ++i)
            {
                m[i].set(i, x);
            }
        }

        matrix operator*(const matrix& rhs) const
        {
            matrix res;

            for (int i = 0; i < maxn; ++i)
            {
                for (int k = 0; k < maxn; ++k)
                {
                    if (m[i].test(k))
                    {
                        res.m[i] |= rhs.m[k];
                    }
                }
            }

            return res;
        }
    };

    matrix f, g;
    f.m[0][0] = 1;

    uint32 ans = inf;
    std::queue<std::pair<int, uint32>> que;

    for (auto ld = 0; const auto& [d, set] : e)
    {
        f = f * binary_exponentiation(g, d - ld);
        ld = d;

        for (const auto& [u, v] : set)
        {
            g.m[u].set(v);
        }

        reinterpret_cast<std::deque<std::pair<int, uint32>>*>(&que)->clear();

        for (auto i = f.m[0]._Find_first(); i < n; i = f.m[0]._Find_next(i))
        {
            que.emplace(i, d);
        }

        ans = std::min(ans, bfs(que, g));
    }

    if (ans != inf)
    {
        std::cout << ans << '\n';
    }
    else
    {
        std::cout << "Impossible\n";
    }

    return 0;
}