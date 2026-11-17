/**
 * 【LGR-038】洛谷5月月赛 R1
 *
 * => https://www.luogu.com.cn/problem/P3765 ( @c 省选/NOI- )
 *
 * -> https://www.luogu.com.cn/problem/P3765
 *
 * Submissions ~> https://www.luogu.com.cn/record/157324933 By huanhuanonly
 *
 * @b Split-merge-treap and @b Boyer–Moore-majority-vote-algorithm
 *
 * @from: https://www.luogu.com.cn/training/147262#problems
 *
 * ----April 28, 2024 [15h:30m:08s]----
*/

#include <bits/stdc++.h>

using uint    = unsigned int;
using llong   = long long int;
using ullong  = unsigned long long int;
using ldouble = long double;

/**
 * @brief Find the number that appears most often in the interval
*/
class Treap
{
public:

    struct node
    {
        int ls, rs;
        int key, value;
        int most, count;
        int number;
    };

    std::vector<node> tree;
    int root = 0;

    static inline std::mt19937 rng;

    Treap() : tree(1) { }

    int push_node(int number, int value)
    {
        tree.push_back({});

        tree.back().key = rng();
        tree.back().value = value;
        tree.back().most = value;
        tree.back().count = 1;
        tree.back().number = number;

        return tree.size() - 1;
    }

    void push_up(int u)
    {
        if (tree[tree[u].ls].most == tree[tree[u].rs].most)
        {
            tree[u].most = tree[tree[u].ls].most;
            tree[u].count = tree[tree[u].ls].count + tree[tree[u].rs].count;
        }
        else if (tree[tree[u].ls].count >= tree[tree[u].rs].count)
        {
            tree[u].most = tree[tree[u].ls].most;
            tree[u].count = tree[tree[u].ls].count - tree[tree[u].rs].count;
        }
        else
        {
            tree[u].most = tree[tree[u].rs].most;
            tree[u].count = tree[tree[u].rs].count - tree[tree[u].ls].count;
        }

        if (tree[u].count == 0)
        {
            tree[u].most = tree[u].value;
            tree[u].count = 1;
        }
        else
        {
            if (tree[u].value == tree[u].most)
                ++tree[u].count;
            else
                --tree[u].count;
        }
    }

    void split(int u, int number, int& rx, int& ry)
    {
        if (u == 0)
        {
            rx = ry = 0;
            return;
        }

        if (tree[u].number > number)
        {
            ry = u;
            split(tree[u].ls, number, rx, tree[u].ls);
        }
        else
        {
            rx = u;
            split(tree[u].rs, number, tree[u].rs, ry);
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

    void insert(int number, int value)
    {
        root = merge(root, push_node(number, value));
    }

    int getmax(int l, int r)
    {
        int x, y, z;
        split(root, l - 1, x, y);
        split(y, r, y, z);

        int res = tree[y].most;
        root = merge(x, merge(y, z));
        return res;
    }

    void change(int number, int value)
    {
        int x, y;
        split(root, number, x, y);

        int u = x;
        while (tree[u].rs)
            u = tree[u].rs;

        tree[u].value = value;
        root = merge(x, y);
    }
};

/**
 * @brief For everyone, fix who supports him
*/
class MultiTreap
{
public:

    struct node
    {
        int ls, rs;
        int key, value;

        int size;
    };

    static inline std::mt19937 rng;

    std::vector<int>  root;
    std::vector<node> tree;

    explicit MultiTreap(int n) : root(n), tree(1) { }

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

    void insert(int rti, int value)
    {
        int x, y;
        split(root[rti], value, x, y);

        root[rti] = merge(x, merge(push_node(value), y));
    }

    int size(int rti, int l, int r)
    {
        int x, y, z;
        split(root[rti], l - 1, x, y);
        split(y, r, y, z);

        int res = tree[y].size;
        root[rti] = merge(x, merge(y, z));

        return res;
    }

    void move(int from, int value, int to)
    {
        if (root[from] == root[to])
            return;

        int x, y, z;
        split(root[from], value - 1, x, y);
        split(y, value, y, z);

        root[from] = merge(x, z);

        split(root[to], value, x, z);
        root[to] = merge(x, merge(y, z));
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

    std::vector<int> v(n + 1);

    Treap tree;
    MultiTreap trees(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> v[i];
        tree.insert(i, v[i]);
        trees.insert(v[i], i);
    }

    for (int i = 1; i <= m; ++i)
    {
        int l, r, s, k;
        std::cin >> l >> r >> s >> k;

        if (int mx = tree.getmax(l, r); trees.size(mx, l, r) > (r - l + 1) / 2)
        {
            s = mx;
        }

        for (int j = 1, x; j <= k; ++j)
        {
            std::cin >> x;
            tree.change(x, s);
            trees.move(v[x], x, s);
            v[x] = s;
        }

        std::cout << s << '\n';
    }

    if (int mx = tree.getmax(1, n); trees.size(mx, 1, n) > n / 2)
        std::cout << mx << '\n';
    else
        std::cout << -1 << '\n';

    return 0;
}