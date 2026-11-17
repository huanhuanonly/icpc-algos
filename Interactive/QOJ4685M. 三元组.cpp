/**
 * 第十二届中国大学生程序设计竞赛 乐山站（CCPC 2026 Leshan Site）
 *
 * => M. 三元组
 *
 * -> https://qoj.ac/contest/4685/problem/24853
 *
 * Submissions ~> https://qoj.ac/submission/3426641 By huanhuanonly
 *
 * @b Interactive and @b Binary-search
 *
 * ----November 10, 2026 [22h:12m:43s]----
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

    int _;
    std::cin >> _;

    while (_--)
    {
        int n;
        std::cin >> n;

        struct item
        {
            int a, b, c;
        };

        std::vector<item> v(n);

        for (auto& [a, b, c] : v)
        {
            std::cin >> a >> b >> c;
        }

        static auto query = [](int a, int b, int c) -> std::string
        {
            std::cout << "? " << a << ' ' << b << ' ' << c << std::endl;

            std::string res;
            std::cin >> res;

            return res;
        };

        static auto answer = [](int a, int b, int c) -> void
        {
            std::cout << "! " << a << ' ' << b << ' ' << c << std::endl;
        };

        while (v.size() > 1)
        {
            std::ranges::sort(v, {}, &item::a);

            const int mid = v.size() / 2;
            const int a = v[mid].a;

            std::ranges::sort(v | std::views::take(mid), {}, &item::b);
            std::ranges::sort(v | std::views::drop(mid), {}, &item::c);

            const int b = v[mid / 2].b;
            const int c = v[(mid + v.size()) / 2].c;

            const auto res = query(a, b, c);

            if (res[0] == '1')
            {
                if (res[1] == '1')
                {
                    v = std::vector(v.begin(), v.begin() + mid / 2);
                }
                else
                {
                    v = std::vector(v.begin() + mid / 2, v.begin() + mid);
                }
            }
            else
            {
                if (res[2] == '1')
                {
                    v = std::vector(v.begin() + mid, v.begin() + (mid + v.size()) / 2);
                }
                else
                {
                    v = std::vector(v.begin() + (mid + v.size()) / 2, v.end());
                }
            }
        }

        answer(v.front().a, v.front().b, v.front().c);
    }

    return 0;
}