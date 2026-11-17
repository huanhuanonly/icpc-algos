/**
 * 第十三届重庆市大学生程序设计竞赛
 *
 * => L. 栈与重复
 *
 * -> https://codeforces.com/gym/105887/problem/L
 *
 * Submissions ~> https://codeforces.com/gym/105887/submission/319742507 By huanhuanonly
 *
 * @b Implementation
 *
 * ----May 16, 2025 [14h:51m:53s]----
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

    int n;
    std::cin >> n;

    constexpr uint64 mod = 998244353;

    std::deque<int> st;

    std::vector<std::pair<int, int>> ins(n);

    int cnt = 4e5;

    std::string s;
    int x;

    for (int i = 0; i < n; ++i)
    {
        std::cin >> s;

        if (s == "Push")
        {
            std::cin >> x;
            ins[i] = {0, x};
        }
        else if (s == "Pop")
        {
            ins[i].first = 1;
        }
        else
        {
            ins[i].first = 2;
        }
    }

    uint64 sum = 0;

    for (const auto& [opt, x] : ins)
    {
        if (opt == 0)
        {
            st.push_back(x);
            (sum += x) %= mod;
        }
        else if (opt == 1)
        {
            sum = (sum + mod - st.back()) % mod;
            st.pop_back();

            --cnt;
        }
        else
        {
            (sum *= 2) %= mod;

            int size = st.size();

            for (int i = 1; st.size() < cnt and i <= size; ++i)
            {
                st.push_front(st[st.size() - i]);
            }
        }

        while (st.size() > cnt)
        {
            st.pop_front();
        }

        std::cout << sum << '\n';
    }

    return 0;
}