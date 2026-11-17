/**
 * => P4743 [Wind Festival] Energy Center ( @c 省选/NOI- )
 *
 * -> https://www.luogu.com.cn/problem/P4743
 *
 * Submissions ~> https://www.luogu.com.cn/record/156988043 By huanhuanonly
 *
 * @b Split-merge-treap
 *
 * @from: https://www.luogu.com.cn/training/147262#problems
 *
 * ----April 25, 2024 [14h:07m:04s]----
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

        int size;
        std::vector<int> value;
        std::vector<int> sum;

        // Random number generator
        static inline std::mt19937 rng;

        node(std::vector<int>&& val)
            : ls(0), rs(0), key(rng()), size(1), value(val), sum(value)
        { }
    };

    std::vector<node> tree;

    int root = 0;

    Treap(int m) : tree(1, node(std::vector<int>(m))) { tree[0].size = 0; }

    int push_node(std::vector<int>&& value)
    {
        tree.emplace_back(node(std::move(value)));
        return tree.size() - 1;
    }

    void push_up(int u)
    {
        tree[u].size = tree[tree[u].ls].size + tree[tree[u].rs].size + 1;

        for (int i = 0; i < tree[u].value.size(); ++i)
        {
            tree[u].sum[i] = tree[tree[u].ls].sum[i] + tree[tree[u].rs].sum[i] + tree[u].value[i];
        }
    }

    void split(int u, int k, int& rx, int& ry)
    {
        if (u == 0)
        {
            rx = ry = 0;
            return;
        }

        if (k <= tree[tree[u].ls].size)
        {
            ry = u;
            split(tree[u].ls, k, rx, tree[u].ls);
        }
        else if (k == tree[tree[u].ls].size + 1)
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

    int size() const
    {
        return tree[root].size;
    }

    void insert(std::vector<int>&& value)
    {
        root = merge(root, push_node(std::move(value)));
    }

    void insert(int pos, std::vector<int>&& value)
    {
        int x, y;
        split(root, pos, x, y);

        root = merge(merge(x, push_node(std::move(value))), y);
    }

    void erase(int k)
    {
        int x, y, z;
        split(root, k, x, y);
        split(x, k - 1, x, z);

        root = merge(merge(x, merge(tree[z].ls, tree[z].rs)), y);
    }

    void getsum(std::ostream& os, int l, int r)
    {
        int x, y, z;
        split(root, l - 1, x, y);
        split(y, r - l + 1, y, z);

        for (const auto& i : tree[y].sum)
            os << i << ' ';

        os << '\n';

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

    int n, m;
    std::cin >> n >> m;

    Treap tree(m);

    for (int i = 0; i < n; ++i)
    {
        std::vector<int> v(m);

        int k;
        std::cin >> k;

        for (int j = 0; j < k; ++j)
        {
            int x, y;
            std::cin >> x >> y;

            v[x] = y;
        }

        tree.insert(std::move(v));
    }

    int q;
    std::cin >> q;

    std::string s;

    while (q--)
    {
        std::cin >> s;

        if (s == "I")
        {
            int pos;
            std::cin >> pos;

            std::vector<int> v(m);

            int k;
            std::cin >> k;

            for (int i = 0; i < k; ++i)
            {
                int x, y;
                std::cin >> x >> y;

                v[x] = y;
            }

            tree.insert(pos, std::move(v));
        }
        else if (s == "D")
        {
            int pos;
            std::cin >> pos;

            tree.erase(pos);
        }
        else if (s == "QA")
        {
            std::cout << tree.size() << '\n';
        }
        else if (s == "QS")
        {
            int l, r;
            std::cin >> l >> r;

            tree.getsum(std::cout, l, r);
        }
    }

    std::cout << "end";

    return 0;
}