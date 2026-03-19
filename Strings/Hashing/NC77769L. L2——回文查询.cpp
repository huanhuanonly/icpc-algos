/**
 * 2024 南昌理工天梯赛选拔赛
 * 
 * => L2——回文查询
 * 
 * -> https://ac.nowcoder.com/acm/contest/77769/L
 * 
 * @b Hashing on @b Segment-tree
 * 
 * @see also https://www.cnblogs.com/knife-rose/p/11230936.html
 *       and https://blog.csdn.net/weixin_43350051/article/details/100011560
*/

#include <bits/stdc++.h>

using uint    = unsigned int;
using llong   = long long int;
using ullong  = unsigned long long int;
using ldouble = long double;

class SegmentTree
{
public:
    
    static constexpr const int P = 131;

    std::vector<ullong> tree;

    std::vector<ullong> p;

    std::string& init;

    explicit SegmentTree(std::string& s)
        : tree(s.size() << 2), p(s.size() + 1), init(s)
    {
        p[0] = 1;

        for (int i = 1; i <= s.size(); ++i)
            p[i] = p[i - 1] * P;
    }

    static constexpr int ls(int u) { return u << 1; }
    static constexpr int rs(int u) { return u << 1 | 1; }

    void push_up(int u, int size)
    {
        tree[u] = tree[ls(u)] * p[size] + tree[rs(u)];
    }

    void build(int u, int l, int r)
    {
        if (l == r)
        {
            tree[u] = init[l - 1];
            return;
        }

        int mid = l + r >> 1;
        
        build(ls(u), l, mid);
        build(rs(u), mid + 1, r);

        // Size of right-node, like r - (l - 1)
        push_up(u, r - ((mid + 1) - 1));
    }

    void update(int u, int l, int r, int x, char c)
    {
        if (l == r)
        {
            tree[u] = c;
            return;
        }

        int mid = l + r >> 1;

        if (x <= mid)
            update(ls(u), l, mid, x, c);
        else
            update(rs(u), mid + 1, r, x, c);

        push_up(u, r - mid);
    }

    // value, length
    std::pair<ullong, int> query(int u, int l, int r, int x, int y)
    {
        if (x <= l and r <= y)
            return {tree[u], r - l + 1};

        int mid = l + r >> 1;

        if (x <= mid)
        {
            if (y > mid)
            {
                auto [lval, llen] = query(ls(u), l, mid, x, y);
                auto [rval, rlen] = query(rs(u), mid + 1, r, x, y);

                return {lval * p[rlen] + rval, llen + rlen};
            }
            else
            {
                return query(ls(u), l, mid, x, y);
            }
        }
        else
        {
            return query(rs(u), mid + 1, r, x, y);
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

    int n, q;
    std::cin >> n >> q;

    std::string s;
    std::cin >> s;

    SegmentTree tree(s);
    tree.build(1, 1, n);

    std::string rs = s;
    std::reverse(rs.begin(), rs.end());
    
    SegmentTree rtree(rs);
    rtree.build(1, 1, n);

    int opt;
    while (q--)
    {
        std::cin >> opt;

        if (opt == 1)
        {
            int x;
            char c;

            std::cin >> x >> c;

            tree.update(1, 1, n, x, c);
            rtree.update(1, 1, n, n - x + 1, c);
        }
        else
        {
            int l, r;
            std::cin >> l >> r;

            if (tree.query(1, 1, n, l, r).first == rtree.query(1, 1, n, n - r + 1, n - l + 1).first)
                std::cout << "Yes\n";
            else
                std::cout << "No\n";
        }
    }


    return 0;
}
