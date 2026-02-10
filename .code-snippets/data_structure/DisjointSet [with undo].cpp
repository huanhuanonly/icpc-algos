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

        _M_history.emplace(
            std::make_pair(_M_tree[fv].parent, _M_tree[fv].parent),
            std::make_pair(_M_tree[fu].size, _M_tree[fu].size));
        
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
    size(size_type u) const
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