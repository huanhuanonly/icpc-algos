/**
 * => P2710 数列 ( @c 省选/NOI- )
 *
 * -> https://www.luogu.com.cn/problem/P2710
 *
 * Submissions ~> https://www.luogu.com.cn/record/158425662 By huanhuanonly
 *
 * @b Split-merge-treap
 *
 * @from: https://www.luogu.com.cn/training/147262#problems
 *
 * ----May 08, 2024 [20h:45m:32s]----
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
        int size, sum;

        bool reversed;
        int same;

        enum { nsame = -5201314 };

        int ml, mr, max;
    };

    std::vector<node> tree;
    int root = 0;

    std::stack<int, std::vector<int>> st;

    Treap() : tree(1)
    {
        tree[0].max = INT_MIN / 2 + 1;
    }

    int push_node(int value)
    {
        static std::mt19937 rng;

        int u;

        if (not st.empty())
        {
            u = st.top();
            st.pop();
            tree[u] = node{};
        }
        else
        {
            tree.push_back({});
            u = tree.size() - 1;
        }

        tree[u].key = rng();
        tree[u].value = value;
        tree[u].size = 1;
        tree[u].sum = value;
        tree[u].same = tree[u].nsame;

        tree[u].max = value;
        tree[u].ml = tree[u].mr = std::max(0, value);
        return u;
    }

    void push_up(int u)
    {
        tree[u].size = tree[tree[u].ls].size + tree[tree[u].rs].size + 1;
        tree[u].sum = tree[tree[u].ls].sum + tree[tree[u].rs].sum + tree[u].value;

        tree[u].ml = std::max(tree[tree[u].ls].ml, tree[tree[u].ls].sum + tree[u].value + tree[tree[u].rs].ml);
        tree[u].mr = std::max(tree[tree[u].rs].mr, tree[tree[u].rs].sum + tree[u].value + tree[tree[u].ls].mr);

        tree[u].max = std::max({tree[tree[u].ls].max, tree[tree[u].rs].max, tree[tree[u].ls].mr + tree[u].value + tree[tree[u].rs].ml});
    }

    void add_reverse(int u)
    {
        tree[u].reversed ^= 1;

        std::swap(tree[u].ls, tree[u].rs);
        std::swap(tree[u].ml, tree[u].mr);
    }

    void add_same(int u, int same)
    {
        tree[u].value = tree[u].same = same;
        tree[u].sum = same * tree[u].size;

        if (same > 0)
        {
            tree[u].max = tree[u].ml = tree[u].mr = tree[u].sum;
        }
        else
        {
            tree[u].max = same;
            tree[u].ml = tree[u].mr = 0;
        }
    }

    void push_down(int u)
    {
        if (tree[u].same != tree[u].nsame)
        {
            if (tree[u].ls)
                add_same(tree[u].ls, tree[u].same);

            if (tree[u].rs)
                add_same(tree[u].rs, tree[u].same);

            tree[u].same = tree[u].nsame;
        }

        if (tree[u].reversed)
        {
            add_reverse(tree[u].ls);
            add_reverse(tree[u].rs);

            tree[u].reversed = false;
        }
    }

    void split(int u, int k, int& rx, int& ry)
    {
        if (u == 0)
        {
            rx = ry = 0;
            return;
        }

        push_down(u);

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
            push_down(u);
            tree[u].rs = merge(tree[u].rs, v);
            push_up(u);
            return u;
        }
        else
        {
            push_down(v);
            tree[v].ls = merge(u, tree[v].ls);
            push_up(v);
            return v;
        }
    }

    void insert(int k, const std::vector<int>& v)
    {
        int x, y;
        split(root, k, x, y);

        for (const auto& i : v)
            x = merge(x, push_node(i));

        root = merge(x, y);
    }

    void inorder(int u, auto func)
    {
        if (u == 0)
            return;

        push_down(u);

        inorder(tree[u].ls, func);

        func(u);

        inorder(tree[u].rs, func);
    }

    void erase(int k, int n)
    {
        int x, y, z;
        split(root, k - 1, x, y);
        split(y, n, y, z);

        inorder(y, [&](int u) -> void { st.push(u); });

        root = merge(x, z);
    }

    void reverse(int k, int n)
    {
        int x, y, z;
        split(root, k - 1, x, y);
        split(y, n, y, z);

        add_reverse(y);

        root = merge(x, merge(y, z));
    }

    void makesame(int k, int n, int value)
    {
        int x, y, z;
        split(root, k - 1, x, y);
        split(y, n, y, z);

        add_same(y, value);

        root = merge(x, merge(y, z));
    }

    int sum_of(int k, int n)
    {
        int x, y, z;
        split(root, k - 1, x, y);
        split(y, n, y, z);

        int sum = tree[y].sum;

        root = merge(x, merge(y, z));
        return sum;
    }

    int at(int k)
    {
        int x, y, z;
        split(root, k - 1, x, y);
        split(y, 1, y, z);

        int sum = tree[y].value;

        root = merge(x, merge(y, z));
        return sum;
    }

    int maxsum_of_sub(int k, int n)
    {
        int x, y, z;
        split(root, k - 1, x, y);
        split(y, n, y, z);

        int sum = tree[y].max;

        root = merge(x, merge(y, z));
        return sum;
    }
};

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int n, m;
    std::cin >> n >> m;

    std::vector<int> v(n);

    for (int i = 0; i < n; ++i)
        std::cin >> v[i];

    Treap tree;
    tree.insert(0, v);

    std::string opt;

    while (m--)
    {
        std::cin >> opt;

        if (opt == "INSERT")
        {
            int x, n;
            std::cin >> x >> n;

            v.resize(n);

            for (int i = 0; i < n; ++i)
                std::cin >> v[i];

            tree.insert(x, v);
        }
        else if (opt == "DELETE")
        {
            int x, n;
            std::cin >> x >> n;

            tree.erase(x, n);
        }
        else if (opt == "REVERSE")
        {
            int x, n;
            std::cin >> x >> n;

            tree.reverse(x, n);
        }
        else if (opt == "MAKE-SAME")
        {
            int x, n, t;
            std::cin >> x >> n >> t;

            tree.makesame(x, n, t);
        }
        else if (opt == "GET-SUM")
        {
            int x, n;
            std::cin >> x >> n;

            std::cout << tree.sum_of(x, n) << '\n';
        }
        else if (opt == "GET")
        {
            int x;
            std::cin >> x;

            std::cout << tree.at(x) << '\n';
        }
        else if (opt == "MAX-SUM")
        {
            int x, n;
            std::cin >> x >> n;

            std::cout << tree.maxsum_of_sub(x, n) << '\n';
        }
    }

    return 0;
}