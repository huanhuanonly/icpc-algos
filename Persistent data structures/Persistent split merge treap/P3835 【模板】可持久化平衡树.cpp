/**
 * 2026 省选赛前模板赛
 *
 * => P3835 【模板】可持久化平衡树 ( @c 省选/NOI- )
 *
 * -> https://www.luogu.com.cn/problem/P3835
 *
 * Submissions ~> https://www.luogu.com.cn/record/158187745 By huanhuanonly
 *
 * @b Persistent-split-merge-treap
 *
 * @from: https://www.luogu.com.cn/training/147262#problems
 *
 * @note The merge() function does not need to create a new node (this is optional),
 *       because the node has already been created when the split() function is called.
 *       erase() is an exception because it deletes the node by merging the left and right nodes,
 *       split() function does not pass through the subtree of its left and right nodes.
 *
 * @see https://www.cnblogs.com/chy-2003/p/11825302.html
 *
 * ----May 06, 2024 [10h:19m:42s]----
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
        int size;
    };

    std::vector<node> tree;
    std::vector<int> root;

    Treap() : tree(1), root(1)
    {
        tree.reserve(500005 * 50);
        root[0] = merge(push_node(-(1ll << 31) + 1), push_node((1ll << 31) - 1), false);
    }

    int push_node(int value)
    {
        static std::mt19937 rng;

        tree.push_back({});

        tree.back().key = rng();
        tree.back().value = value;
        tree.back().size = 1;

        return tree.size() - 1;
    }

    int push_node(const node& nd)
    {
        tree.push_back(nd);
        return tree.size() - 1;
    }

    int push_root(int rt)
    {
        root.push_back(rt);
        return root.size() - 1;
    }

    void push_up(int u)
    {
        tree[u].size = tree[tree[u].ls].size + tree[tree[u].rs].size + 1;
    }

    void split(int u, int value, int& rx, int& ry, bool ex = false)
    {
        if (u == 0)
        {
            rx = ry = 0;
            return;
        }

        if (ex)
            u = push_node(tree[u]);

        if (tree[u].value > value)
        {
            ry = u;
            split(tree[u].ls, value, rx, tree[u].ls, ex);
        }
        else
        {
            rx = u;
            split(tree[u].rs, value, tree[u].rs, ry, ex);
        }

        push_up(u);
    }

    int merge(int u, int v, bool ex = false)
    {
        if (u == 0 or v == 0)
            return u + v;

        if (tree[u].key > tree[v].key)
        {
            if (ex)
                u = push_node(tree[u]);

            tree[u].rs = merge(tree[u].rs, v, ex);
            push_up(u);
            return u;
        }
        else
        {
            if (ex)
                v = push_node(tree[v]);

            tree[v].ls = merge(u, tree[v].ls, ex);
            push_up(v);
            return v;
        }
    }

    void insert(int rt, int value)
    {
        int x, y;
        split(root[rt], value, x, y, true);

        root.push_back(merge(x, merge(push_node(value), y)));
    }

    void erase(int rt, int value)
    {
        int x, y, z;
        split(root[rt], value - 1, x, y, true);
        split(y, value, y, z, true);

        root.push_back(merge(x, merge(merge(tree[y].ls, tree[y].rs, true), z)));
    }

    int rank_of(int rt, int value)
    {
        int x, y;
        split(root[rt], value - 1, x, y, true);

        int res = tree[x].size;

        root.push_back(merge(x, y));
        return res;
    }

    int at(int rt, int k)
    {
        root.push_back(root[rt]);

        auto dfs = [this](auto self, int u, int k) -> int
        {
            if (u == 0)
                return 0;

            if (k <= tree[tree[u].ls].size)
                return self(self, tree[u].ls, k);
            else if (k == tree[tree[u].ls].size + 1)
                return tree[u].value;
            else
                return self(self, tree[u].rs, k - tree[tree[u].ls].size - 1);
        };

        return dfs(dfs, root.back(), k);
    }

    int prev(int rt, int value)
    {
        int x, y;
        split(root[rt], value - 1, x, y, true);

        int u = x;
        while (tree[u].rs)
            u = tree[u].rs;

        root.push_back(merge(x, y));
        return tree[u].value;
    }

    int next(int rt, int value)
    {
        int x, y;
        split(root[rt], value, x, y, true);

        int u = y;
        while (tree[u].ls)
            u = tree[u].ls;

        root.push_back(merge(x, y));
        return tree[u].value;
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

    int n;
    std::cin >> n;

    Treap tree;

    while (n--)
    {
        int v, opt, x;
        std::cin >> v >> opt >> x;

        switch (opt)
        {
            case 1:
            {
                tree.insert(v, x);
                break;
            }

            case 2:
            {
                tree.erase(v, x);
                break;
            }

            case 3:
            {
                std::cout << tree.rank_of(v, x) << '\n';
                break;
            }

            case 4:
            {
                std::cout << tree.at(v, x + 1) << '\n';
                break;
            }

            case 5:
            {
                std::cout << tree.prev(v, x) << '\n';
                break;
            }

            case 6:
            {
                std::cout << tree.next(v, x) << '\n';
                break;
            }
        }
    }

    return 0;
}