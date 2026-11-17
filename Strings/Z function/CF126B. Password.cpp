/**
 * Codeforces Beta Round 93 (Div. 1 Only)
 *
 * => B. Password ( @c 1700 )
 *
 * -> https://codeforces.com/contest/126/problem/B
 *
 * Submissions ~> https://codeforces.com/contest/126/submission/252413288 By huanhuanonly
 *
 * @b Z-function
 *
 * ----March 20, 2024 [16h:15m:38s]----
*/

#include <bits/stdc++.h>

using uint = unsigned int;
using llong = long long int;
using ullong = unsigned long long int;
using ldouble = long double;

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __localhost
    ::freopen("Input.txt", "r", stdin);
    ::freopen("Output.txt", "w", stdout);
#endif

    std::string s;
    std::cin >> s;

    std::vector<int> z(s.size());

    int l = 0, r = 0;

    z[0] = s.size();

    std::set<int> st;

    for (int i = 1; i < s.size(); ++i)
    {
        if (i <= r)
            z[i] = std::min(r - i + 1, z[i - l]);

        while (i + z[i] < s.size() and s[z[i]] == s[i + z[i]])
            ++z[i];

        if (i + z[i] == s.size() and st.lower_bound(z[i]) != st.end())
        {
            std::cout << std::string_view(s.c_str(), z[i]);
            return 0;
        }

        st.insert(z[i]);

        if (i + z[i] - 1 > r)
        {
            r = i + z[i] - 1;
            l = i;
        }
    }

    std::cout << "Just a legend";

    return 0;
}