/**
 * => Can you answer these queries III
 * 
 * -> https://ac.nowcoder.com/acm/problem/51109
 * 
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=63974418 By huanhuanonly
 * 
 * @b Segment-tree to find the maximum sub-segment sum of interval
 * 
 * ----September 22, 2023 [21h:09m:07s]----
*/

#include <bits/stdc++.h>

using llong = long long;
using ullong = unsigned long long;

class SegmentTree
{
public:
    struct node
    {
        int sum, l, r, max;
    };

    std::vector<int> arr;
    std::vector<node> tree;

    SegmentTree(std::vector<int>&& v) : arr(v), tree(arr.size() << 2) { }

    static constexpr inline ullong ls(ullong p) { return p << 1; }
    static constexpr inline ullong rs(ullong p) { return p << 1 | 1; }

    node& push_up(node& res, const node& l, const node& r)
    {
        res.sum = l.sum + r.sum;
        res.max = std::max({ l.max, r.max, l.r + r.l });
        res.l   = std::max(l.l, l.sum + r.l);
        res.r   = std::max(r.r, r.sum + l.r);
        
        return res;
    }

    void push_up(int p) { push_up(tree[p], tree[ls(p)], tree[rs(p)]); }

    void build(int p, int l, int r)
    {
        if (l == r)
        {
            tree[p] = { arr[l], arr[l], arr[l], arr[l] };
            return;
        }
        int mid = l + r >> 1;
        build(ls(p), l, mid), build(rs(p), mid + 1, r);
        push_up(p);
    }

    void update(int p, int l, int r, int x, int v)
    {
        if (l == x and r == x)
        {
            tree[p] = { v, v, v, v };
            return;
        }

        int mid = l + r >> 1;
        if (x <= mid)
            update(ls(p), l, mid, x, v);
        else
            update(rs(p), mid + 1, r, x, v);

        push_up(p);
    }

    node query(int p, int l, int r, int x, int y)
    {
        if (x <= l and r <= y)
        {
            return tree[p];
        }

        int mid = l + r >> 1;

        // When completely included in the sub-interval
        if (y <= mid)
            return query(ls(p), l, mid, x, y);
        else if (x > mid)
            return query(rs(p), mid + 1, r, x, y);

        // Otherwise you will need to try merging them
        else
        {
            node res;
            return push_up(res, query(ls(p), l, mid, x, y), query(rs(p), mid + 1, r, x, y));
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

    int n, m;
    std::cin >> n >> m;

    std::vector<int> v(n + 1);
    for (int i = 1; i <= n; ++i) std::cin >> v[i];

    SegmentTree seg(std::move(v));
    seg.build(1, 1, n);
    
    int op, x, y;
    while (m--)
    {
        std::cin >> op >> x >> y;
        if (op == 1)
        {
            std::cout << seg.query(1, 1, n, std::min(x, y), std::max(x, y)).max << '\n';
        }
        else
        {
            seg.update(1, 1, n, x, y);
        }
    }

    return 0;
}