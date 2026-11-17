/**
 * 哈尔滨华德学院第十七届程序设计竞赛（同步赛）
 *
 * => K-排行榜查询（hard）
 *
 * -> https://ac.nowcoder.com/acm/contest/132781/K
 *
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=83580308 By huanhuanonly
 *
 * @b Split-merge-treap
 *
 * ----May 13, 2026 [01h:02m:20s]----
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

class Treap
{
public:

    struct node
    {
        int64 ls, rs;
        int64 size;

        int64 key, value;
    };

    std::vector<node> tree;
    int64 root = 0;

    Treap() : tree(1)
    { }

    int64 new_node(int64 value)
    {
        static std::mt19937 rng;
        tree.emplace_back(0, 0, 1, int64(rng()), value);
        return tree.size() - 1;
    }

    void push_up(int64 u)
    {
        tree[u].size = tree[tree[u].ls].size + tree[tree[u].rs].size + 1;
    }

    template<typename _Comp>
    void split_by_value(int64 u, int64 value, int64& rx, int64& ry, _Comp comp)
    {
        if (u == 0)
        {
            rx = ry = 0;
            return;
        }

        if (comp(tree[u].value, value))
        {
            rx = u;
            split_by_value(tree[u].rs, value, tree[u].rs, ry, comp);
        }
        else
        {
            ry = u;
            split_by_value(tree[u].ls, value, rx, tree[u].ls, comp);
        }

        push_up(u);
    }

    void split_by_size(int64 u, int64 size, int64& rx, int64& ry)
    {
        if (u == 0)
        {
            rx = ry = 0;
            return;
        }

        if (size <= tree[tree[u].ls].size)
        {
            ry = u;
            split_by_size(tree[u].ls, size, rx, tree[u].ls);
        }
        else
        {
            rx = u;
            split_by_size(tree[u].rs, size - tree[tree[u].ls].size - 1, tree[u].rs, ry);
        }

        push_up(u);
    }

    int64 merge(int64 u, int64 v)
    {
        if (u == 0 or v == 0)
        {
            return u | v;
        }

        if (tree[u].key < tree[v].key)
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

    template<typename _Comp>
    void insert(int64 value, _Comp comp)
    {
        int64 x, y;
        split_by_value(root, value, x, y, std::move(comp));

        root = merge(merge(x, new_node(value)), y);
    }

    template<typename _Comp>
    int64 extract(int64 value, _Comp comp)
    {
        int64 x, y, z;
        split_by_value(root, value, x, y, std::move(comp));
        split_by_size(y, 1, y, z);

        root = merge(x, z);
        return y;
    }

    template<typename _Comp>
    void reinsert(int64 u, _Comp comp)
    {
        int64 x, y;
        split_by_value(root, tree[u].value, x, y, comp);

        root = merge(merge(x, u), y);
    }

    template<typename _Comp>
    int64 at(int64 k, _Comp comp)
    {
        int64 x, y, z;
        split_by_size(root, k - 1, x, y);
        split_by_size(y, 1, y, z);

        const int64 result = tree[y].value;

        root = merge(merge(x, y), z);
        return result;
    }

    template<typename _Comp>
    int64 rank_of(int64 value, _Comp comp)
    {
        int64 x, y;
        split_by_value(root, value, x, y, comp);

        const int64 result = tree[x].size + 1;

        root = merge(x, y);
        return result;
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

    struct item
    {
        int64 sid;

        struct prob
        {
            bool ac;
            int64 cnt;
        };

        std::map<int64, prob> probs;

        int64 cnt;
        int64 sum;
    };

    int64 n, m, q;
    std::cin >> n >> m >> q;

    std::map<int64, item> data;

    Treap treap;

    auto comp = [&](int64 lhs, int64 rhs) -> bool
    {
        auto& ld = data[lhs], rd = data[rhs];

        if (ld.cnt != rd.cnt)
        {
            return ld.cnt > rd.cnt;
        }
        else if (ld.sum != rd.sum)
        {
            return ld.sum < rd.sum;
        }
        else
        {
            return ld.sid < rd.sid;
        }
    };

    auto weak_comp = [&](int64 lhs, int64 rhs) -> bool
    {
        auto& ld = data[lhs], rd = data[rhs];

        if (ld.cnt != rd.cnt)
        {
            return ld.cnt > rd.cnt;
        }
        else
        {
            return ld.sum < rd.sum;
        }
    };

    while (q--)
    {
        int64 opt;
        std::cin >> opt;

        if (opt == 1)
        {
            int64 sid, pid;
            std::string result;
            int64 time;

            std::cin >> sid >> pid >> result >> time;

            if (const auto it = data.find(sid); it != data.end())
            {
                const auto u = treap.extract(sid, comp);
                item& item = it->second;

                if (auto& p = item.probs[pid]; not p.ac)
                {
                    if (result == "AC")
                    {
                        p.ac = true;

                        ++item.cnt;
                        item.sum += time + p.cnt * 20;
                    }
                    else if (result != "CE")
                    {
                        ++p.cnt;
                    }
                }

                treap.reinsert(u, comp);
            }
            else
            {
                item& item = data[sid];
                item.sid = sid;

                if (result == "AC")
                {
                    item.probs[pid] = {true, 0};
                    item.cnt = 1;
                    item.sum = time;
                }
                else if (result != "CE")
                {
                    item.probs[pid] = {false, 1};
                }

                treap.insert(sid, comp);
            }
        }
        else
        {
            int64 k;
            std::cin >> k;

            if (k > data.size())
            {
                std::cout << -1 << '\n';
            }
            else
            {
                const int64 sid = treap.at(k, comp);
                const int64 rank = treap.rank_of(sid, weak_comp);

                std::cout << rank << ' ' << sid << ' ' << data[sid].cnt << ' ' << data[sid].sum << '\n';
            }
        }
    }

    return 0;
}