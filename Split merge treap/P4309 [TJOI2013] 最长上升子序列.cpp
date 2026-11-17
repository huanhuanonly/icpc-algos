/**
 * => P4309 [TJOI2013] 最长上升子序列 ( @c 提高 )
 *
 * -> https://www.luogu.com.cn/problem/P4309
 *
 * Submissions ~> https://www.luogu.com.cn/record/157390231 By huanhuanonly
 *
 * @b Split-merge-treap
 *
 * @from: https://www.luogu.com.cn/training/147262#problems
 *
 * ----April 29, 2024 [11h:06m:06s]----
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

        int dp, max;
        int size;
    };

    std::vector<node> tree;
    int root = 0;

    Treap() : tree(1) { }

    int push_node(int value)
    {
        static std::mt19937 rng;

        tree.push_back({});

        tree.back().key = rng();
        tree.back().value = value;
        tree.back().size = 1;

        return tree.size() - 1;
    }

    void push_up(int u)
    {
        tree[u].size = tree[tree[u].ls].size + tree[tree[u].rs].size + 1;
        tree[u].max = std::max({tree[tree[u].ls].max, tree[tree[u].rs].max, tree[u].dp});
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

    int insert(int k, int value)
    {
        int x, y;
        split(root, k - 1, x, y);

        int dp = tree[x].max + 1;

        int nd = push_node(value);
        tree[nd].dp = dp;
        tree[nd].max = dp;

        root = merge(x, merge(nd, y));

        return tree[root].max;
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

    for (int i = 1, x; i <= n; ++i)
    {
        std::cin >> x;
        std::cout << tree.insert(x + 1, i) << '\n';
    }

    return 0;
}