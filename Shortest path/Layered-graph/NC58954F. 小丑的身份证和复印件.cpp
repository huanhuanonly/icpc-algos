/**
 * 2023年长沙学院程序设计竞赛(CCSUPC)
 *
 * => F-小丑的身份证和复印件
 *
 * -> https://ac.nowcoder.com/acm/contest/58954/F
 *
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=64552021 By huanhuanonly
 *
 * @b Bfs based on @b Layered-graph
 *
 * ----October 18, 2023 [11h:23m:06s]----
*/

#include <bits/stdc++.h>

using uint = unsigned;
using llong = long long;
using ullong = unsigned long long;

/** The length of the card is 10, so it has 2^10 states */
int  dis[100][100][1 << 10];

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::pair<int, int> start, end;

    const char s_card[] = "JOKERjoker";
    std::map<char, int> card;
    for (int i = 0, j = 1; i < sizeof(s_card) - 1; ++i, j <<= 1) card[s_card[i]] = j;

    std::vector<std::vector<char>> mp(n, std::vector<char>(m));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            std::cin >> mp[i][j];
            if (mp[i][j] == '(') start = std::make_pair(i, j);
            else if (mp[i][j] == ')') end = std::make_pair(i, j);
        }
    }

    std::function<int()> bfs = [&]() -> int
    {
        memset(dis, 0x3f, sizeof(dis));
        dis[start.first][start.second][0b0000000000] = 0;

        std::pair<int, int> d[] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

        std::queue<std::tuple<int, int, int>> que;
        que.push({ start.first, start.second, 0 });

        while (not que.empty())
        {
            auto [x, y, layer] = que.front();
            que.pop();

            for (const auto& [i, j] : d)
            {
                int cx = x + i, cy = y + j, cl = layer;

                if (cx >= 0 && cx < n && cy >= 0 && cy < m && mp[cx][cy] != '#')
                {
                    auto it = card.find(mp[cx][cy]);
                    if (it != card.end()) cl |= it->second;

                    if (dis[cx][cy][cl] > dis[x][y][layer] + 1)
                    {
                        dis[cx][cy][cl] = dis[x][y][layer] + 1;
                        que.push({ cx, cy, cl });
                    }
                }
            }
        }
        return dis[end.first][end.second][0b1111111111];
    };

    int ans = bfs();
    std::cout << (ans == 0x3f3f3f3f ? -1 : ans) << '\n';

    return 0;
}