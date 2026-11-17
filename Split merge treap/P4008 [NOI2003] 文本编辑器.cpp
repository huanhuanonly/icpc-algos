/**
 * => P4008 [NOI2003] 文本编辑器 ( @c 提高+/省选− )
 *
 * -> https://www.luogu.com.cn/problem/P4008
 *
 * Submissions ~> https://www.luogu.com.cn/record/157450760 By huanhuanonly
 *
 * @b Split-merge-treap
 *
 * @from: https://www.luogu.com.cn/training/147262#problems
 *
 * ----April 29, 2024 [21h:33:06s]----
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
        char value;

        int size;
    };

    std::vector<node> tree;
    int root = 0;

    int cursor = 1;

    Treap() : tree(1) { tree.reserve(1200 * 1200 * 3); }

    static inline std::mt19937 rng;

    int push_node(char value)
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

    void move_to(int n)
    {
        cursor = n + 1;
    }

    void move(int n)
    {
        cursor += n;
    }

    void insert(int len)
    {
        int x, y;
        split(root, cursor - 1, x, y);

        for (int i = 0, c; i < len; ++i)
        {
            while (not((c = std::cin.get()) >= 32 and c <= 126));
            x = merge(x, push_node(c));
        }

        root = merge(x, y);
    }

    template<typename _Func>
    void inorder(int u, const _Func& func)
    {
        if (u == 0)
            return;

        inorder(tree[u].ls, func);

        func(u);

        inorder(tree[u].rs, func);
    }

    void erase(int len)
    {
        int x, y, z;
        split(root, cursor - 1, x, y);
        split(y, len, y, z);

        root = merge(x, z);
    }

    void output(int len)
    {
        int x, y, z;
        split(root, cursor - 1, x, y);
        split(y, len, y, z);

        inorder(y, [&](int u) -> void { std::cout.put(tree[u].value); });
        std::cout.put('\n');

        root = merge(x, merge(y, z));
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

    int t;
    std::cin >> t;

    Treap tree;

    int n;
    std::string opt;

    while (t--)
    {
        std::cin >> opt;

        if (opt == "Move")
        {
            std::cin >> n;
            tree.move_to(n);
        }
        else if (opt == "Insert")
        {
            std::cin >> n;
            tree.insert(n);
        }
        else if (opt == "Delete")
        {
            std::cin >> n;
            tree.erase(n);
        }
        else if (opt == "Get")
        {
            std::cin >> n;
            tree.output(n);
        }
        else if (opt == "Prev")
        {
            tree.move(-1);
        }
        else if (opt == "Next")
        {
            tree.move(1);
        }
    }

    return 0;
}