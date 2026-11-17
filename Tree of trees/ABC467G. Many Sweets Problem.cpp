/**
 * AtCoder Beginner Contest 467
 *
 * => G - Many Sweets Problem ( @c 625 )
 *
 * -> https://atcoder.jp/contests/abc467/tasks/abc467_g
 *
 * Submissions ~> https://atcoder.jp/contests/abc467/submissions/77727856 By huanhuanonly
 *
 * @b Binary-indexed-tree-of-Segment-trees
 *
 * ----July 22, 2026 [01h:11m:33s]----
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
        uint64 cnt, sum;
    };

    static inline auto tree = std::vector<node>(1);
    int root = 0;

    static int create_node()
    {
        tree.emplace_back();
        return tree.size() - 1;
    }

    static void push_up(int u)
    {
        tree[u].cnt = tree[tree[u].ls].cnt + tree[tree[u].rs].cnt;
        tree[u].sum = tree[tree[u].ls].sum + tree[tree[u].rs].sum;
    }

    static void update(int& u, int l, int r, int i, const std::pair<uint64, uint64>& cntsum)
    {
        if (not u)
        {
            u = create_node();
        }

        if (l == r)
        {
            tree[u].cnt = cntsum.first;
            tree[u].sum = cntsum.second;
            return;
        }

        const int mid = l + r >> 1;

        if (i <= mid)
        {
            update(tree[u].ls, l, mid, i, cntsum);
        }
        else
        {
            update(tree[u].rs, mid + 1, r, i, cntsum);
        }

        push_up(u);
    }
};

class BinaryIndexedTree
{
public:

    std::vector<SegmentTree> tree;
    int maxv;

    explicit BinaryIndexedTree(int n, int maxv)
        : tree(n), maxv(maxv)
    { }

    static int lowbit(int x)
    {
        return x & -x;
    }

    void update(int pos, int i, const std::pair<uint64, uint64>& cntsum)
    {
        for (; pos < tree.size(); pos += lowbit(pos))
        {
            SegmentTree::update(tree[pos].root, 1, maxv, i, cntsum);
        }
    }

    uint64 count(int l, int r, uint64 k)
    {
        std::vector<int> setl, setr;

        for (; r; setr.push_back(tree[r].root), r -= lowbit(r));
        for (--l; l; setl.push_back(tree[l].root), l -= lowbit(l));

        bool found = false;

        auto dfs = [&](const auto& self, int l, int r, uint64 k) -> uint64
        {
            if (l == r)
            {
                uint64 sum = 0;

                for (const int& u : setr)
                {
                    sum += SegmentTree::tree[u].sum;
                }

                for (const int& u : setl)
                {
                    sum -= SegmentTree::tree[u].sum;
                }

                if (sum >= k)
                {
                    uint64 cnt = 0;

                    for (const int& u : setr)
                    {
                        cnt += SegmentTree::tree[u].cnt;
                    }

                    for (const int& u : setl)
                    {
                        cnt -= SegmentTree::tree[u].cnt;
                    }

                    found = true;
                    return cnt;
                }
                else
                {
                    return 0;
                }
            }

            uint64 sumls = 0;

            for (const int& u : setr)
            {
                sumls += SegmentTree::tree[SegmentTree::tree[u].ls].sum;
            }

            for (const int& u : setl)
            {
                sumls -= SegmentTree::tree[SegmentTree::tree[u].ls].sum;
            }

            const int mid = l + r >> 1;

            if (sumls >= k)
            {
                for (int& u : setr)
                {
                    u = SegmentTree::tree[u].ls;
                }

                for (int& u : setl)
                {
                    u = SegmentTree::tree[u].ls;
                }

                return self(self, l, mid, k);
            }
            else
            {
                uint64 cnt = 0;

                for (const int& u : setr)
                {
                    cnt += SegmentTree::tree[SegmentTree::tree[u].ls].cnt;
                }

                for (const int& u : setl)
                {
                    cnt -= SegmentTree::tree[SegmentTree::tree[u].ls].cnt;
                }

                for (int& u : setr)
                {
                    u = SegmentTree::tree[u].rs;
                }

                for (int& u : setl)
                {
                    u = SegmentTree::tree[u].rs;
                }

                return cnt + self(self, mid + 1, r, k - sumls);
            }
        };

        if (const auto cnt = dfs(dfs, 1, maxv, k); found)
        {
            return cnt;
        }
        else
        {
            return ~uint64{};
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

    int n, q;
    std::cin >> n >> q;

    std::vector<uint64> v(n + 1, std::numeric_limits<uint64>::max());

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> v[i];
    }

    SegmentTree::tree.reserve(2e7);

    std::vector<std::tuple<int, int, int, int, uint64>> queries(q);

    for (auto& [c, x, l, r, k] : queries)
    {
        std::cin >> c >> x >> l >> r >> k;
    }

    auto set = v;
    set.append_range(queries | std::views::elements<1>);

    std::ranges::sort(set | std::views::drop(1), std::ranges::greater{});

    auto $ = [&, cnt = std::map<uint64, int>()](uint64 x) mutable -> int
    {
        return std::ranges::lower_bound(set, x, std::ranges::greater{}) - set.begin() + cnt[x]++;
    };

    std::vector<int> ids(n + 1);

    BinaryIndexedTree tree(n + 1, set.size());

    for (int i = 1; i <= n; ++i)
    {
        tree.update(i, ids[i] = $(v[i]), {1, v[i]});
    }

    for (const auto& [c, x, l, r, k] : queries)
    {
        tree.update(c, ids[c], {0, 0});
        v[c] = x;
        tree.update(c, ids[c] = $(v[c]), {1, v[c]});

        if (const auto cnt = tree.count(l, r, k); ~cnt)
        {
            std::cout << cnt << '\n';
        }
        else
        {
            std::cout << "-1\n";
        }
    }

    return 0;
}