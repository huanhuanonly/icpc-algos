/**
 * Toyota Programming Contest 2024#12（AtCoder Beginner Contest 384）
 *
 * => E - Takahashi is Slime 2 ( @c 450 )
 *
 * -> https://atcoder.jp/contests/abc384/tasks/abc384_e
 *
 * Submissions ~> https://atcoder.jp/contests/abc384/submissions/60811654 By huanhuanonly
 *
 * @b Breadth-first-search
 *
 * ----December 15, 2024 [21h:09m:40s]----
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

    int64 h, w, x;
    std::cin >> h >> w >> x;

    int32 p, q;
    std::cin >> p >> q;

    --p, --q;

    std::vector<std::vector<int64>> mp(h, std::vector<int64>(w));

    for (uint32 i = 0; i < h; ++i)
    {
        for (uint32 j = 0; j < w; ++j)
        {
            std::cin >> mp[i][j];
        }
    }

    auto bfs = [&, vis = std::vector<std::vector<bool>>(h, std::vector<bool>(w))]() mutable -> int64
    {
        struct node
        {
            int32 x, y;
            int64 w;

            bool operator<(const node& nd) const
            {
                return this->w > nd.w;
            }
        };

        int64 sum = 0;

        std::priority_queue<node> que;
        que.push({p, q, mp[p][q]});
        vis[p][q] = true;

        const std::pair<int32, int32> d[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

        while (not que.empty())
        {
            auto now = que.top();
            que.pop();

            if (not(now.w < sum / x + !!(sum % x)) and not(now.x == p and now.y == q))
            {
                continue;
            }

            sum += now.w;

            for (const auto& [dx, dy] : d)
            {
                int32 cx = now.x + dx, cy = now.y + dy;

                if (cx >= 0 and cx < h and cy >= 0 and cy < w and not vis[cx][cy])
                {
                    que.push({cx, cy, mp[cx][cy]});
                    vis[cx][cy] = true;
                }
            }
        }

        return sum;
    };

    std::cout << bfs();

    return 0;
}