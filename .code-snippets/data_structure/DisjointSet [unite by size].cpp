class DisjointSet
{
public:

    using size_type = int;

    struct node
    {
        size_type parent;
        size_type size;
    };

    constexpr explicit
    DisjointSet(size_type __n = 0)
        : _M_tree(__n)
    { reset(); }

    [[nodiscard]] constexpr size_type
    find(size_type u) const noexcept
    { return is_root(u) ? u : find(_M_tree[u].parent); }

    constexpr bool
    unite(size_type u, size_type v) noexcept
    {
        size_type fu = find(u);
        size_type fv = find(v);

        if (fu != fv)
        {
            if (_M_tree[fu].size < _M_tree[fv].size)
            {
                std::swap(fu, fv);
            }

            _M_tree[fv].parent = fu;
            _M_tree[fu].size += _M_tree[fv].size;
            return true;
        }
        else
        {
            return false;
        }
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
        assert(__n >= 0);

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
    {
        for (size_type i = 0; i < size(); ++i)
        {
            _M_tree[i].parent = i;
            _M_tree[i].size = 1;
        }
    }

    [[nodiscard]] constexpr size_type
    size() const noexcept
    { return static_cast<size_type>(_M_tree.size()); }

    [[nodiscard]] constexpr size_type
    component_size(size_type u) const noexcept
    { return _M_tree[find(u)].size; }

private:

    std::vector<node> _M_tree;
};