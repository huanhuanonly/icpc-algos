/**
 * Testing Round 20 (Unrated, Communication Problems)
 * 
 * => A2. Encode and Decode (Hard Version)
 * 
 * -> https://codeforces.com/contest/2168/problem/A2
 * 
 * Submissions ~> https://codeforces.com/contest/2168/submission/347271892 By huanhuanonly
 * 
 * @b Run-twice ( @a communication )
 * 
 * ----November 03, 2025 [22h:52m:20s]----
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

    std::string type;
    std::cin >> type;

    if (type == "first")
    {
        int n;
        std::cin >> n;

        for (int i = 0, v; i < n; ++i)
        {
            std::cin >> v;
            
            auto s = std::to_string(v);
            s.insert(0, std::string(10 - s.size(), '0'));

            std::ranges::transform(s, s.begin(), [](char c) -> char { return c - '0' + 'a'; });

            std::cout << s;
        }
    }
    else
    {
        std::string s;
        std::cin >> s;

        std::cout << s.size() / 10 << '\n';

        std::ranges::transform(s, s.begin(), [](char c) -> char { return c - 'a' + '0'; });

        for (int i = 0; i < s.size(); i += 10)
        {
            std::cout << std::stoi(s.substr(i, 10)) << ' ';
        }
    }

    return 0;
}