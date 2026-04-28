template<typename _CapacityT = int, typename _CostT = int>
requires
    requires(_CostT __cost) { { -__cost } -> std::convertible_to<_CostT>; } and
    (not std::unsigned_integral<_CostT>)
class SpfaDinic
{
public:
    
    using size_type = int;
    using capacity_type = _CapacityT;
    using cost_type = _CostT;

    struct edge
    {
        size_type to;
        size_type rid;

        capacity_type cap;
        cost_type cost;
    };

    static constexpr size_type rid_mask = size_type{1} << sizeof(size_type) * 8 - 1;

    explicit
    SpfaDinic(size_type __n = 0) : _M_e(__n), _M_cg(__n), _M_vis(__n), _M_cur(__n)
    { }

    void
    add_edge(size_type __from, size_type __to, capacity_type __cap, cost_type __cost)
    {
        _M_e[__from].emplace_back(__to, size_type(_M_e[__to].size()) | rid_mask, __cap, __cost);
        _M_e[__to].emplace_back(__from, size_type(_M_e[__from].size()) - 1, capacity_type{}, -__cost);
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

    [[nodiscard]] cost_type
    current_cost() const noexcept
    { return _M_cost; }

    template<typename _Comp = std::ranges::less, typename _Proj = std::identity>
    cost_type
    build_cost_graph(
        size_type __source,
        size_type __sink,
        cost_type __inf = std::numeric_limits<cost_type>::max(),
        _Comp __comp = {},
        _Proj __proj = {})
    {
        _M_cg.assign(_M_cg.size(), __inf);
        _M_vis.assign(_M_vis.size(), false);
        _M_cur.assign(_M_cur.size(), size_type{});

        std::queue<size_type> que;
        que.push(__source);
        _M_cg[__source] = cost_type{};

        while (not que.empty())
        {
            const auto u = que.front();
            que.pop();

            _M_vis[u] = false;

            for (const edge& i : _M_e[u])
            {
                if (i.cap and __comp(__proj(_M_cg[u] + i.cost), __proj(_M_cg[i.to])))
                {
                    _M_cg[i.to] = _M_cg[u] + i.cost;

                    if (not _M_vis[i.to])
                    {
                        _M_vis[i.to] = true;
                        que.push(i.to);
                    }
                }
            }
        }

        return _M_cg[__sink];
    }

    cost_type
    build_min_cost_graph(size_type __source, size_type __sink)
    { return build_cost_graph(__source, __sink, std::numeric_limits<cost_type>::max(), std::ranges::less{}); }
    
    cost_type
    build_max_cost_graph(size_type __source, size_type __sink)
    { return build_cost_graph(__source, __sink, std::numeric_limits<cost_type>::min(), std::ranges::greater{}); }

    capacity_type
    augment_flow(size_type __source, size_type __sink)
    {
        const auto flow = _M_augment_flow(__source, __sink, std::numeric_limits<capacity_type>::max());
        _M_flow += flow;
        return flow;
    }

    struct cost_flow
    {
        cost_type     cost;
        capacity_type flow;
    };

    cost_flow
    min_cost_feasible_flow(size_type __source, size_type __sink)
    {
        while (build_min_cost_graph(__source, __sink) < cost_type{})
        {
            while (augment_flow(__source, __sink));
        }

        return cost_flow{.cost = _M_cost, .flow = _M_flow};
    }
    
    cost_flow
    max_cost_feasible_flow(size_type __source, size_type __sink)
    {
        while (build_max_cost_graph(__source, __sink) > cost_type{})
        {
            while (augment_flow(__source, __sink));
        }
        
        return cost_flow{.cost = _M_cost, .flow = _M_flow};
    }

    cost_flow
    min_cost_max_flow(size_type __source, size_type __sink)
    {
        while (build_min_cost_graph(__source, __sink) != std::numeric_limits<cost_type>::max())
        {
            while (augment_flow(__source, __sink));
        }

        return cost_flow{.cost = _M_cost, .flow = _M_flow};
    }

    cost_flow
    max_cost_max_flow(size_type __source, size_type __sink)
    {
        while (build_max_cost_graph(__source, __sink) != std::numeric_limits<cost_type>::min())
        {
            while (augment_flow(__source, __sink));
        }

        return cost_flow{.cost = _M_cost, .flow = _M_flow};
    }

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
        _M_cost = cost_type{};
    }

    void
    resize(size_type __n)
    {
        _M_e.resize(__n);
        _M_cg.resize(__n);
        _M_vis.resize(__n);
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
        _M_cost = cost_type{};
    }

private:

    capacity_type
    _M_augment_flow(size_type __u, size_type __sink, capacity_type __limit)
    {
        if (__u == __sink)
        {
            return __limit;
        }

        _M_vis[__u] = true;

        while (_M_cur[__u] < size_type(_M_e[__u].size()))
        {
            edge& i = _M_e[__u][_M_cur[__u]];
            ++_M_cur[__u];

            if (_M_cg[__u] + i.cost == _M_cg[i.to] and i.cap and not _M_vis[i.to])
            {
                if (const auto flow = _M_augment_flow(i.to, __sink, std::min(__limit, i.cap)); flow)
                {
                    i.cap -= flow;
                    _M_e[i.to][i.rid & ~rid_mask].cap += flow;

                    _M_cost += flow * i.cost;

                    _M_vis[__u] = false;
                    return flow;
                }

                _M_cg[i.to] = std::numeric_limits<cost_type>::max();
            }
        }

        _M_vis[__u] = false;
        return capacity_type{};
    }

    std::vector<std::vector<edge>> _M_e;
    std::vector<cost_type> _M_cg;

    std::vector<bool> _M_vis;
    std::vector<size_type> _M_cur;

    capacity_type _M_flow{};
    cost_type _M_cost{};
};