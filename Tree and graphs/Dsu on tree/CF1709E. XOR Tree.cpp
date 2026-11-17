/**
 * Educational Codeforces Round 132 (Rated for Div. 2)
 *
 * => E. XOR Tree ( @c 2400 )
 *
 * -> https://codeforces.com/contest/1709/problem/E
 *
 * Submissions ~> https://codeforces.com/contest/1709/submission/256253760 By huanhuanonly
 *
 * @b Dsu-on-tree
 *
 * ----April 12, 2024 [22h:08m:52s]----
*/

#include <bits/stdc++.h>

using uint    = unsigned int;
using llong   = long long int;
using ullong  = unsigned long long int;
using ldouble = long double;

class DsuOnTree
{
public:

    const std::vector<std::vector<int>>& e;
    std::vector<int> v;

    struct node
    {
        int size, wson, xorsum;

        std::set<int> st;
    };

    std::vector<node> tree;

    int ans = 0;

    DsuOnTree(const std::vector<std::vector<int>>& __e, std::vector<int>&& __v)
        : e(__e), v(__v), tree(__e.size())
    {
        build(1, 1);
    }

    void build(int p, int fa)
    {
        tree[p].size = 1;
        tree[p].xorsum = tree[fa].xorsum ^ v[p];

        for (const auto& i : e[p])
        {
            if (i == fa)
                continue;

            build(i, p);

            tree[p].size += tree[i].size;

            if (tree[i].size > tree[tree[p].wson].size)
                tree[p].wson = i;
        }
    }

    void dfs(int p, int fa)
    {
        bool flag = true;

        tree[p].st.insert(tree[p].xorsum);

        for (const auto& i : e[p])
        {
            if (i == fa)
                continue;

            dfs(i, p);

            if (tree[i].st.size() > tree[p].st.size())
                std::swap(tree[i].st, tree[p].st);

            for (const auto& x : tree[i].st)
            {
                if (tree[p].st.find(x ^ v[p]) != tree[p].st.end())
                {
                    flag = false;
                    break;
                }
            }

            tree[p].st.merge(tree[i].st);
        }

        if (not flag)
        {
            ++ans;
            tree[p].st.clear();
        }
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

    std::vector<int> v(n + 1);

    for (int i = 1; i <= n; ++i)
        std::cin >> v[i];

    std::vector<std::vector<int>> e(n + 1);

    for (int i = 1; i < n; ++i)
    {
        int x, y;
        std::cin >> x >> y;

        e[x].push_back(y);
        e[y].push_back(x);
    }

    DsuOnTree tree(e, std::move(v));

    tree.dfs(1, 1);

    std::cout << tree.ans;

    return 0;
}