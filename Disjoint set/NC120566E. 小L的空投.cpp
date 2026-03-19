/**
 * 2026牛客寒假算法基础集训营6
 * 
 * => E-小L的空投 ( @c 1900 )
 * 
 * -> https://ac.nowcoder.com/acm/contest/120566/E
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=82426223 By huanhuanonly
 * 
 * @b Graphs
 * @b Disjoint-set
 * @b Offline
 * 
 * ----February 13, 2026 [17h:54m:24s]----
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

inline namespace huanhuanonly {
    inline namespace data_structure
{
class DisjointSet
{
public:

    using size_type = int;

    struct node
    {
        size_type parent;
        size_type size;
    };

    struct change_record
    {
        std::pair<size_type&, size_type> parent;
        std::pair<size_type&, size_type> size;
    };

    explicit
    DisjointSet(size_type __n)
        : _M_tree(__n)
    {
        for (size_type i = 0; i < __n; ++i)
        {
            _M_tree[i].parent = i;
            _M_tree[i].size = 1;
        }
    }

    size_type
    find(size_type u) const
    { return is_root(u) ? u : find(_M_tree[u].parent); }

    bool
    unite(size_type u, size_type v)
    {
        size_type fu = find(u);
        size_type fv = find(v);

        if (fu == fv)
        {
            return false;
        }

        if (_M_tree[fu].size < _M_tree[fv].size)
        {
            std::swap(fu, fv);
        }

        _M_history.emplace(change_record{
                { _M_tree[fv].parent, _M_tree[fv].parent },
                { _M_tree[fu].size,   _M_tree[fu].size   }
            }
        );
        
        _M_tree[fv].parent = fu;
        _M_tree[fu].size += _M_tree[fv].size;

        return true;
    }

    [[nodiscard]] bool
    is_root(size_type u) const
    { return _M_tree[u].parent == u; }

    [[nodiscard]] bool
    connected(size_type u, size_type v) const
    { return find(u) == find(v); }

    void
    undo()
    {
        if (not _M_history.empty())
        {
            const auto& rec = _M_history.top();

            rec.parent.first = rec.parent.second;
            rec.size.first = rec.size.second;

            _M_history.pop();
        }
    }

    [[nodiscard]] size_type
    size() const
    { return static_cast<size_type>(_M_tree.size()); }

    [[nodiscard]] size_type
    component_size(size_type u) const
    { return _M_tree[find(u)].size; }

    [[nodiscard]] size_type
    checkpoint() const
    { return static_cast<size_type>(_M_history.size()); }

    void
    rollback(size_type __cp)
    { for (; checkpoint() > __cp; undo()); }

private:

    std::vector<node> _M_tree;
    std::stack<change_record, std::vector<change_record>> _M_history;
};
}} // namespace huanhuanonly::data_structure

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int n, m, x, d;
    std::cin >> n >> m >> x >> d;

    std::set<std::pair<int, int>, std::ranges::greater> set;

    std::vector<int> h(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> h[i];
        set.emplace(h[i], i);
    }

    std::vector<std::vector<int>> e(n + 1);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        std::cin >> u >> v;

        e[u].push_back(v);
        e[v].push_back(u);
    }

    std::vector<int> H(x);

    for (int i = 0; i < x; ++i)
    {
        std::cin >> H[i];
    }

    DisjointSet dsu(n + 1);

    std::vector<int> ans(x);
    int cnt = 0;

    std::vector<bool> vis(n + 1);

    for (int i = x - 1; i >= 0; --i)
    {
        for (auto it = set.begin(); it != set.end() and it->first > H[i]; it = set.erase(it))
        {
            vis[it->second] = true;

            if (d == 1)
            {
                ++cnt;
            }

            for (const auto& u : e[it->second])
            {
                if (not vis[u])
                {
                    continue;
                }

                if (dsu.connected(it->second, u))
                {
                    continue;
                }

                const int b = (dsu.component_size(it->second) < d) + (dsu.component_size(u) < d);

                dsu.unite(it->second, u);

                if (b == 0)
                {
                    --cnt;
                }
                else if (b == 2 and dsu.component_size(it->second) >= d)
                {
                    ++cnt;
                }
            }
        }

        ans[i] = cnt;
    }

    for (int i = 0; i < x; ++i)
    {
        std::cout << ans[i] << '\n';
    }

    return 0;
}