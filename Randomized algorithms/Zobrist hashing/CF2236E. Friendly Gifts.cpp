/**
 * Codeforces Round 1103 (Div. 3)
 *
 * => E. Friendly Gifts ( @c 1700 )
 *
 * -> https://codeforces.com/contest/2236/problem/E
 *
 * Submissions ~> https://codeforces.com/contest/2236/submission/378438072 By huanhuanonly
 *
 * @b Zobrist-hashing
 * @b Monotonic-queue ( @a sliding-window )
 * @b Prefix-sum
 *
 * ----June 13, 2026 [01h:21m:58s]----
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

    int _;
    std::cin >> _;

    while (_--)
    {
        int n;
        std::cin >> n;

        static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

        std::vector<uint64> map(n + 1);
        std::vector<uint64> premap(n + 1);

        for (int i = 1; i <= n; ++i)
        {
            map[i] = rng();
            premap[i] = premap[i - 1] + map[i];
        }

        std::vector<uint64> v(n + 1);
        std::vector<uint64> pre(n + 1);

        for (int i = 1; i <= n; ++i)
        {
            std::cin >> v[i];
            pre[i] = pre[i - 1] + map[v[i]];
        }

        auto match = [&](int i, int len, int s) -> bool
        {
            if (s < 1 or s + len - 1 > n)
            {
                return false;
            }
            else
            {
                return pre[i + len - 1] - pre[i - 1] == premap[s + len - 1] - premap[s - 1];
            }
        };

        auto check = [&](int len) -> bool
        {
            std::deque<int> que;
            std::map<int, int> record;

            for (int i = 1; i <= n; ++i)
            {
                for (; not que.empty() and que.front() < i - len + 1; que.pop_front());
                for (; not que.empty() and v[i] < v[que.back()]; que.pop_back());
                que.push_back(i);

                if (i >= len)
                {
                    if (const uint64 min = v[que.front()]; match(i - len + 1, len, min))
                    {
                        record[min] = i;
                    }
                }
            }

            for (const auto& [key, value] : record)
            {
                if (auto it = record.find(key + len); it != record.end())
                {
                    if (std::abs(value - it->second) >= len)
                    {
                        return true;
                    }
                }
            }

            return false;
        };

        bool found = false;

        for (int len = n / 2; len >= 1; --len)
        {
            if (check(len))
            {
                found = true;
                std::cout << len << '\n';
                break;
            }
        }

        if (not found)
        {
            std::cout << 0 << '\n';
        }
    }

    return 0;
}