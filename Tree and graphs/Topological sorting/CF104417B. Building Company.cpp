/**
 * The 13th Shandong ICPC Provincial Collegiate Programming Contest
 * 
 * => B. Building Company
 * 
 * -> https://codeforces.com/gym/104417/problem/B
 * 
 * Submissions ~> https://codeforces.com/gym/104417/submission/261643293 By huanhuanonly
 * 
 * @b Topological-sorting
 * 
 * ----May 19, 2024 [19h:18m:47s]----
*/

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>

using uint    = unsigned int;
using llong   = long long int;
using ullong  = unsigned long long int;
using ldouble = long double;

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int g;
    std::cin >> g;

    // <t, u>
    std::unordered_map<int, llong> mp;

    for (int i = 0; i < g; ++i)
    {
        int t, u;
        std::cin >> t >> u;

        mp[t] = u;
    }

    int n;
    std::cin >> n;

    std::vector<int> cnt(n);
    std::vector<std::unordered_map<int, int>> add(n);

    struct node
    {
        int value;
        int id;

        bool operator<(const node& nd) const
        {
            return this->value > nd.value;
        }
    };

    // <t, queue>
    std::map<int, std::priority_queue<node>> que;
    int ans = 0;

    for (int i = 0; i < n; ++i)
    {
        std::cin >> cnt[i];

        for (int j = 0; j < cnt[i]; ++j)
        {
            int t, u;
            std::cin >> t >> u;

            que[t].push({u, i});
        }

        int k;
        std::cin >> k;

        for (int j = 0; j < k; ++j)
        {
            int t, u;
            std::cin >> t >> u;

            if (cnt[i])
                add[i][t] = u;
            else
                mp[t] += u;
        }

        if (cnt[i] == 0)
        {
            ++ans;
        }
    }

    std::vector<int> cur;
    cur.reserve(n);

    node nd;

    for (auto it = mp.begin(); it != mp.end(); ++it)
    {
        while (not que[it->first].empty() and it->second >= (nd = que[it->first].top()).value)
        {
            if (--cnt[nd.id] == 0)
            {
                cur.push_back(nd.id);
            }

            que[it->first].pop();
        }
    }
    
    while (not cur.empty())
    {
        int now = cur.back();
        cur.pop_back();

        ++ans;

        for (auto it = add[now].begin(); it != add[now].end(); ++it)
        {
            mp[it->first] += it->second;

            while (not que[it->first].empty() and mp[it->first] >= (nd = que[it->first].top()).value)
            {
                if (--cnt[nd.id] == 0)
                {
                    cur.push_back(nd.id);
                }

                que[it->first].pop();
            }
        }
    }

    std::cout << ans;

    return 0;
}