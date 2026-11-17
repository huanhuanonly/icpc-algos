/**
 * 2025年码蹄杯 职业院校赛道 & 青少年挑战赛道入门组国赛
 * 
 * => MC0447 茶叶的年份 ( @c 星耀 )
 * 
 * -> https://www.matiji.net/exam/brushquestion/47/4693/305EE97B0D5E361DE6A28CD18C929AF0
 * 
 * Submissions ~> https://www.matiji.net/exam/oj/submit-detail/15229983/47/4693/305EE97B0D5E361DE6A28CD18C929AF0 By huanhuanonly
 * 
 * @b Binary-lifting
 * 
 * ----August 26, 2025 [19h:21m:33s]----
*/

#include <bits/stdc++.h>

using uint64 = unsigned long long;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<uint64> v(n + 1);

    std::vector<uint64> pre(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> v[i];
    }

    for (int i = 1; i <= n; ++i)
    {
        pre[i] = pre[i - 1] + v[i];
    }

    auto get = [&](int l, int r) -> uint64
    {
        return pre[r] - pre[l - 1];
    };

    std::vector<std::vector<int>> next(n + 2, std::vector<int>(21, n + 1));
    std::vector<std::vector<uint64>> cost(n + 2, std::vector<uint64>(21));

    std::set<std::pair<int, int>> st;

    for (int i = 1; i <= n; ++i)
    {
        while (not st.empty() and st.begin()->first < v[i])
        {
            int pos = st.begin()->second;

            next[pos][0] = i;
            cost[pos][0] = (i - pos) * v[pos] - get(pos, i - 1);

            st.erase(st.begin());
        }

        st.insert({v[i], i});
    }

    for (int lay = 1; lay < 21; ++lay)
    {
        for (int i = 1; i <= n; ++i)
        {
            next[i][lay] = next[next[i][lay - 1]][lay - 1];
            cost[i][lay] = cost[i][lay - 1] + cost[next[i][lay - 1]][lay - 1];
        }
    }

    while (q--)
    {
        int l, r;
        std::cin >> l >> r;

        uint64 sum = 0;

        for (int i = 21 - 1; i >= 0; --i)
        {
            if (next[l][i] <= r)
            {
                sum += cost[l][i];
                l = next[l][i];
            }
        }

        if (l < r)
        {
            sum += (r - l + 1) * v[l] - get(l, r);
        }

        std::cout << sum << '\n';
    }

    return 0;
}