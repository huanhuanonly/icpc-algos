/**
 * 2026 省选赛前模板赛
 *
 * => P6136 【模板】普通平衡树（数据加强版） ( @c 提高+/省选− )
 *
 * -> https://www.luogu.com.cn/problem/P6136
 *
 * Submissions ~> https://www.luogu.com.cn/record/156859649 By huanhuanonly
 *
 * @b Split-merge-treap
 *
 * @from: https://www.luogu.com.cn/training/147262#problems
 *
 * ----April 23, 2024 [20h:49m:03s]----
*/

// #pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

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

    // Random number generator
    std::mt19937 rng;

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

    void split(int u, int value, int& rx, int& ry)
    {
        if (u == 0)
        {
            rx = ry = 0;
            return;
        }

        if (tree[u].value > value)
        {
            ry = u;
            split(tree[u].ls, value, rx, tree[u].ls);
        }
        else
        {
            rx = u;
            split(tree[u].rs, value, tree[u].rs, ry);
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
        int x, y;
        split(root, value, x, y);

        x = merge(x, push_node(value));
        root = merge(x, y);
    }

    void erase(int value)
    {
        int x, y, z;
        split(root, value, x, y);
        split(x, value - 1, x, z);

        root = merge(merge(x, merge(tree[z].ls, tree[z].rs)), y);
    }

    int rank_of(int value)
    {
        int x, y;
        split(root, value - 1, x, y);

        int res = tree[x].size + 1;
        root = merge(x, y);

        return res;
    }

    int at(int x)
    {
        std::function<int(int, int)> dfs = [&](int u, int k) -> int
        {
            if (k <= tree[tree[u].ls].size)
                return dfs(tree[u].ls, k);
            else if (k == tree[tree[u].ls].size + 1)
                return tree[u].value;
            else
                return dfs(tree[u].rs, k - tree[tree[u].ls].size - 1);
        };

        return dfs(root, x);
    }

    int prev(int value)
    {
        int x, y;
        split(root, value - 1, x, y);

        int size = tree[x].size;
        root = merge(x, y);

        return at(size);
    }

    int next(int value)
    {
        int x, y;
        split(root, value, x, y);

        int size = tree[x].size + 1;
        root = merge(x, y);

        return at(size);
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

    Treap tree;

    int n, m;
    std::cin >> n >> m;

    for (int i = 0, x; i < n; ++i)
    {
        std::cin >> x;
        tree.insert(x);
    }

    int last = 0;
    int ans = 0;

    while (m--)
    {
        int opt, x;
        std::cin >> opt >> x;

        x ^= last;

        switch (opt)
        {
            case 1:
                tree.insert(x);
                break;

            case 2:
                tree.erase(x);
                break;

            case 3:
                last = tree.rank_of(x);
                ans ^= last;
                break;

            case 4:
                last = tree.at(x);
                ans ^= last;
                break;

            case 5:
                last = tree.prev(x);
                ans ^= last;
                break;

            case 6:
                last = tree.next(x);
                ans ^= last;
                break;
        }
    }

    std::cout << ans;

    return 0;
}