/**
 * Codeforces Round 668 (Div. 1)
 *
 * => E. Bricks ( @c 2800 )
 *
 * -> https://codeforces.com/contest/1404/problem/E
 *
 * Submissions ~> https://codeforces.com/contest/1404/submission/387442532 By huanhuanonly
 *
 * @b Bipartite-graph ( @a maximum-independent-set )
 * @b Dinic for @a Max-flow ( @a bipartite-graph-with-modeling )
 *
 * ----August 17, 2026 [23h:51m:33s]----
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
    inline namespace network_flow
{
template<typename _CapacityT = int>
class Dinic
{
public:

    using size_type = int;
    using capacity_type = _CapacityT;

    struct edge
    {
        size_type to;
        size_type rid;

        capacity_type cap;
    };

    static constexpr size_type rid_mask = size_type{1} << sizeof(size_type) * 8 - 1;

    explicit
    Dinic(size_type __n = 0) : _M_e(__n), _M_cg(__n), _M_cur(__n)
    { }

    void
    add_edge(size_type __from, size_type __to, capacity_type __cap)
    {
        _M_e[__from].emplace_back(__to, size_type(_M_e[__to].size()) | rid_mask, __cap);
        _M_e[__to].emplace_back(__from, size_type(_M_e[__from].size()) - 1, capacity_type{});
    }

    [[nodiscard]] size_type
    size() const noexcept
    { return size_type(_M_e.size()); }

    [[nodiscard]] const std::vector<edge>&
    edges(size_type __i) const
    { return _M_e[__i]; }

    [[nodiscard]] capacity_type
    current_flow() const noexcept
    { return _M_flow; }

    size_type
    build_level_graph(size_type __source, size_type __sink)
    {
        _M_cg.assign(_M_cg.size(), std::numeric_limits<size_type>::max());
        _M_cur.assign(_M_cur.size(), size_type{});

        std::queue<size_type> que;
        que.push(__source);
        _M_cg[__source] = size_type{};

        while (not que.empty())
        {
            const auto u = que.front();
            que.pop();

            for (const edge& i : _M_e[u])
            {
                if (i.cap and _M_cg[i.to] == std::numeric_limits<size_type>::max())
                {
                    _M_cg[i.to] = _M_cg[u] + 1;
                    que.push(i.to);
                }
            }
        }

        return _M_cg[__sink];
    }

    capacity_type
    augment_flow(size_type __source, size_type __sink)
    {
        const auto flow = _M_augment_flow(__source, __sink, std::numeric_limits<capacity_type>::max());
        _M_flow += flow;
        return flow;
    }

    capacity_type
    max_flow(size_type __source, size_type __sink)
    {
        while (build_level_graph(__source, __sink) != std::numeric_limits<size_type>::max())
        {
            while (augment_flow(__source, __sink));
        }

        return _M_flow;
    }

    capacity_type
    min_cut(size_type __source, size_type __sink)
    { return max_flow(__source, __sink); }

    void
    restore()
    {
        for (std::vector<edge>& es : _M_e)
        {
            for (edge& i : es)
            {
                if (i.rid & rid_mask)
                {
                    i.cap += _M_e[i.to][i.rid ^ rid_mask].cap;
                    _M_e[i.to][i.rid ^ rid_mask].cap = 0;
                }
            }
        }

        _M_flow = capacity_type{};
    }

    void
    resize(size_type __n)
    {
        _M_e.resize(__n);
        _M_cg.resize(__n);
        _M_cur.resize(__n);
    }

    void
    reset()
    {
        for (std::vector<edge>& i : _M_e)
        {
            i.clear();
        }

        _M_flow = capacity_type{};
    }

private:

    capacity_type
    _M_augment_flow(size_type __u, size_type __sink, capacity_type __limit)
    {
        if (__u == __sink)
        {
            return __limit;
        }

        while (_M_cur[__u] < size_type(_M_e[__u].size()))
        {
            edge& i = _M_e[__u][_M_cur[__u]];
            ++_M_cur[__u];

            if (_M_cg[__u] + 1 == _M_cg[i.to] and i.cap)
            {
                if (const auto flow = _M_augment_flow(i.to, __sink, std::min(__limit, i.cap)); flow)
                {
                    i.cap -= flow;
                    _M_e[i.to][i.rid & ~rid_mask].cap += flow;

                    return flow;
                }

                _M_cg[i.to] = std::numeric_limits<size_type>::max();
            }
        }

        return capacity_type{};
    }

    std::vector<std::vector<edge>> _M_e;
    std::vector<size_type> _M_cg;

    std::vector<size_type> _M_cur;

    capacity_type _M_flow{};
};
}} // namespace huanhuanonly::network_flow

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int n, m;
    std::cin >> n >> m;

    std::vector<std::string> map(n);
    int cnt = 0;

    for (auto& s : map)
    {
        std::cin >> s;
        cnt += std::ranges::count(s, '#');
    }

    std::vector id(n, std::vector<std::pair<int, int>>(m));
    int lcnt = 0, rcnt = 0;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (map[i][j] == '#')
            {
                if (i + 1 < n and map[i + 1][j] == '#')
                {
                    id[i][j].first = ++lcnt;
                }

                if (j + 1 < m and map[i][j + 1] == '#')
                {
                    id[i][j].second = ++rcnt;
                }
            }
        }
    }

    std::vector<std::vector<int>> e(lcnt + rcnt);

    Dinic dinic(lcnt + rcnt + 2);

    const int source = dinic.size() - 1;
    const int sink = source - 1;

    for (int i = 0; i < lcnt; ++i)
    {
        dinic.add_edge(source, i, 1);
    }

    for (int i = 0; i < rcnt; ++i)
    {
        dinic.add_edge(lcnt + i, sink, 1);
    }

    auto add_edge = [&](int u, int v) -> void
    {
        --u, v += lcnt - 1;
        dinic.add_edge(u, v, 1);
    };

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (id[i][j].first)
            {
                if (id[i][j].second)
                {
                    add_edge(id[i][j].first, id[i][j].second);
                }

                if (id[i + 1][j].second)
                {
                    add_edge(id[i][j].first, id[i + 1][j].second);
                }
            }

            if (id[i][j].second)
            {
                if (id[i][j + 1].first)
                {
                    add_edge(id[i][j + 1].first, id[i][j].second);
                }
            }

            if (i + 1 < n and j + 1 < m and id[i][j + 1].first and id[i + 1][j].second)
            {
                add_edge(id[i][j + 1].first, id[i + 1][j].second);
            }
        }
    }

    cnt -= lcnt + rcnt - dinic.max_flow(source, sink);

    std::cout << cnt << '\n';

    return 0;
}