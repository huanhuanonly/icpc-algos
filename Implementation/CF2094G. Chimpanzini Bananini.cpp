/**
 * Codeforces Round 1017 (Div. 4)
 *
 * => G. Chimpanzini Bananini ( @c 1700 )
 *
 * -> https://codeforces.com/contest/2094/problem/G
 *
 * Submissions ~> https://codeforces.com/contest/2094/submission/315815722 By huanhuanonly
 *
 * @b Implementation
 *
 * ----April 16, 2025 [18h:27m:18s]----
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

#ifdef __localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int _;
    std::cin >> _;

    while (_--)
    {
        int q;
        std::cin >> q;

        uint64 sum = 0;

        bool reversed = false;

        uint64 dsum[2]{};

        std::deque<uint64> que;

        while (q--)
        {
            int opt;

            std::cin >> opt;

            switch (opt)
            {
                case 1:
                {
                    if (not reversed)
                    {
                        uint64 x = que.back();
                        dsum[0] -= x * que.size();
                        dsum[1] -= sum;
                        que.pop_back();

                        que.push_front(x);
                        dsum[0] += sum;
                        dsum[1] += x * que.size();
                    }
                    else
                    {
                        uint64 x = que.front();
                        dsum[0] -= sum;
                        dsum[1] -= x * que.size();
                        que.pop_front();

                        que.push_back(x);
                        dsum[0] += x * que.size();
                        dsum[1] += sum;
                    }

                    break;
                }

                case 2:
                {
                    reversed = not reversed;
                    break;
                }

                case 3:
                {
                    uint64 x;
                    std::cin >> x;

                    if (not reversed)
                    {
                        que.push_back(x);
                        dsum[0] += x * que.size();
                        dsum[1] += sum + x;
                    }
                    else
                    {
                        que.push_front(x);
                        dsum[0] += sum + x;
                        dsum[1] += x * que.size();
                    }


                    sum += x;

                    break;
                }
            }

            std::cout << dsum[reversed] << '\n';
        }
    }

    return 0;
}