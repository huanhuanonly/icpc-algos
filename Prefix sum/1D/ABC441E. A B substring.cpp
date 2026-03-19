/**
 * AtCoder Beginner Contest 441 (Promotion of Engineer Guild Fes)
 * 
 * => E - A > B substring ( @c 450 )
 * 
 * -> https://atcoder.jp/contests/abc441/tasks/abc441_e
 * 
 * Submissions ~> https://atcoder.jp/contests/abc441/submissions/72544687 By huanhuanonly
 * 
 * @b Prefix-sum and @b FHQ-Treap
 * 
 * ----January 17, 2026 [21h:48m:34s]----
*/

#include <bits/stdc++.h>

using int8 = signed char;
using int16 = short;
using int32 = int;
using int64 = long long;

using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long long;

#ifdef __GNUC__
using int128 = __int128;
using uint128 = unsigned __int128;
#endif

using real32 = float;
using real64 = double;
using real128 = long double;

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

    Treap() : tree(1) { }

    int push_node(int value)
    {
        static std::mt19937 rng;

        tree.emplace_back();
        
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

    void insert(int value)
    {
        int x, y;
        split(root, value, x, y);

        x = merge(x, push_node(value));
        root = merge(x, y);
    }

    void erase(int value)
    {
        int x, y, z;
        split(root, value, x, y);
        split(x, value - 1, x, z);

        root = merge(merge(x, merge(tree[z].ls, tree[z].rs)), y);
    }

    int rank_of(int value)
    {
        int x, y;
        split(root, value - 1, x, y);

        int res = tree[x].size + 1;
        root = merge(x, y);

        return res;
    }

    int count_greater(int value)
    {
        int x, y;
        split(root, value, x, y);
        
        int res = tree[y].size;
        root = merge(x, y);

        return res;
    }

    int at(int x)
    {
        std::function<int(int, int)> dfs = [&](int u, int k) -> int
        {
            if (k <= tree[tree[u].ls].size)
                return dfs(tree[u].ls, k);
            else if (k == tree[tree[u].ls].size + 1)
                return tree[u].value;
            else
                return dfs(tree[u].rs, k - tree[tree[u].ls].size - 1);
        };

        return dfs(root, x);
    }

    int prev(int value)
    {
        int x, y;
        split(root, value - 1, x, y);

        int size = tree[x].size;
        root = merge(x, y);

        return at(size);
    }

    int next(int value)
    {
        int x, y;
        split(root, value, x, y);

        int size = tree[x].size + 1;
        root = merge(x, y);

        return at(size);
    }
};

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int n;
    std::string s;

    std::cin >> n >> s;

    std::vector<int> v(n + 1);

    std::ranges::transform(s, v.begin() + 1, [](char c) -> int
    {
        if (c == 'A')
        {
            return +1;
        }
        else if (c == 'B')
        {
            return -1;
        }
        else
        {
            return 0;
        }
    });

    std::partial_sum(v.begin(), v.end(), v.begin());

    Treap treap;

    for (int i = 1; i <= n; ++i)
    {
        treap.insert(v[i]);
    }

    uint64 ans = 0;

    for (int i = 1; i <= n; ++i)
    {
        ans += treap.count_greater(v[i - 1]);
        treap.erase(v[i]);
    }

    std::cout << ans;

    return 0;
}