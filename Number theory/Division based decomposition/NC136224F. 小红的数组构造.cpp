/**
 * 牛客周赛 Round 147
 *
 * => F-小红的数组构造 ( @c 2000 )
 *
 * -> https://ac.nowcoder.com/acm/contest/136224/F
 *
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=83826794 By huanhuanonly
 *
 * @b Number-theory ( @a division-based-decomposition )
 * @b Breadth-first-search
 *
 * ----June 08, 2026 [09h:53m:40s]----
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

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int _;
    std::cin >> _;

    while (_--)
    {
        int n, x, k;
        std::cin >> n >> x >> k;

        std::vector<int> set;

        for (int i = 1; i <= x; i = x / (x / i) + 1)
        {
            set.push_back(x / i);
        }

        set.pop_back();
        std::ranges::transform(set, set.begin(), [](int i) -> int { return i - 1; });

        const int target = k - n;

        if (target < 0)
        {
            std::cout << "NO\n";
            continue;
        }

        const auto inf = std::numeric_limits<int>::max() / 2;

        std::vector<int> dis(target + 1, inf);
        std::vector<std::map<int, int>> cnts(dis.size());

        std::vector<bool> vis(dis.size());

        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::ranges::greater> que;

        que.emplace(0, 0);
        dis[0] = 0;

        while (not que.empty())
        {
            auto [cdis, cid] = que.top();
            que.pop();

            if (vis[cid])
            {
                continue;
            }

            vis[cid] = true;

            for (int i : set)
            {
                if (cid + i < dis.size() and dis[cid] + 1 < dis[cid + i])
                {
                    dis[cid + i] = dis[cid] + 1;

                    cnts[cid + i] = cnts[cid];
                    ++cnts[cid + i][i];

                    que.emplace(dis[cid + i], cid + i);
                }
            }
        }

        if (dis.back() > n)
        {
            std::cout << "NO\n";
            continue;
        }

        std::vector<int> ans(n, x);

        for (auto [i, it] = std::pair(0, cnts.back().begin()); it != cnts.back().end(); ++i)
        {
            ans[i] = x / (it->first + 1);

            if (--it->second == 0)
            {
                ++it;
            }
        }

        assert(*std::ranges::fold_left_first(ans | std::views::transform([x](int i) { return x / i; }), std::plus{}) == k);

        std::cout << "YES\n";

        for (int i = 0; i < n; ++i)
        {
            std::cout << ans[i] << " \n"[i + 1 == n];
        }
    }

    return 0;
}