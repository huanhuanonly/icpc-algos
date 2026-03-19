/**
 * AtCoder Beginner Contest 444
 * 
 * => E - Sparse Range ( @c 450 )
 * 
 * -> https://atcoder.jp/contests/abc444/tasks/abc444_e
 * 
 * Submissions ~> https://atcoder.jp/contests/abc444/submissions/73112047 By huanhuanonly
 * 
 * @b Combinatorics
 * 
 * ----February 07, 2026 [23h:13m:14s]----
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

    int64 n, d;
    std::cin >> n >> d;

    std::vector<int64> v(n);

    for (int i = 0; i < n; ++i)
    {
        std::cin >> v[i];
    }

    constexpr auto inf = std::numeric_limits<int64>::max() / 2;

    uint64 ans = 0;

    std::deque<int64> que;
    std::multiset<int64> set{-inf, inf};
    std::multiset<int64> min{inf + inf};

    for (int i = 0; i < n; ++i)
    {
        que.push_back(v[i]);

        auto it = set.insert(v[i]);

        min.extract(*std::next(it) - *std::prev(it));
        min.insert(*std::next(it) - *it);
        min.insert(*it - *std::prev(it));

        while (*min.begin() < d)
        {
            it = set.find(que.front());

            min.extract(*std::next(it) - *it);
            min.extract(*it - *std::prev(it));
            min.insert(*std::next(it) - *std::prev(it));

            set.erase(it);
            que.pop_front();
        }

        ans += que.size();
    }

    std::cout << ans;

    return 0;
}