/**
 * 2026 省选赛前模板赛 / bzoj3196 / Tyvj1730
 *
 * => P3380 【模板】树套树 ( @c 省选/NOI- )
 *
 * -> https://www.luogu.com.cn/problem/P3380
 *
 * Submissions ~> https://www.luogu.com.cn/record/158476496 By huanhuanonly
 *
 * @b Segment-tree-of-Split-merge-treaps
 *
 * ----May 09, 2024 [15h:52m:09s]----
*/

#include <bits/stdc++.h>

using uint    = unsigned int;
using llong   = long long int;
using ullong  = unsigned long long int;
using ldouble = long double;

class TreapOnSegmentTree
{
public:

    struct node
    {
        int ls, rs;
        int key, value;
        int size;
    };

    std::vector<node> tree;
    std::vector<int>  root;

    int n;

    explicit TreapOnSegmentTree(const std::vector<int>& v)
        : tree(1), root(v.size() << 2), n(v.size() - 1) { build(1, 1, n, v); }

    static int ls(int u) { return u << 1; }
    static int rs(int u) { return u << 1 | 1; }

    void build(int u, int l, int r, const std::vector<int>& v)
    {
        for (int i = l; i <= r; ++i)
            insert(u, v[i]);

        if (l == r)
            return;

        int mid = l + r >> 1;

        build(ls(u), l, mid, v);
        build(rs(u), mid + 1, r, v);
    }

    int push_node(int value)
    {
        static std::mt19937 rng;

        tree.push_back(node{0, 0, int(rng()), value, 1});
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

    void insert(int rt, int value)
    {
        int x, y;
        split(root[rt], value, x, y);
        root[rt] = merge(x, merge(push_node(value), y));
    }

    int rank_of(int u, int l, int r, int x, int y, int value)
    {
        if (x <= l and r <= y)
        {
            int f, s;
            split(root[u], value - 1, f, s);
            int res = tree[f].size;
            root[u] = merge(f, s);
            return res;
        }

        int mid = l + r >> 1;
        int res = 0;

        if (x <= mid)
            res += rank_of(ls(u), l, mid, x, y, value);
        if (y > mid)
            res += rank_of(rs(u), mid + 1, r, x, y, value);

        return res;
    }

    int at(int k, int l, int r)
    {
        int ll = 0, rr = 1e8 + 1, mid;

        while (rr - ll > 1)
        {
            mid = ll + rr >> 1;

            if (rank_of(1, 1, n, l, r, mid) + 1 <= k)
                ll = mid;
            else
                rr = mid;
        }

        return ll;
    }

    int change(int u, int l, int r, int pos, int value)
    {
        if (l == r)
        {
            int last = tree[root[u]].value;
            tree[root[u]].value = value;
            return last;
        }

        int mid = l + r >> 1;
        int last;

        if (pos <= mid)
            last = change(ls(u), l, mid, pos, value);
        else
            last = change(rs(u), mid + 1, r, pos, value);

        int x, y, z;
        split(root[u], last - 1, x, y);
        split(y, last, y, z);

        root[u] = merge(x, merge(merge(tree[y].ls, tree[y].rs), z));

        tree[y].ls = tree[y].rs = 0;
        tree[y].value = value;
        tree[y].size = 1;

        split(root[u], value, x, z);
        root[u] = merge(x, merge(y, z));

        return last;
    }

    int prev(int u, int l, int r, int x, int y, int value)
    {
        if (x <= l and r <= y)
        {
            int f, s;
            split(root[u], value - 1, f, s);

            int cur = f;
            while (tree[cur].rs)
                cur = tree[cur].rs;

            root[u] = merge(f, s);

            if (cur)
                return tree[cur].value;
            else
                return -2147483647;
        }

        int mid = l + r >> 1;

        int mx = -2147483647;

        if (x <= mid)
            if (int res = prev(ls(u), l, mid, x, y, value); res != -2147483647)
                mx = std::max(mx, res);

        if (y > mid)
            if (int res = prev(rs(u), mid + 1, r, x, y, value); res != -2147483647)
                mx = std::max(mx, res);

        return mx;
    }

    int next(int u, int l, int r, int x, int y, int value)
    {
        if (x <= l and r <= y)
        {
            int f, s;
            split(root[u], value, f, s);

            int cur = s;
            while (tree[cur].ls)
                cur = tree[cur].ls;

            root[u] = merge(f, s);

            if (cur)
                return tree[cur].value;
            else
                return 2147483647;
        }

        int mid = l + r >> 1;

        int mn = 2147483647;

        if (x <= mid)
            if (int res = next(ls(u), l, mid, x, y, value); res != 2147483647)
                mn = std::min(mn, res);

        if (y > mid)
            if (int res = next(rs(u), mid + 1, r, x, y, value); res != 2147483647)
                mn = std::min(mn, res);

        return mn;
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

    std::vector<int> v(n + 1);

    for (int i = 1; i <= n; ++i)
        std::cin >> v[i];

    TreapOnSegmentTree tree(v);

    int opt, l, r, pos, k;

    while (m--)
    {
        std::cin >> opt;

        switch (opt)
        {
            case 1:
            {
                std::cin >> l >> r >> k;
                std::cout << tree.rank_of(1, 1, n, l, r, k) + 1 << '\n';
                break;
            }

            case 2:
            {
                std::cin >> l >> r >> k;
                std::cout << tree.at(k, l, r) << '\n';
                break;
            }

            case 3:
            {
                std::cin >> pos >> k;
                tree.change(1, 1, n, pos, k);
                break;
            }

            case 4:
            {
                std::cin >> l >> r >> k;
                std::cout << tree.prev(1, 1, n, l, r, k) << '\n';
                break;
            }

            case 5:
            {
                std::cin >> l >> r >> k;
                std::cout << tree.next(1, 1, n, l, r, k) << '\n';
                break;
            }
        }
    }

    return 0;
}