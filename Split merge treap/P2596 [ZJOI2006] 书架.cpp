/**
 * => P2596 [ZJOI2006] 书架 ( @c 提高+/省选− )
 *
 * -> https://www.luogu.com.cn/problem/P2596
 *
 * Submissions ~> https://www.luogu.com.cn/record/157371583 By huanhuanonly
 *
 * @b Split-merge-treap
 *
 * @from: https://www.luogu.com.cn/training/147262#problems
 *
 * ----April 28, 2024 [21h:38m:32s]----
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

        int fa;
        int size;
    };

    std::vector<node> tree;
    int root = 0;

    // Record the node number in tree whose id is s
    std::vector<int> log;

    Treap(int n) : tree(1), log(n + 1) { }

    int push_node(int value)
    {
        tree.push_back({});

        static std::mt19937 rng;

        tree.back().key = rng();
        tree.back().value = value;
        tree.back().size = 1;

        return tree.size() - 1;
    }

    void push_up(int u)
    {
        tree[u].size = tree[tree[u].ls].size + tree[tree[u].rs].size + 1;

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

    void insert(int value)
    {
        int nd = push_node(value);

        root = merge(root, nd);
        log[value] = nd;
    }

    void move_to_front(int k)
    {
        int x, y, z;
        split(root, k - 1, x, y);
        split(y, 1, y, z);

        root = merge(y, merge(x, z));
    }

    void move_to_back(int k)
    {
        int x, y, z;
        split(root, k - 1, x, y);
        split(y, 1, y, z);

        root = merge(merge(x, z), y);
    }

    node& at(int k)
    {
        int x, y, z;
        split(root, k - 1, x, y);
        split(y, 1, y, z);

        node& res = tree[y];
        root = merge(x, merge(y, z));

        return res;
    }

    void swap(int u, int v)
    {
        int& x = at(u).value;
        int& y = at(v).value;

        std::swap(x, y);
        std::swap(log[x], log[y]);
    }

    int index_of(int value)
    {
        int u = log[value];

        int res = tree[tree[u].ls].size + 1;

        while (tree[u].fa)
        {
            if (tree[tree[u].fa].rs == u)
            {
                res += tree[tree[tree[u].fa].ls].size + 1;
            }

            u = tree[u].fa;
        }

        return res;
    }

    int id_of(int k)
    {
        return at(k).value;
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

    Treap tree(n);

    for (int i = 0, x; i < n; ++i)
    {
        std::cin >> x;
        tree.insert(x);
    }

    std::string opt;
    int s, t;

    while (m--)
    {
        std::cin >> opt;

        if (opt == "Top")
        {
            std::cin >> s;
            tree.move_to_front(tree.index_of(s));
        }
        else if (opt == "Bottom")
        {
            std::cin >> s;
            tree.move_to_back(tree.index_of(s));
        }
        else if (opt == "Insert")
        {
            std::cin >> s >> t;
            tree.swap(tree.index_of(s), tree.index_of(s) + t);
        }
        else if (opt == "Ask")
        {
            std::cin >> s;
            std::cout << tree.index_of(s) - 1 << '\n';
        }
        else if (opt == "Query")
        {
            std::cin >> s;
            std::cout << tree.id_of(s) << '\n';
        }
    }

    return 0;
}