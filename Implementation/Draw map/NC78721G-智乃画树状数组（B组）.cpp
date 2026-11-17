/**
 * 2023年第六届传智杯程序设计挑战赛决赛
 *
 * => G-智乃画树状数组（B组）
 *
 * -> https://ac.nowcoder.com/acm/contest/78721/G
 *
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=68390458 By huanhuanonly
 *
 * @b Implementation ( @a draw-map )
 *
 * ----March 25, 2024 [20h:51m:30s]----
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

    int n;
    std::cin >> n;

    std::vector<std::vector<char>> mp(2 * std::floor(std::log2(n)) + 7, std::vector<char>(4 * n + 3, ' '));

    for (int i = 0; i < mp.size(); ++i)
        mp[i].front() = '*';

    for (int i = 0; i < mp.size(); ++i)
        mp[i].back() = '*';

    for (int i = 0; i < mp.front().size(); ++i)
        mp.front()[i] = '*';

    for (int i = 0; i < mp.front().size(); ++i)
        mp.back()[i] = '*';

    auto print_number = [&](int x, int y, int v) -> void
    {
        if (v >= 100)
        {
            mp[x][y + 1] = '0' + v / 100;
            mp[x][y + 2] = '0' + v / 10 % 10;
            mp[x][y + 3] = '0' + v / 1 % 10;
        }
        else if (v >= 10)
        {
            mp[x][y + 1] = '0' + v / 10 % 10;
            mp[x][y + 2] = '0' + v / 1 % 10;
        }
        else
        {
            mp[x][y + 1] = '0' + v / 1 % 10;
        }
    };

    auto print_rect = [&](int x, int y, int flag = 0, int flag2 = 0) -> void
    {
        if (flag2 == 1)
        {
            mp[x][y] = '+';
            mp[x + 2][y] = '+';
        }
        else if (flag2 == 2)
        {
            mp[x][y + 4] = '+';
            mp[x + 2][y + 4] = '+';
        }
        else if (flag2)
        {
            if (mp[x][y] == ' ')
                mp[x][y] = '-';

            if (mp[x + 2][y] == ' ')
                mp[x + 2][y] = '-';

            if (mp[x][y + 4] == ' ')
                mp[x][y + 4] = '-';

            if (mp[x + 2][y + 4] == ' ')
                mp[x + 2][y + 4] = '-';
        }
        else
        {
            mp[x][y] = '+';
            mp[x + 2][y] = '+';
            mp[x][y + 4] = '+';
            mp[x + 2][y + 4] = '+';
        }

        if (flag == 0 or flag == 1)
            mp[x + 1][y] = '|';

        if (flag == 0 or flag == 2)
            mp[x + 1][y + 4] = '|';


        mp[x][y + 1] = '-';
        mp[x][y + 2] = '-';
        mp[x][y + 3] = '-';
        mp[x + 2][y + 1] = '-';
        mp[x + 2][y + 2] = '-';
        mp[x + 2][y + 3] = '-';
    };

    auto get_layer = [&](int layer, int col) -> std::pair<int, int>
    {
        int x = layer * 2;
        int y = 2 + (col - 1) * 4;

        return {x, y};
    };

    auto print_line = [&](int layer, int x, int y) -> void
    {
        for (int i = x; i <= y; ++i)
        {
            auto [xx, yy] = get_layer(layer, i);
            print_rect(xx - 1, yy - 1, i == x ? 1 : (i == y ? 2 : 3), i == x ? 1 : (i == y ? 2 : 3));
        }
    };

    for (int i = 1, ct = 1; ct <= n; i += 4, ++ct)
    {
        print_rect(mp.size() - 4, i);
        print_number(mp.size() - 3, i, ct);
    }
    mp[mp.size() - 4][mp.front().size() - 2] = '+';
    mp[mp.size() - 3][mp.front().size() - 2] = '|';
    mp[mp.size() - 2][mp.front().size() - 2] = '+';

    for (int i = 1; i <= n; i += 2)
    {
        int layer = std::max<int>(std::ceil(std::log2(n)), 1);
        for (int j = i, k = 0; j <= n and layer; j <<= 1, --layer, k = (k << 1) | 1)
        {
            auto [x, y] = get_layer(layer, j);

            print_rect(x - 1, y - 1);
            print_number(x, y - 1, j);

            print_line(layer, j - k, j);
        }
    }

    for (int i = 0; i < mp.size(); ++i)
    {
        for (int j = 0; j < mp[i].size(); ++j)
            std::cout << mp[i][j];
        std::cout.put('\n');
    }
    return 0;
}