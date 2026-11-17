/**
 * Codeforces Round 974 (Div. 3)
 *
 * => H. Robin Hood Archery ( @c 1900 )
 *
 * -> https://codeforces.com/contest/2014/problem/H
 *
 * Submissions ~> https://codeforces.com/contest/2014/submission/282785852 By huanhuanonly
 *
 * @b Zobrist-hashing
 *
 * ----September 24, 2024 [22h:07m:03s]----
*/

#include <bits/stdc++.h>

using uint    = unsigned int;
using llong   = long long int;
using ullong  = unsigned long long int;
using ldouble = long double;

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int _;
    std::cin >> _;

    while (_--)
    {
        int n, q;
        std::cin >> n >> q;

        std::vector<ullong> v(n + 1);

        std::map<int, ullong> mp;

        std::mt19937 rng;

        for (int i = 1; i <= n; ++i)
        {
            std::cin >> v[i];

            if (mp.contains(v[i]) == false)
            {
                mp[v[i]] = rng();
            }

            v[i] = mp[v[i]];

            v[i] ^= v[i - 1];
        }

        while (q--)
        {
            int l, r;
            std::cin >> l >> r;

            if ((v[r] ^ v[l - 1]) == 0)
                std::cout << "YES\n";
            else
                std::cout << "NO\n";
        }
    }

    return 0;
}