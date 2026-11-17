/**
 * => P5338 [TJOI2019] 甲苯先生的滚榜 ( @c 省选/NOI- )
 *
 * -> https://www.luogu.com.cn/problem/P5338
 *
 * Submissions ~> https://www.luogu.com.cn/record/157409873 By huanhuanonly
 *
 * @b Split-merge-treap
 *
 * @from: https://www.luogu.com.cn/training/147262#problems
 *
 * ----April 29, 2024 [16h:19m:54s]----
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

        struct value_t
        {
            uint counting, timing;

            bool operator<(const value_t& rv) const
            {
                if (counting != rv.counting)
                    return counting < rv.counting;
                else
                    return timing > rv.timing;
            }

        } value;

        int size;

        static inline std::mt19937 rng;

        node() : ls(0), rs(0), key(rng()), value{0, 0}, size(0) { }
    };

    std::vector<node> tree;
    int root = 0;

    int last_erased = 0;

    Treap() : tree(1) { }

    int push_node(const node::value_t& value)
    {
        if (last_erased)
        {
            int res = last_erased;
            last_erased = 0;

            tree[res].ls = tree[res].rs = 0;
            tree[res].value = value;
            tree[res].size = 1;

            return res;
        }
        else
        {
            tree.push_back({});
            tree.back().value = value;
            tree.back().size = 1;

            return tree.size() - 1;
        }
    }

    void push_up(int u)
    {
        tree[u].size = tree[tree[u].ls].size + tree[tree[u].rs].size + 1;
    }

    void split(int u, const node::value_t& value, int& rx, int& ry)
    {
        if (u == 0)
        {
            rx = ry = 0;
            return;
        }

        if (tree[u].value < value)
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

    int insert(const node::value_t& value)
    {
        int x, y;
        split(root, {value.counting, value.timing - 1}, x, y);

        int res = tree[x].size;
        root = merge(x, merge(push_node(value), y));

        return res;
    }

    void erase(const node::value_t& value)
    {
        int x, y, z;
        split(root, {value.counting, value.timing - 1}, x, y);
        split(y, value, y, z);

        last_erased = y;

        root = merge(x, merge(merge(tree[y].ls, tree[y].rs), z));
    }
};

uint get(uint& seed, uint last, uint m)
{
    seed = seed * 17 + last;
    return seed % m + 1;
}

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __localhost
    ::freopen("Input.txt", "r", stdin);
    ::freopen("Output.txt", "w", stdout);
#endif

    int _;
    std::cin >> _;

    uint last = 7;

    while (_--)
    {
        uint m, n, seed;
        std::cin >> m >> n >> seed;

        std::vector<Treap::node::value_t> v(m + 1);

        Treap tree;

        for (int i = 1; i <= n; ++i)
        {
            int Ria = get(seed, last, m);
            int Rib = get(seed, last, m);

            tree.erase(v[Ria]);

            v[Ria].counting += 1;
            v[Ria].timing += Rib;

            last = tree.insert(v[Ria]);

            std::cout << last << '\n';
        }
    }

    return 0;
}