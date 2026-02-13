class DisjointSet
{
public:

    using size_type = int;

    struct node
    {
        size_type parent;
        size_type size;
    };

    explicit
    DisjointSet(size_type __n)
        : _M_tree(__n)
    { reset(); }

    [[nodiscard]] size_type
    find(size_type u) const
    { return is_root(u) ? u : find(_M_tree[u].parent); }

    bool
    unite(size_type u, size_type v)
    {
        const size_type fu = find(u);
        const size_type fv = find(v);

        if (fu != fv)
        {
            _M_tree[fv].parent = fu;
            _M_tree[fu].size += _M_tree[fv].size;
            return true;
        }
        else
        {
            return false;
        }
    }

    [[nodiscard]] bool
    is_root(size_type u) const
    { return _M_tree[u].parent == u; }

    [[nodiscard]] bool
    connected(size_type u, size_type v)
    { return find(u) == find(v); }

    void
    expand(size_type __n)
    {
        const size_type old_size = size();
        _M_tree.resize(old_size + __n);

        for (size_type i = old_size; i < old_size + __n; ++i)
        {
            _M_tree[i].parent = i;
            _M_tree[i].size = 1;
        }
    }

    void
    reset()
    {
        for (size_type i = 0; i < size(); ++i)
        {
            _M_tree[i].parent = i;
            _M_tree[i].size = 1;
        }
    }

    [[nodiscard]] size_type
    size()
    { return static_cast<size_type>(_M_tree.size()); }

    [[nodiscard]] size_type
    component_size(size_type u) const
    { return _M_tree[find(u)].size; }

private:

    std::vector<node> _M_tree;
};