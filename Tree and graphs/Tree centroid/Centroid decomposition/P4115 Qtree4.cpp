/**
 * => P4115 Qtree4 ( @c 省选/NOI- )
 *
 * -> https://www.luogu.com.cn/problem/P4115
 *
 * Submissions ~> https://www.luogu.com.cn/record/280596696 By huanhuanonly
 *
 * @b Centroid-decomposition
 * @b Lazy-deletion-heap
 *
 * ----June 04, 2026 [15h:35m:32s]----
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

template<typename _Tp, typename _Comp = std::ranges::less>
class LazyHeap
{
public:

    using value_type = _Tp;

    void push(const value_type& __value)
    { _M_check(); _M_que.push(__value); }

    void pop()
    { _M_check(); _M_que.pop(); }

    const value_type& top() const
    { _M_check(); return _M_que.top(); }

    void erase(const value_type& __value)
    { _M_check(); _M_removed.push(__value); }

    bool empty() const
    { _M_check(); return _M_que.empty(); }

private:

    void _M_check() const
    {
        _Comp comp{};

        for (; not _M_que.empty() and not _M_removed.empty() and comp(_M_que.top(), _M_removed.top()); _M_removed.pop());
        for (; not _M_que.empty() and not _M_removed.empty() and not comp(_M_que.top(), _M_removed.top()) and not comp(_M_removed.top(), _M_que.top()); _M_que.pop(), _M_removed.pop());
    }

private:

    mutable std::priority_queue<value_type, std::vector<value_type>, _Comp> _M_que, _M_removed;
};

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int n;
    std::cin >> n;

    std::vector<std::vector<std::pair<int, int>>> e(n + 1);

    for (int i = 0; i < n - 1; ++i)
    {
        int u, v, w;
        std::cin >> u >> v >> w;

        e[u].emplace_back(v, w);
        e[v].emplace_back(u, w);
    }

    std::vector<bool> removed(n + 1);
    std::vector<int> sizes(n + 1);

    auto find_centroid = [&](int u) -> int
    {
        std::vector<int> set;

        auto build = [&](const auto& self, int u, int fa) -> void
        {
            if (removed[u])
            {
                return;
            }

            set.push_back(u);

            sizes[u] = 1;

            for (const auto& [v, w] : e[u])
            {
                if (v != fa)
                {
                    self(self, v, u);
                    sizes[u] += sizes[v];
                }
            }
        };

        build(build, u, 0);

        for (int v : set)
        {
            int mx = sizes[u] - sizes[v];

            for (const auto& [i, w] : e[v])
            {
                if (sizes[i] < sizes[v])
                {
                    mx = std::max(mx, sizes[i]);
                }
            }

            if (mx <= sizes[u] / 2)
            {
                return v;
            }
        }

        std::unreachable();
    };

    std::vector<int> depth(n + 1);

    LazyHeap<int> best;

    std::vector<LazyHeap<int>> dsets(n + 1);
    std::vector<std::vector<LazyHeap<int>>> disets(n + 1);

    std::vector<std::vector<std::tuple<int, int, int>>> psets(n + 1);

    std::vector<int> contrs(n + 1);

    auto contr = [&](int u) -> int
    {
        if (dsets[u].empty())
        {
            return ~0;
        }

        const auto a = dsets[u].top();
        dsets[u].pop();

        if (dsets[u].empty())
        {
            dsets[u].push(a);
            return ~0;
        }

        const auto b = dsets[u].top();
        dsets[u].push(a);

        return a + b;
    };

    auto collect = [&](const auto& self, int u, int fa, int top) -> void
    {
        psets[u].emplace_back(top, disets[top].size() - 1, depth[u]);
        disets[top].back().push(depth[u]);

        for (const auto& [v, w] : e[u])
        {
            if (v != fa and not removed[v])
            {
                depth[v] = depth[u] + w;
                self(self, v, u, top);
            }
        }
    };

    auto centroid_decomposition = [&](const auto& self, int u) -> void
    {
        removed[u] = true;
        sizes[u] = 0;
        depth[u] = 0;

        disets[u].emplace_back();
        psets[u].emplace_back(u, 0, 0);
        disets[u].back().push(0);

        for (const auto& [v, w] : e[u])
        {
            if (not removed[v])
            {
                depth[v] = w;

                disets[u].emplace_back();
                collect(collect, v, u, u);
                self(self, find_centroid(v));
            }
        }

        for (const auto& set : disets[u])
        {
            dsets[u].push(set.top());
        }

        if (~(contrs[u] = contr(u)))
        {
            best.push(contrs[u]);
        }
    };

    centroid_decomposition(centroid_decomposition, find_centroid(1));

    std::vector<bool> color(n + 1, true);
    int cnt_white = n;

    int q;
    std::cin >> q;

    while (q--)
    {
        char opt;
        std::cin >> opt;

        if (opt == 'C')
        {
            int u;
            std::cin >> u;

            for (const auto& [parent, id, d] : psets[u])
            {
                if (not disets[parent][id].empty())
                {
                    dsets[parent].erase(disets[parent][id].top());
                }

                color[u] ? void(disets[parent][id].erase(d)) : void(disets[parent][id].push(d));

                if (not disets[parent][id].empty())
                {
                    dsets[parent].push(disets[parent][id].top());
                }

                if (~contrs[parent])
                {
                    best.erase(contrs[parent]);
                }

                contrs[parent] = contr(parent);

                if (~contrs[parent])
                {
                    best.push(contrs[parent]);
                }
            }

            if (color[u])
            {
                --cnt_white;
                color[u] = false;
            }
            else
            {
                ++cnt_white;
                color[u] = true;
            }
        }
        else
        {
            if (cnt_white == 1)
            {
                std::cout << "0\n";
            }
            else if (cnt_white)
            {
                std::cout << std::max(best.top(), 0) << '\n';
            }
            else
            {
                std::cout << "They have disappeared.\n";
            }
        }
    }

    return 0;
}