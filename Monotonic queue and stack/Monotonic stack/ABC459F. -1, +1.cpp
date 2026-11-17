/**
 * Tokio Marine & Nichido Fire Insurance Programming Contest 2026 (AtCoder Beginner Contest 459)
 *
 * => F - -1, +1 ( @c 525 )
 *
 * -> https://atcoder.jp/contests/abc459/tasks/abc459_f
 *
 * Submissions ~> https://atcoder.jp/contests/abc459/submissions/76178038 By huanhuanonly
 *
 * @b Greedy
 * @b Monotonic-stack
 * @b Prefix-sum
 *
 * ----May 28, 2026 [11h:47m:37s]----
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

constexpr int64 div_floor(int64 lhs, int64 rhs)
{
    return lhs / rhs - (lhs % rhs and (lhs ^ rhs) < 0);
}

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

        constexpr int64 inf = std::numeric_limits<int>::max();

        std::vector<int64> v(n);

        for (int i = 0; i < n; ++i)
        {
            std::cin >> v[i];
            v[i] -= i;
        }

        auto a = v;

        std::stack<std::pair<int64, int64>> stack;
        stack.emplace(-inf, 1);

        for (int i = 0; i < n; ++i)
        {
            if (v[i] > stack.top().first)
            {
                stack.emplace(v[i], 1);
            }
            else if (v[i] == stack.top().first)
            {
                ++stack.top().second;
            }
            else
            {
                while (true)
                {
                    auto cur = stack.top();
                    stack.pop();

                    const int64 diff = cur.first - stack.top().first;

                    if (cur.first - diff >= v[i] + diff * cur.second)
                    {
                        v[i] += diff * cur.second;
                        stack.top().second += cur.second;
                    }
                    else
                    {
                        const auto k = div_floor(cur.first - v[i], cur.second + 1);

                        cur.first -= k;
                        v[i] += k * cur.second;

                        const auto cnt = cur.first - v[i];

                        v[i] += cnt;

                        if (cur.first - 1 == stack.top().first)
                        {
                            stack.top().second += cnt;
                        }
                        else if (cnt)
                        {
                            stack.emplace(cur.first - 1, cnt);
                        }

                        if (cur.second > cnt)
                        {
                            stack.emplace(cur.first, cur.second - cnt);
                        }

                        break;
                    }
                }

                if (v[i] == stack.top().first)
                {
                    ++stack.top().second;
                }
                else
                {
                    stack.emplace(v[i], 1);
                }
            }
        }

        std::vector<int64> b;
        b.reserve(n);

        for (const auto& [x, cnt] : *reinterpret_cast<const std::deque<std::pair<int64, int64>>*>(&stack) | std::views::drop(1))
        {
            for (int i = 0; i < cnt; ++i)
            {
                b.push_back(x);
            }
        }

        std::partial_sum(a.begin(), a.end(), a.begin());
        std::partial_sum(b.begin(), b.end(), b.begin());

        int64 ans = 0;

        for (int i = 0; i < n - 1; ++i)
        {
            ans += a[i] - b[i];
        }

        std::cout << ans << '\n';
    }

    return 0;
}