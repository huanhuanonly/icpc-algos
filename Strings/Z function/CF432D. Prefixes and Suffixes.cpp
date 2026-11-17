/**
 * Codeforces Round 246 (Div. 2)
 *
 * => D. Prefixes and Suffixes ( @c 2000 )
 *
 * -> https://codeforces.com/contest/432/problem/D
 *
 * Submissions ~> https://codeforces.com/contest/432/submission/252527540 By huanhuanonly
 *
 * @b Z-function
 *
 * ----March 21, 2024 [11h:13m:05s]----
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

    z[0] = s.size();

    std::vector<int> st{z[0]};

    std::vector<int> ans{z[0]};

    int l = 0, r = 0;

    for (int i = 1; i < s.size(); ++i)
    {
        if (i <= r)
            z[i] = std::min(z[i - l], r - i + 1);

        while (i + z[i] < s.size() and s[z[i]] == s[i + z[i]])
            ++z[i];

        if (i + z[i] == s.size())
        {
            ans.push_back(z[i]);
        }

        st.push_back(z[i]);

        if (i + z[i] - 1 > r)
        {
            r = i + z[i] - 1;
            l = i;
        }
    }

    std::sort(st.begin(), st.end());

    std::sort(ans.begin(), ans.end());

    std::cout << ans.size() << '\n';

    for (const auto& i : ans)
        std::cout << i << ' ' << std::distance(std::lower_bound(st.begin(), st.end(), i), st.end()) << '\n';

    return 0;
}