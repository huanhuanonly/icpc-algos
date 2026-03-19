/**
 * Testing Round 20 (Unrated, Communication Problems)
 * 
 * => B. Locate
 * 
 * -> https://codeforces.com/contest/2168/problem/B
 * 
 * Submissions ~> https://codeforces.com/contest/2168/submission/347278788 By huanhuanonly
 * 
 * @b Run-twice ( @a communication )
 * @b Interactive
 * @b Binary-search
 * 
 * ----November 04, 2025 [10h:29m:20s]----
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

#ifdef __GNUC__
using int128 = __int128;
using uint128 = unsigned __int128;
#endif

using real32 = float;
using real64 = double;
using real128 = long double;

int query(int l, int r)
{
    std::cout << "? " << l << ' ' << r << std::endl;
    
    int res;
    std::cin >> res;

    return res;
}

void answer(int p)
{
    std::cout << "! " << p << std::endl;
}

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    std::string type;
    std::cin >> type;

    if (type == "first")
    {
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

            for (int i = 0; i < n; ++i)
            {
                if (v[i] == n)
                {
                    std::cout << 0 << '\n';
                    break;
                }
                else if (v[i] == 1)
                {
                    std::cout << 1 << '\n';
                    break;
                }
            }
        }
    }
    else
    {
        int _;
        std::cin >> _;

        while (_--)
        {
            int n, x;
            std::cin >> n >> x;

            int l = 1, r = n, mid;

            while (r - l > 1)
            {
                mid = l + r >> 1;

                if (query(1, mid) == n - 1)
                {
                    r = mid;
                }
                else
                {
                    l = mid;
                }
            }

            std::array<int, 2> ans{};
            ans[1] = r;

            l = 1, r = n;

            while (r - l > 1)
            {
                mid = l + r >> 1;

                if (query(mid, n) == n - 1)
                {
                    l = mid;
                }
                else
                {
                    r = mid;
                }
            }

            ans[0] = l;

            answer(ans[x]);
        }
    }

    return 0;
}