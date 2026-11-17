/**
 * 【LGR-015】洛谷11月月赛·Day1
 *
 * => P2633 Count on a tree ( @c 省选/NOI- )
 *
 * -> https://www.luogu.com.cn/problem/P2633
 *
 * Submissions ~> https://www.luogu.com.cn/record/282871115 By huanhuanonly
 *
 * @b Dfs on @a Trees
 * @b LCA ( @a binary-lifting )
 * @b Tree-prefix-sum
 * @b Persistent-segment-tree
 *
 * ----June 24, 2026 [22h:55m:04s]----
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

#if defined(__SIZEOF_INT128__)
using int128 = __int128;
using uint128 = unsigned __int128;
#endif

using real32 = float;
using real64 = double;

#if defined(__SIZEOF_FLOAT80__)
using real80 = __float80;
#endif

#if defined(__SIZEOF_FLOAT128__)
using real128 = __float128;
#endif

class PersistentSegmentTree
{
public:

    struct node
    {
        int ls, rs;
        int cnt;
    };

    static inline std::vector<node> tree = std::vector<node>(5e6);

    int root = 0;

    static int create_node()
    {
        static int pos = 0;
        return ++pos;
    }

    static int copy_node(int u)
    {
        const int i = create_node();
        tree[i] = tree[u];
        return i;
    }

    static void push_up(int u)
    {
        tree[u].cnt = tree[tree[u].ls].cnt + tree[tree[u].rs].cnt;
    }

    static void add(int& u, int l, int r, int i)
    {
        u = copy_node(u);

        if (l == r)
        {
            ++tree[u].cnt;
            return;
        }

        const int mid = l + (r - l) / 2;

        if (i <= mid)
        {
            add(tree[u].ls, l, mid, i);
        }
        else
        {
            add(tree[u].rs, mid + 1, r, i);
        }

        push_up(u);
    }

    static int reduce(int u, int v, int lca, int parent_lca, int l, int r, int k)
    {
        if (l == r)
        {
            return l;
        }

        const int mid = l + (r - l) / 2;

        if (const int lcnt = tree[tree[u].ls].cnt + tree[tree[v].ls].cnt - tree[tree[lca].ls].cnt - tree[tree[parent_lca].ls].cnt; k <= lcnt)
        {
            return reduce(tree[u].ls, tree[v].ls, tree[lca].ls, tree[parent_lca].ls, l, mid, k);
        }
        else
        {
            return reduce(tree[u].rs, tree[v].rs, tree[lca].rs, tree[parent_lca].rs, mid + 1, r, k - lcnt);
        }
    }
};

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int n, m;
    std::cin >> n >> m;

    std::vector<int> w(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> w[i];
    }

    std::vector<std::vector<int>> e(n + 1);

    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        std::cin >> u >> v;

        e[u].push_back(v);
        e[v].push_back(u);
    }

    constexpr int maxw = std::numeric_limits<int>::max();
    constexpr int laycnt = 18;

    std::vector<std::array<int, laycnt>> parent(n + 1);
    std::vector<int> depth(n + 1);
    std::vector<PersistentSegmentTree> psegs(n + 1);

    auto lca = [&](int u, int v) -> int
    {
        if (depth[u] < depth[v])
        {
            std::swap(u, v);
        }

        for (int i = laycnt, diff = depth[u] - depth[v]; i--; )
        {
            if (diff & 1 << i)
            {
                u = parent[u][i];
            }
        }

        if (u == v)
        {
            return u;
        }

        for (int i = laycnt; i--; )
        {
            if (parent[u][i] != parent[v][i])
            {
                u = parent[u][i];
                v = parent[v][i];
            }
        }

        return parent[u][0];
    };

    auto build = [&](const auto& self, int u) -> void
    {
        for (int i = 1; i < laycnt; ++i)
        {
            parent[u][i] = parent[parent[u][i - 1]][i - 1];
        }

        depth[u] = depth[parent[u][0]] + 1;

        psegs[u].root = psegs[parent[u][0]].root;
        PersistentSegmentTree::add(psegs[u].root, 1, maxw, w[u]);

        for (int v : e[u])
        {
            if (v != parent[u][0])
            {
                parent[v][0] = u;
                self(self, v);
            }
        }
    };

    build(build, 1);

    for (int lastans = 0; m--; )
    {
        int u, v, k;
        std::cin >> u >> v >> k;

        u ^= lastans;

        const int top = lca(u, v);

        lastans = PersistentSegmentTree::reduce(
            psegs[u].root,
            psegs[v].root,
            psegs[top].root,
            psegs[parent[top][0]].root,
            1, maxw,
            k);

        std::cout << lastans << '\n';
    }

    return 0;
}