/**
 * Codeforces Round 817 (Div. 4)
 *
 * => E. Counting Rectangles ( @c 1600 )
 *
 * -> https://codeforces.com/contest/1722/problem/E
 *
 * Submissions ~> https://codeforces.com/contest/1722/submission/242104637 By huanhuanonly
 *
 * @b Segment-tree-of-Segment-trees
 *
 * ----January 18, 2024 [00h:28m:39s]----
*/

#include <bits/stdc++.h>

using llong = long long;
using ullong = unsigned long long;

class SubSegmentTree
{
public:
    struct node
    {
        int ls, rs;
        ullong value;
    };

    std::vector<node> tree;

    explicit SubSegmentTree() : tree(2) { }

    int push_node()
    {
        tree.emplace_back(node());
        return tree.size() - 1;
    }

    int ls(int p)
    {
        if (tree[p].ls)
            return tree[p].ls;
        else
            return tree[p].ls = push_node();
    }
    int rs(int p)
    {
        if (tree[p].rs)
            return tree[p].rs;
        else
            return tree[p].rs = push_node();
    }

    void push_up(int p)
    {
        tree[p].value = tree[tree[p].ls].value + tree[tree[p].rs].value;
    }

    void insert(int p, int l, int r, int pos, ullong value)
    {
        if (l == r)
        {
            tree[p].value += value;
            return;
        }

        int mid = l + r >> 1;
        if (pos <= mid)
            insert(ls(p), l, mid, pos, value);
        if (pos > mid)
            insert(rs(p), mid + 1, r, pos, value);

        push_up(p);
    }

    ullong query(int p, int l, int r, int x, int y)
    {
        if (x <= l and r <= y) return tree[p].value;

        int mid = l + r >> 1;
        ullong sum = 0;

        if (x <= mid)
            sum += query(ls(p), l, mid, x, y);
        if (y > mid)
            sum += query(rs(p), mid + 1, r, x, y);
        return sum;
    }
};

class SegmentTree
{
public:

    std::vector<SubSegmentTree> tree;

    std::size_t n;

    explicit SegmentTree(std::size_t __n) : tree(__n << 2), n(__n) { }

    static constexpr inline int ls(int p) { return p << 1; }
    static constexpr inline int rs(int p) { return p << 1 | 1; }

    void insert(int p, int l, int r, const std::pair<int, int>& value)
    {
        tree[p].insert(1, 1, n, value.second, value.first * value.second);

        if (l == r) return;

        int mid = l + r >> 1;
        if (value.first <= mid)
            insert(ls(p), l, mid, value);
        if (value.first > mid)
            insert(rs(p), mid + 1, r, value);
    }

    ullong query(int p, int l, int r, int x, int y, int x2, int y2)
    {
        if (x <= l and r <= y)
            return tree[p].query(1, 1, n, x2, y2);

        int mid = l + r >> 1;
        ullong sum = 0;

        if (x <= mid)
            sum += query(ls(p), l, mid, x, y, x2, y2);
        if (y > mid)
            sum += query(rs(p), mid + 1, r, x, y, x2, y2);
        return sum;
    }
};

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int _;
    std::cin >> _;

    while (_--)
    {
        int n, q;
        std::cin >> n >> q;

        SegmentTree tree(1001);
        int x, y;
        for (int i = 0; i < n; ++i)
        {
            std::cin >> x >> y;
            tree.insert(1, 1, 1001, { x, y });
        }

        int x2, y2;
        for (int i = 0; i < q; ++i)
        {
            std::cin >> x >> y >> x2 >> y2;

            std::cout << tree.query(1, 1, 1001, x + 1, x2 - 1, y + 1, y2 - 1) << '\n';
        }
    }

    return 0;
}