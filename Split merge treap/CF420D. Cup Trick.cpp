/**
 * Coder-Strike 2014 - Finals (online edition, Div. 1)
 *
 * => D. Cup Trick ( @c 2200 )
 *
 * -> https://codeforces.com/contest/420/problem/D
 *
 * Submissions ~> https://codeforces.com/contest/420/submission/259596857 By huanhuanonly
 *
 * @b Split-merge-treap
 *
 * @from: https://www.luogu.com.cn/training/147262#problems
 *
 * ----May 05, 2024 [15h:19m:45s]----
*/

#include <bits/stdc++.h>

using uint = unsigned int;
using llong = long long int;
using ullong = unsigned long long int;
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
    int root = 0;

    std::unordered_set<int> st;

    Treap() : tree(1) { }

    int push_node()
    {
        static std::mt19937 rng;

        tree.push_back({});

        tree.back().key = rng();
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

    void apply(int n)
    {
        tree.reserve(n + 1);

        while (n--)
        {
            root = merge(root, push_node());
        }
    }

    bool run(int value, int to)
    {
        int x, y, z;
        split(root, 1, x, y);

        if (not(tree[x].value == value or (tree[x].value == 0 and st.find(value) == st.end())))
        {
            root = merge(x, y);
            return false;
        }

        tree[x].value = value;
        st.insert(value);

        split(y, to - 1, y, z);

        root = merge(y, merge(x, z));
        return true;
    }

    std::vector<int> data()
    {
        std::vector<int> out;
        out.reserve(tree.size() + 1);

        std::vector<bool> vis(tree.size() + 1);

        std::function<void(int)> dfs = [&](int u) -> void
        {
            if (u == 0)
                return;

            dfs(tree[u].ls);

            out.push_back(tree[u].value);
            vis[tree[u].value] = true;

            dfs(tree[u].rs);
        };

        dfs(root);

        for (int i = 0, j = 1; i < out.size(); ++i)
        {
            if (out[i] == 0)
            {
                while (j < vis.size() and vis[j])
                    ++j;

                if (j < vis.size())
                    vis[j] = true;

                out[i] = j;
            }
        }

        return out;
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

    Treap tree;
    tree.apply(n);

    std::vector<std::pair<int, int>> log(m);

    for (auto& [i, j] : log)
        std::cin >> i >> j;

    for (int i = m - 1; i >= 0; --i)
    {
        if (tree.run(log[i].first, log[i].second) == false)
        {
            std::cout << -1;
            return 0;
        }
    }

    for (const auto& i : tree.data())
        std::cout << i << ' ';

    return 0;
}