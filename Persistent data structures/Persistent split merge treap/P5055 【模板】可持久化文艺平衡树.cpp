/**
 * => P5055 【模板】可持久化文艺平衡树 ( @c 省选/NOI- )
 *
 * -> https://www.luogu.com.cn/problem/P5055
 *
 * Submissions ~> https://www.luogu.com.cn/record/158312585 By huanhuanonly
 *
 * @b Persistent-split-merge-treap
 *
 * @from: https://www.luogu.com.cn/training/147262#problems
 *
 * @note The push_down() function must be durable because it changes
 *       the historical version of the tree. The merge() function will
 *       call the push_down() function, so the merge() function must
 *       also be persistent (create nodes on the path)
 *
 * ----May 07, 2024 [18h:27m:32s]----
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

        bool reversed;
        llong sum;
    };

    std::vector<node> tree;
    std::vector<int>  root;

    Treap() : tree(1), root(1) { tree.reserve(int(5e5 + 1) * 50); }

    int push_node(int value)
    {
        static std::mt19937 rng;

        tree.push_back({});
        tree.back().key = rng();
        tree.back().value = value;
        tree.back().sum = value;
        tree.back().size = 1;

        return tree.size() - 1;
    }

    int push_node(const node& nd)
    {
        tree.push_back(nd);
        return tree.size() - 1;
    }

    void push_up(int u)
    {
        tree[u].size = tree[tree[u].ls].size + tree[tree[u].rs].size + 1;
        tree[u].sum = tree[tree[u].ls].sum + tree[tree[u].rs].sum + tree[u].value;
    }

    void push_down(int u)
    {
        if (tree[u].reversed)
        {
            if (tree[u].ls)
                tree[u].ls = push_node(tree[tree[u].ls]);

            if (tree[u].rs)
                tree[u].rs = push_node(tree[tree[u].rs]);

            std::swap(tree[u].ls, tree[u].rs);

            tree[tree[u].ls].reversed = not tree[tree[u].ls].reversed;
            tree[tree[u].rs].reversed = not tree[tree[u].rs].reversed;

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

        u = push_node(tree[u]);
        push_down(u);

        if (tree[tree[u].ls].size >= k)
        {
            ry = u;
            split(tree[u].ls, k, rx, tree[u].ls);
        }
        else if (tree[tree[u].ls].size + 1 == k)
        {
            rx = u;

            if (tree[u].rs)
                ry = push_node(tree[tree[u].rs]);
            else
                ry = 0;

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
            u = push_node(tree[u]);
            push_down(u);

            tree[u].rs = merge(tree[u].rs, v);
            push_up(u);
            return u;
        }
        else
        {
            v = push_node(tree[v]);
            push_down(v);

            tree[v].ls = merge(u, tree[v].ls);
            push_up(v);
            return v;
        }
    }

    void insert(int rt, int k, int value)
    {
        int x, y;
        split(root[rt], k, x, y);
        root.push_back(merge(x, merge(push_node(value), y)));
    }

    void erase(int rt, int k)
    {
        int x, y, z;
        split(root[rt], k - 1, x, y);
        split(y, 1, y, z);

        root.push_back(merge(x, merge(merge(tree[y].ls, tree[y].rs), z)));
    }

    void reverse(int rt, int l, int r)
    {
        int x, y, z;
        split(root[rt], l - 1, x, y);
        split(y, r - l + 1, y, z);

        tree[y].reversed = not tree[y].reversed;

        root.push_back(merge(x, merge(y, z)));
    }

    llong sum_of(int rt, int l, int r)
    {
        int x, y, z;
        split(root[rt], l - 1, x, y);
        split(y, r - l + 1, y, z);

        llong sum = tree[y].sum;

        root.push_back(merge(x, merge(y, z)));

        return sum;
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

    llong lastans = 0;

    Treap tree;

    for (int i = 0; i < n; ++i)
    {
        llong v, opt;
        std::cin >> v >> opt;

        switch (opt)
        {
            case 1:
            {
                llong p, x;
                std::cin >> p >> x;

                p ^= lastans;
                x ^= lastans;

               tree.insert(v, p, x);
               break;
            }

            case 2:
            {
                llong p;
                std::cin >> p;

                p ^= lastans;

                tree.erase(v, p);
                break;
            }

            case 3:
            {
                llong l, r;
                std::cin >> l >> r;

                l ^= lastans;
                r ^= lastans;

                tree.reverse(v, l, r);
                break;
            }

            case 4:
            {
                llong l, r;
                std::cin >> l >> r;

                l ^= lastans;
                r ^= lastans;

                lastans = tree.sum_of(v, l, r);
                std::cout << lastans << '\n';
                break;
            }
        }
    }

    return 0;
}