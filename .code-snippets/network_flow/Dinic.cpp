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