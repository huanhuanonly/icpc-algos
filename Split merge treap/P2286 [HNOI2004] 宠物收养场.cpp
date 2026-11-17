/**
 * => P2286 [HNOI2004] 宠物收养场 ( @c 普及 )
 *
 * -> https://www.luogu.com.cn/problem/P2286
 *
 * Submissions ~> https://www.luogu.com.cn/record/156911396 By huanhuanonly
 *
 * @b Split-merge-treap
 *
 * @from: https://www.luogu.com.cn/training/147262#problems
 *
 * ----April 24, 2024 [16h:20m:44s]----
*/

#include <bits/stdc++.h>

using uint    = unsigned int;
using llong   = long long int;
using ullong  = unsigned long long int;
using ldouble = long double;

class Treap
{
public:

    using value_type = int;

    struct node
    {
        int ls, rs;
        value_type key, value;

        int size;
    };

    std::vector<node> tree;

    // Random number generator
    std::mt19937 rng;

    int root = 0;

    Treap() : tree(1) { }

    int push_node(value_type value)
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

    void split(int u, value_type value, int& rx, int& ry)
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

    int size() const
    {
        return tree[root].size;
    }

    void insert(value_type value)
    {
        int x, y;
        split(root, value, x, y);

        x = merge(x, push_node(value));
        root = merge(x, y);
    }

    void erase(value_type value)
    {
        int x, y, z;
        split(root, value, x, y);
        split(x, value - 1, x, z);

        root = merge(merge(x, merge(tree[z].ls, tree[z].rs)), y);
    }

    int rank_of(value_type value)
    {
        int x, y;
        split(root, value - 1, x, y);

        int res = tree[x].size + 1;
        root = merge(x, y);

        return res;
    }

    std::optional<value_type> at(int x)
    {
        std::function<std::optional<value_type>(int, int)> dfs = [&](int u, int k) -> std::optional<value_type>
        {
            if (u == 0)
                return std::nullopt;

            if (k <= tree[tree[u].ls].size)
                return dfs(tree[u].ls, k);
            else if (k == tree[tree[u].ls].size + 1)
                return tree[u].value;
            else
                return dfs(tree[u].rs, k - tree[tree[u].ls].size - 1);
        };

        return dfs(root, x);
    }

    std::optional<value_type> prev(value_type value)
    {
        int x, y;
        split(root, value - 1, x, y);

        int size = tree[x].size;
        root = merge(x, y);

        return at(size);
    }

    std::optional<value_type> next(value_type value)
    {
        int x, y;
        split(root, value, x, y);

        int size = tree[x].size + 1;
        root = merge(x, y);

        return at(size);
    }

    bool exist(value_type value)
    {
        int x, y;
        split(root, value, x, y);

        bool res = false;

        for (int u = x; u; u = tree[u].rs)
            if (tree[u].value == value)
                res = true;

        root = merge(x, y);

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

    Treap tree1, tree2;

    int n;
    std::cin >> n;

    ullong ans = 0;

    for (int i = 0; i < n; ++i)
    {
        int a, b;
        std::cin >> a >> b;

        if (a == 0)
        {
            if (tree2.size())
            {
                auto prev = tree2.prev(b);
                auto next = tree2.next(b);

                if (prev.has_value() and (next.has_value() == false or std::abs(*prev - b) <= std::abs(*next - b)))
                {
                    ans += std::abs(*prev - b);
                    tree2.erase(*prev);
                }
                else
                {
                    ans += std::abs(*next - b);
                    tree2.erase(*next);
                }
            }
            else
            {
                tree1.insert(b);
            }
        }
        else
        {
            if (tree1.size())
            {
                auto prev = tree1.prev(b);
                auto next = tree1.next(b);

                if (prev.has_value() and (next.has_value() == false or std::abs(*prev - b) <= std::abs(*next - b)))
                {
                    ans += std::abs(*prev - b);
                    tree1.erase(*prev);
                }
                else
                {
                    ans += std::abs(*next - b);
                    tree1.erase(*next);
                }
            }
            else
            {
                tree2.insert(b);
            }
        }

        ans %= 1000000;
    }

    std::cout << ans;

    return 0;
}