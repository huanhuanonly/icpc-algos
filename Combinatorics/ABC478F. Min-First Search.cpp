/**
 * AtCoder Beginner Contest 478
 *
 * => F - Min-First Search ( @c 525 )
 *
 * -> https://atcoder.jp/contests/abc478/tasks/abc478_f
 *
 * Submissions ~> https://atcoder.jp/contests/abc478/submissions/80051821 By huanhuanonly
 *
 * @b Trees
 * @b Combinatorics
 * @b Monotonic-stack
 *
 * ----October 15, 2026 [11h:26m:02s]----
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

    std::vector<int> v(n + 1, n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> v[i];
    }

    constexpr uint64 mod = 998244353;

    uint64 tot = 1;

    std::stack<int> stack;
    stack.push(0);

    for (int i = 1; i <= n; ++i)
    {
        for (; v[stack.top()] < v[i]; stack.pop());

        (tot *= std::max(1, i - std::max(1, stack.top()))) %= mod;
        stack.push(i);
    }

    std::cout << tot << '\n';

    return 0;
}