/**
 * AtCoder Beginner Contest 473
 *
 * => D - Coefficient Stair ( @c 400 )
 *
 * -> https://atcoder.jp/contests/abc473/tasks/abc473_d
 *
 * Submissions ~> https://atcoder.jp/contests/abc473/submissions/78857284 By huanhuanonly
 *
 * @b Dfs-enumeration
 *
 * ----August 31, 2026 [10h:28m:08s]----
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

    int n, k;
    std::cin >> n >> k;

    std::vector<int> que(n + 1);

    auto dfs = [&](const auto& self, int pos, int sum) -> void
    {
        if (pos == n + 1)
        {
            if (sum == k)
            {
                for (int i = 1; i <= n; ++i)
                {
                    std::cout << que[i] << " \n"[i == n];
                }
            }

            return;
        }

        if (pos < n)
        {
            for (int i = 0; sum + i * pos <= k; ++i)
            {
                que[pos] = i;
                self(self, pos + 1, sum + i * pos);
            }
        }
        else if ((k - sum) % n == 0)
        {
            que[pos] = (k - sum) / n;
            self(self, pos + 1, k);
        }

        que[pos] = 0;
    };

    dfs(dfs, 1, 0);

    return 0;
}