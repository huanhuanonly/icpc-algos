/**
 * 2026 省选赛前模板赛
 *
 * => P4556 【模板】线段树合并 / [Vani 有约会] 雨天的尾巴 ( @c 省选/NOI- )
 *
 * -> https://www.luogu.com.cn/problem/P4556
 *
 * Submissions ~> https://www.luogu.com.cn/record/282814864 By huanhuanonly
 *
 * @b Segment-tree-merging
 * @b Tree-difference
 * @b Dfs on @a Trees
 * @b LCA ( @a binary-lifting )
 *
 * ----June 24, 2026 [14h:59m:10s]----
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

class SegmentTree
{
public:

    struct node
    {
        int ls, rs;
        std::pair<int, int> value;
    };

    static inline std::vector<node> tree = std::vector<node>(1e7);

    int root = 0;

    static int create_node()
    {
        static int pos = 0;
        return ++pos;
    }

    static void push_up(int u)
    {
        tree[u].value = std::max(tree[tree[u].ls].value, tree[tree[u].rs].value);
    }

    static void add(int& u, int l, int r, int i, int value)
    {
        if (not u)
        {
            u = create_node();
        }

        if (l == r)
        {
            tree[u].value.first += value;
            tree[u].value.second = -i;
            return;
        }

        const int mid = l + r >> 1;

        if (i <= mid)
        {
            add(tree[u].ls, l, mid, i, value);
        }
        else
        {
            add(tree[u].rs, mid + 1, r, i, value);
        }

        push_up(u);
    }

    int reduce()
    {
        if (tree[root].value.first)
        {
            return -tree[root].value.second;
        }
        else
        {
            return 0;
        }
    }

    static void merge(int& u, int v, int l, int r)
    {
        if (not u or not v)
        {
            u |= v;
            return;
        }

        if (l == r)
        {
            tree[u].value.first += tree[v].value.first;
            return;
        }

        const int mid = l + r >> 1;

        merge(tree[u].ls, tree[v].ls, l, mid);
        merge(tree[u].rs, tree[v].rs, mid + 1, r);

        push_up(u);
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

    std::vector<std::vector<int>> e(n + 1);

    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        std::cin >> u >> v;

        e[u].push_back(v);
        e[v].push_back(u);
    }

    std::vector<int> depth(n + 1);

    constexpr int laycnt = 18;
    std::vector<std::array<int, laycnt>> parent(n + 1);

    auto build = [&](const auto& self, int u) -> void
    {
        for (int v : e[u])
        {
            if (v != parent[u][0])
            {
                depth[v] = depth[u] + 1;
                parent[v][0] = u;

                self(self, v);
            }
        }
    };

    build(build, 1);

    for (int i = 1; i < laycnt; ++i)
    {
        for (int u = 1; u <= n; ++u)
        {
            parent[u][i] = parent[parent[u][i - 1]][i - 1];
        }
    }

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

    constexpr int maxc = 1e5;
    std::vector<SegmentTree> segs(n + 1);

    for (int i = 0; i < m; ++i)
    {
        int u, v, c;
        std::cin >> u >> v >> c;

        const int t = lca(u, v);

        SegmentTree::add(segs[u].root, 1, maxc, c, 1);
        SegmentTree::add(segs[v].root, 1, maxc, c, 1);
        SegmentTree::add(segs[t].root, 1, maxc, c, -1);
        SegmentTree::add(segs[parent[t][0]].root, 1, maxc, c, -1);
    }

    std::vector<int> ans(n + 1);

    auto dfs = [&](const auto& self, int u) -> void
    {
        for (int v : e[u])
        {
            if (v != parent[u][0])
            {
                self(self, v);
                SegmentTree::merge(segs[u].root, segs[v].root, 1, maxc);
            }
        }

        ans[u] = segs[u].reduce();
    };

    dfs(dfs, 1);

    for (int i = 1; i <= n; ++i)
    {
        std::cout << ans[i] << '\n';
    }

    return 0;
}