/**
 * => P3988 [SHOI2013] 发牌 ( @c 普及+/提高− )
 *
 * -> https://www.luogu.com.cn/problem/P3988
 *
 * Submissions ~> https://www.luogu.com.cn/record/156995382 By huanhuanonly
 *
 * @b Split-merge-treap
 *
 * @from: https://www.luogu.com.cn/training/147262#problems
 *
 * ----April 25, 2024 [15h:40m:38s]----
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

    static inline std::mt19937 rng;

    std::vector<node> tree;
    int root = 0;

    Treap() : tree(1) { }

    int push_node(int value)
    {
        tree.push_back({});

        tree.back().key = rng();
        tree.back().value = value;
        tree.back().size = 1;

        return tree.size() - 1;
    }

    void push_up(int u)
    {
        tree[u].size = tree[tree[u].ls].size + tree[tree[u].rs].size + 1;
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
        {
            return u + v;
        }

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
        root = merge(root, push_node(value));
    }

    int pop_front()
    {
        int x;
        split(root, 1, x, root);
        return tree[x].value;
    }

    void loop_forward(int k)
    {
        int x, y;
        split(root, k, x, y);
        root = merge(y, x);
    }

    int size()
    {
        return tree[root].size;
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

    for (int i = 1; i <= n; ++i)
    {
        tree.insert(i);
    }

    for (int i = 1; i <= n; ++i)
    {
        int k;
        std::cin >> k;

        tree.loop_forward(k % tree.size());
        std::cout << tree.pop_front() << '\n';
    }

    return 0;
}