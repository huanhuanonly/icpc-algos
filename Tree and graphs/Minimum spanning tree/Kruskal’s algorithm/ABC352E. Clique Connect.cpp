/**
 * AtCoder Beginner Contest 352
 * 
 * => E - Clique Connect ( @c 450 )
 * 
 * -> https://atcoder.jp/contests/abc352/tasks/abc352_e
 * 
 * Submissions ~> https://atcoder.jp/contests/abc352/submissions/53134909 By huanhuanonly
 * 
 * @b Kruskal’s-algorithm
 * 
 * ----May 04, 2024 [21h:28m:35s]----
*/

#include <bits/stdc++.h>

using uint = unsigned int;
using llong = long long int;
using ullong = unsigned long long int;
using ldouble = long double;

template<typename _ValueType>
class DisjointSet
{
public:
    using value_type = _ValueType;

    std::vector<value_type> v;

    explicit DisjointSet(std::size_t n)
        : v(n)
    {
        std::iota(v.begin(), v.end(), 0);
    }

    int find(int x)
    {
        return v[x] == x ? x : v[x] = find(v[x]);
    }

    void merge(int x, int y)
    {
        v[find(y)] = find(x);
    }
};

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __localhost
    ::freopen("Input.txt", "r", stdin);
    ::freopen("Output.txt", "w", stdout);
#endif

    int n, m;
    std::cin >> n >> m;

    DisjointSet<int> ds(n + 1);

    std::vector<std::pair<int, std::vector<int>>> mp;

    for (int i = 0; i < m; ++i)
    {
        int k, c;
        std::cin >> k >> c;

        std::vector<int> ct(k);
        
        for (int j = 0; j < k; ++j)
        {
            std::cin >> ct[j];
            
            if (j)
                ds.merge(ct[j], ct[j - 1]);
        }

        mp.push_back({c, std::move(ct)});
    }

    int fa = ds.find(1);
    for (int i = 1; i <= n; ++i)
    {
        if (ds.find(i) != fa)
        {
            std::cout << -1;
            return 0;
        }
    }

    std::iota(ds.v.begin(), ds.v.end(), 0);

    std::sort(mp.begin(), mp.end(), [&](const auto& lv, const auto& rv) -> bool
    {
        return lv.first < rv.first;
    });

    ullong sum = 0;

    for (int i = 0; i < mp.size(); ++i)
    {
        for (int j = 1; j < mp[i].second.size(); ++j)
        {
            if (ds.find(mp[i].second[j]) != ds.find(mp[i].second[j - 1]))
            {
                sum += mp[i].first;
                ds.merge(mp[i].second[j], mp[i].second[j - 1]);
            }
        }
    }

    std::cout << sum;

    return 0;
}