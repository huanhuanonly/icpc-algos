class DisjointSet
{
public:

    using size_type = int;

    constexpr explicit
    DisjointSet(size_type __n = 0)
        : _M_parent(__n)
    { reset(); }

    [[nodiscard]] constexpr size_type
    find(size_type u) noexcept
    { return _M_parent[u] == u ? u : _M_parent[u] = find(_M_parent[u]); }

    constexpr bool
    unite(size_type u, size_type v) noexcept
    {
        const size_type fu = find(u);
        const size_type fv = find(v);

        if (fu != fv)
        {
            _M_parent[fv] = fu;
            return true;
        }
        else
        {
            return false;
        }
    }

    [[nodiscard]] constexpr bool
    connected(size_type u, size_type v) noexcept
    { return find(u) == find(v); }

    constexpr void
    expand(size_type __n)
    {
        assert(__n >= 0);

        const size_type size = static_cast<size_type>(_M_parent.size());
        _M_parent.resize(size + __n);
        std::iota(_M_parent.begin() + size, _M_parent.end(), size);
    }

    constexpr void
    reset() noexcept
    { std::iota(_M_parent.begin(), _M_parent.end(), 0); }

    [[nodiscard]] constexpr size_type
    size() const noexcept
    { return static_cast<size_type>(_M_parent.size()); }

private:

    std::vector<size_type> _M_parent;
};