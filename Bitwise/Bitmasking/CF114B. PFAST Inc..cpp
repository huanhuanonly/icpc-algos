/**
 * Codeforces Beta Round 86 (Div. 2 Only)
 * 
 * => B. PFAST Inc. ( @c 1500 )
 * 
 * -> https://codeforces.com/contest/114/problem/B
 * 
 * Submissions ~> https://codeforces.com/contest/114/submission/339271012 By huanhuanonly
 * 
 * @b Bitmasks
 * 
 * ----September 18, 2025 [22h:18m:28s]----
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

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int n, m;
    std::cin >> n >> m;

    std::map<std::string, int> mp;
    std::vector<std::string> vs(n);

    std::string s, t;

    for (int i = 0; i < n; ++i)
    {
        std::cin >> s;
        mp[s];
    }

    for (auto [it, i] = std::tuple(mp.begin(), 0); it != mp.end(); ++it, ++i)
    {
        it->second = (1U << i);
        vs[i] = it->first;
    }

    std::vector<int> masks(m);

    for (int i = 0; i < m; ++i)
    {
        std::cin >> s >> t;
        masks[i] = mp[s] | mp[t];
    }

    std::pair<int, int> ans;

    for (uint32 i = 1; i < (1U << n); ++i)
    {
        bool can = true;

        for (int j = 0; j < m; ++j)
        {
            if ((i & masks[j]) == masks[j])
            {
                can = false;
                break;
            }
        }

        if (can)
        {
            ans = std::max(ans, {std::popcount(i), i});
        }
    }

    std::cout << ans.first << '\n';

    std::vector<std::string> set;

    for (int i = 0; ans.second; ++i, ans.second >>= 1)
    {
        if (ans.second & 1)
        {
            set.push_back(vs[i]);
        }
    }

    std::ranges::sort(set);

    for (const auto& i : set)
    {
        std::cout << i << '\n';
    }

    return 0;
}