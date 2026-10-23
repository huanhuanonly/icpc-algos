class RollbackDisjointSet
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
        std::pair<size_type, size_type> parent;
        std::pair<size_type, size_type> size;
    };

    constexpr explicit
    RollbackDisjointSet(size_type __n = 0)
        : _M_tree(__n)
    { for (size_type i = 0; i < __n; _M_tree[i] = node{.parent = i, .size = 1}, ++i); }

    [[nodiscard]] constexpr size_type
    find(size_type u) const noexcept
    { return is_root(u) ? u : find(_M_tree[u].parent); }

    constexpr bool
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
                {fv, _M_tree[fv].parent},
                {fu, _M_tree[fu].size  }});

        _M_tree[fv].parent = fu;
        _M_tree[fu].size += _M_tree[fv].size;

        return true;
    }

    [[nodiscard]] constexpr bool
    is_root(size_type u) const noexcept
    { return _M_tree[u].parent == u; }

    [[nodiscard]] constexpr bool
    connected(size_type u, size_type v) const noexcept
    { return find(u) == find(v); }

    constexpr void
    expand(size_type __n)
    {
        assert(_M_history.empty());

        const size_type old_size = size();
        _M_tree.resize(old_size + __n);

        for (size_type i = old_size; i < old_size + __n; ++i)
        {
            _M_tree[i].parent = i;
            _M_tree[i].size = 1;
        }
    }

    constexpr void
    reset() noexcept
    { rollback(0); }

    [[nodiscard]] constexpr size_type
    size() const
    { return static_cast<size_type>(_M_tree.size()); }

    [[nodiscard]] constexpr size_type
    component_size(size_type u) const
    { return _M_tree[find(u)].size; }

    [[nodiscard]] constexpr size_type
    checkpoint() const
    { return static_cast<size_type>(_M_history.size()); }

    constexpr void
    undo() noexcept
    {
        if (not _M_history.empty())
        {
            const auto& rec = _M_history.top();

            _M_tree[rec.parent.first].parent = rec.parent.second;
            _M_tree[rec.size.first].size = rec.size.second;

            _M_history.pop();
        }
    }

    constexpr void
    rollback(size_type __cp) noexcept
    { for (; checkpoint() > __cp; undo()); }

private:

    std::vector<node> _M_tree;
    std::stack<change_record, std::vector<change_record>> _M_history;
};