/**
 * Codeforces Round 1084 (Div. 3)
 * 
 * => E. Divisive Battle ( @c Rating )
 * 
 * -> https://codeforces.com/contest/2200/problem/E
 * 
 * Submissions ~> https://codeforces.com/contest/2200/submission/364707125 By huanhuanonly
 * 
 * @b Game-theory and @b Number-theory ( @a prime-factorization )
 * 
 * ----February 28, 2026 [23h:51m:27s]----
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
[[nodiscard]] std::vector<_Tp> prime_factorization(_Tp __n)
{
    std::vector<_Tp> res;

    for (_Tp i = 2; i * i <= __n; ++i)
    {
        for (; __n % i == 0; __n /= i)
        {
            res.push_back(i);
        }
    }

    if (__n != 1)
    {
        res.push_back(__n);
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

    int _;
    std::cin >> _;

    while (_--)
    {
        int n;
        std::cin >> n;

        std::vector<int> v(n);

        for (int i = 0; i < n; ++i)
        {
            std::cin >> v[i];
        }

        if (std::ranges::is_sorted(v))
        {
            std::cout << "Bob\n";
            continue;
        }

        bool alice = false;

        for (int i = 0; i < n; ++i)
        {
            if (auto ps = prime_factorization(v[i]); not ps.empty())
            {
                std::ranges::sort(ps);
                
                if (ps.front() != ps.back())
                {
                    alice = true;
                    break;
                }
                else
                {
                    v[i] = ps.front();
                }
            }
        }

        if (alice or not std::ranges::is_sorted(v))
        {
            std::cout << "Alice\n";
        }
        else
        {
            std::cout << "Bob\n";
        }
    }

    return 0;
}