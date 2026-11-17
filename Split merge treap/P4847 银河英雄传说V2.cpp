/**
 * => P4847 银河英雄传说V2 ( @c 提高+/省选− )
 *
 * -> https://www.luogu.com.cn/problem/P4847
 *
 * Submissions ~> https://www.luogu.com.cn/record/157468020 By huanhuanonly
 *
 * @b Split-merge-treap
 *
 * @from: https://www.luogu.com.cn/training/147262#problems
 *
 * @note When maintaining the parent node, it must be reassigned after splitting
 *
 * ----April 30, 2024 [10h:04m:54s]----
*/

#include <bits/stdc++.h>

using uint    = unsigned int;
using llong   = long long int;
using ullong  = unsigned long long int;
using ldouble = long double;

class Treap
{
public:

    struct node
    {
        int ls, rs;
        int key, value;

        int fa, size;

        llong sum;
    };

    std::vector<node> tree;
    std::set<int> root;

    std::map<int, int> mp;

    explicit Treap(const std::vector<int>& v) : tree(1)
    {
        for (int i = 0; i < v.size(); ++i)
        {
            int nd = push_node(v[i]);
            root.insert(nd);
            mp[i + 1] = nd;
        }
    }

    int push_node(int value)
    {
        static std::mt19937 rng;

        tree.push_back({});

        tree.back().key = rng();
        tree.back().value = value;
        tree.back().sum = value;
        tree.back().size = 1;

        return tree.size() - 1;
    }

    void push_up(int u)
    {
        tree[u].size = tree[tree[u].ls].size + tree[tree[u].rs].size + 1;
        tree[u].sum  = tree[tree[u].ls].sum + tree[tree[u].rs].sum + tree[u].value;

        tree[u].fa = 0;

        if (tree[u].ls)
            tree[tree[u].ls].fa = u;
        if (tree[u].rs)
            tree[tree[u].rs].fa = u;
    }

    void split(int u, int k, int& rx, int& ry)
    {
        if (u == 0)
        {
            rx = ry = 0;
            return;
        }

        if (tree[tree[u].ls].size >= k)
        {
            ry = u;
            split(tree[u].ls, k, rx, tree[u].ls);
        }
        else if (tree[tree[u].ls].size + 1 == k)
        {
            rx = u;
            ry = tree[u].rs;
            tree[u].rs = 0;
        }
        else
        {
            rx = u;
            split(tree[u].rs, k - tree[tree[u].ls].size - 1, tree[u].rs, ry);
        }

        push_up(u);
    }

    int merge(int u, int v)
    {
        if (u == 0 or v == 0)
            return u + v;

        if (tree[u].key > tree[v].key)
        {
            tree[u].rs = merge(tree[u].rs, v);
            push_up(u);
            return u;
        }
        else
        {
            tree[v].ls = merge(u, tree[v].ls);
            push_up(v);
            return v;
        }
    }

    // root, index
    std::pair<int, int> root_of(int value)
    {
        int u = mp[value];
        int res = tree[tree[u].ls].size + 1;

        while (tree[u].fa)
        {
            if (tree[tree[u].fa].rs == u)
                res += tree[tree[tree[u].fa].ls].size + 1;

            u = tree[u].fa;
        }

        return std::make_pair(u, res);
    }

    void merge_sequence(int lv, int rv)
    {
        int lrt = root_of(lv).first;
        int rrt = root_of(rv).first;

        if (lrt == rrt)
            return;

        root.erase(lrt);

        auto nd = root.extract(rrt);
        nd.value() = merge(rrt, lrt);
        root.insert(std::move(nd));
    }

    void split_sequence(int value)
    {
        auto [u, index] = root_of(value);

        int nrt;

        auto nd = root.extract(u);

        split(u, index - 1, nd.value(), nrt);

        // The parent node must be reassigned
        tree[nd.value()].fa = 0;
        tree[nrt].fa = 0;

        root.insert(std::move(nd));
        root.insert(nrt);
    }

    llong sum_of_sequence(int lv, int rv)
    {
        auto [lrt, lid] = root_of(lv);
        auto [rrt, rid] = root_of(rv);

        if (lrt != rrt)
            return -1;

        if (lid > rid)
            std::swap(lid, rid);

        auto nd = root.extract(lrt);

        int x, y, z;
        split(lrt, lid - 1, x, y);
        split(y, rid - lid + 1, y, z);

        llong sum = tree[y].sum;

        nd.value() = merge(x, merge(y, z));
        root.insert(std::move(nd));
        return sum;
    }
};

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __localhost
    ::freopen("Input.txt", "r", stdin);
    ::freopen("Output.txt", "w", stdout);
#endif

    int n, m;
    std::cin >> n >> m;

    std::vector<int> v(n);

    for (int i = 0; i < n; ++i)
        std::cin >> v[i];

    Treap tree(v);

    char c;
    int x, y;

    while (m--)
    {
        std::cin >> c;

        switch (c)
        {
            case 'M':
                std::cin >> x >> y;
                tree.merge_sequence(x, y);
                break;

            case 'D':
                std::cin >> x;
                tree.split_sequence(x);
                break;

            case 'Q':
                std::cin >> x >> y;
                std::cout << tree.sum_of_sequence(x, y) << '\n';
                break;
        }
    }

    return 0;
}