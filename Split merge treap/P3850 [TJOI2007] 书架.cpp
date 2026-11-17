/**
 * => P3850 [TJOI2007] 书架 ( @c 提高 )
 *
 * -> https://www.luogu.com.cn/problem/P3850
 *
 * Submissions ~> https://www.luogu.com.cn/record/157381570 By huanhuanonly
 *
 * @b Split-merge-treap
 *
 * @from: https://www.luogu.com.cn/training/147262#problems
 *
 * ----April 28, 2024 [23h:24m:01s]----
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
        int key;
        std::string value;

        int size;
    };

    std::vector<node> tree;
    int root = 0;

    Treap() : tree(1) { }

    int push_node(const std::string& value)
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

    void insert(const std::string& value)
    {
        root = merge(root, push_node(value));
    }

    void insert(int pos, const std::string& value)
    {
        int x, y;
        split(root, pos, x, y);
        root = merge(x, merge(push_node(value), y));
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

    std::string s;

    for (int i = 0; i < n; ++i)
    {
        std::cin >> s;
        tree.insert(s);
    }

    int m;
    std::cin >> m;

    for (int i = 0, x; i < m; ++i)
    {
        std::cin >> s >> x;
        tree.insert(x, s);
    }

    int q;
    std::cin >> q;

    while (q--)
    {
        int x;
        std::cin >> x;

        std::cout << tree.at(x + 1).value << '\n';
    }

    return 0;
}