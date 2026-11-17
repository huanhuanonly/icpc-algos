/**
 * 第十二届中国大学生程序设计竞赛 长春站（CCPC 2026 Changchun Site）
 *
 * => K. 纸带染色
 *
 * -> https://qoj.ac/contest/4582/problem/22920
 *
 * Submissions ~> https://qoj.ac/submission/3400214 By huanhuanonly
 *
 * @b Merge-sort-tree
 *
 * ----November 07, 2026 [19h:23m:13s]----
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

struct MergeSortTree
{
    std::vector<std::vector<int>> tree;

    explicit MergeSortTree(int n)
        : tree(n << 2)
    { }

    static int ls(int u)
    { return u << 1; }

    static int rs(int u)
    { return u << 1 | 1; }

    void build(int u, int l, int r, const std::vector<int>& a)
    {
        if (l == r)
        {
            tree[u].push_back(a[l]);
            return;
        }

        const int mid = l + r >> 1;

        build(ls(u), l, mid, a);
        build(rs(u), mid + 1, r, a);

        tree[u].resize(r - l + 1);
        std::ranges::merge(tree[ls(u)], tree[rs(u)], tree[u].begin(), std::ranges::greater{});
    }

    int count_gt(int u, int l, int r, int x, int y, int v)
    {
        if (x <= l and r <= y)
        {
            return std::ranges::lower_bound(tree[u], v, std::ranges::greater{}) - tree[u].begin();
        }

        const int mid = l + r >> 1;
        int total = 0;

        if (x <= mid)
        {
            total = count_gt(ls(u), l, mid, x, y, v);
        }

        if (y > mid)
        {
            total += count_gt(rs(u), mid + 1, r, x, y, v);
        }

        return total;
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

    int n, m, q;
    std::cin >> n >> m >> q;

    std::vector<std::pair<bool, int>> ops(m + 1);

    for (auto& [o, x] : ops | std::views::drop(1))
    {
        std::cin >> o >> x;
    }

    std::vector<int> end(m + 1, m + 1);

    std::deque<int> stl, str;

    std::multiset<int> setr;
    std::multiset<int, std::ranges::greater> setl;

    for (int i = 1; i <= m; ++i)
    {
        if (ops[i].first)
        {
            while (not str.empty() and ops[i].second <= ops[str.back()].second)
            {
                setr.extract(ops[str.back()].second);

                end[str.back()] = i;
                str.pop_back();
            }

            str.push_back(i);
            setr.insert(ops[i].second);

            if (ops[i].second == 1)
            {
                for (; not stl.empty(); end[stl.back()] = i, stl.pop_back());
                setl.clear();
            }
            else if (not setl.empty() and *setl.begin() + 1 >= ops[i].second) while (true)
            {
                auto nd = setl.extract(ops[stl.front()].second);

                if (not setl.empty() and *setl.begin() + 1 >= ops[i].second)
                {
                    end[stl.front()] = i;
                    stl.pop_front();
                }
                else
                {
                    setl.insert(std::move(nd));

                    while (not str.empty() and str.front() < stl.front())
                    {
                        setr.extract(ops[str.front()].second);

                        end[str.front()] = i;
                        str.pop_front();
                    }

                    break;
                }
            }
        }
        else
        {
            while (not stl.empty() and ops[i].second >= ops[stl.back()].second)
            {
                setl.extract(ops[stl.back()].second);
                end[stl.back()] = i;
                stl.pop_back();
            }

            stl.push_back(i);
            setl.insert(ops[i].second);

            if (ops[i].second == n)
            {
                for (; not str.empty(); end[str.back()] = i, str.pop_back());
                setr.clear();
            }
            else if (not setr.empty() and *setr.begin() <= ops[i].second + 1) while (true)
            {
                auto nd = setr.extract(ops[str.front()].second);

                if (not setr.empty() and *setr.begin() <= ops[i].second + 1)
                {
                    end[str.front()] = i;
                    str.pop_front();
                }
                else
                {
                    setr.insert(std::move(nd));

                    while (not stl.empty() and stl.front() < str.front())
                    {
                        setl.extract(ops[stl.front()].second);
                        end[stl.front()] = i;
                        stl.pop_front();
                    }

                    break;
                }
            }
        }
    }

    MergeSortTree mst(m);
    mst.build(1, 1, m, end);

    while (q--)
    {
        int l, r;
        std::cin >> l >> r;

        std::cout << mst.count_gt(1, 1, m, l, r, r) << '\n';
    }

    return 0;
}