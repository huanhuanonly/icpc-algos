/**
 * Tokio Marine & Nichido Fire Insurance Programming Contest 2024 (AtCoder Beginner Contest 355)
 *
 * => E - Guess the Sum ( @c 500 )
 *
 * -> https://atcoder.jp/contests/abc355/tasks/abc355_e
 *
 * Submissions ~> https://atcoder.jp/contests/abc355/submissions/78173517 By huanhuanonly
 *
 * @b Interactive and @b Breadth-first-search
 *
 * ----August 08, 2026 [00h:45m:55s]----
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

    int n, l, r;
    std::cin >> n >> l >> r;

    constexpr int mod = 100;

    static auto query = [](int i, int j) -> int
    {
        std::cout << "? " << i << ' ' << j << std::endl;

        int result;
        std::cin >> result;

        return result % mod;
    };

    static auto answer = [](int s) -> void
    {
        std::cout << "! " << (s % mod + mod) % mod << std::endl;
    };

    std::vector<std::vector<std::tuple<int, int, int, int>>> e((1 << n) + 1);

    for (int i = 0; i <= n; ++i)
    {
        for (int j = 0; (1 << i) * (j + 1) <= (1 << n); ++j)
        {
            e[(1 << i) * j].emplace_back((1 << i) * (j + 1), i, j, +1);
            e[(1 << i) * (j + 1)].emplace_back((1 << i) * j, i, j, -1);
        }
    }

    std::vector<std::tuple<int, int, int, int>> last((1 << n) + 1);

    auto bfs = [&]() -> void
    {
        std::queue<int> que;
        que.push(l);

        std::vector<bool> vis((1 << n) + 1);
        vis[l] = true;

        while (not que.empty())
        {
            const int u = que.front();
            que.pop();

            for (const auto& [v, i, j, k] : e[u])
            {
                if (not vis[v])
                {
                    vis[v] = true;
                    que.push(v);
                    last[v] = {u, i, j, k};
                }
            }
        }
    };

    bfs();

    int sum = 0;

    for (int u = r + 1; u != l; )
    {
        const auto& [v, i, j, k] = last[u];
        sum += query(i, j) * k;
        u = v;
    }

    answer(sum);

    return 0;
}