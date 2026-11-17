/**
 * AtCoder Beginner Contest 356
 *
 * => F - Distance Component Size Query ( @c 525 )
 *
 * -> https://atcoder.jp/contests/abc356/tasks/abc356_f
 *
 * Submissions ~> https://atcoder.jp/contests/abc356/submissions/54663995 By huanhuanonly
 *
 * @b Split-merge-treap ( @a dynamic-connectivity )
 *
 * ----June 17, 2024 [16h:13m:42s]----
*/

#include <bits/stdc++.h>

using uint    = unsigned int;
using llong   = long long int;
using ullong  = unsigned long long int;
using ldouble = long double;

class MultiTreap
{
public:
    struct node
    {
        int ls, rs;
        llong key, value;
        int size, fa;
    };

private:
    std::vector<node> tree;

    // [value] = (index in tree)
    std::map<llong, int> log;

public:
    MultiTreap() : tree(1) { tree.reserve(2e5 + 1); }

    int apply_node(llong value)
    {
        static std::mt19937 rng;

        int id;

        if (auto it = log.find(value); it != log.end())
        {
            id = it->second;
            tree[id].fa = tree[id].ls = tree[id].rs = 0;
        }
        else
        {
            tree.push_back({});
            id = tree.size() - 1;
            tree[id].key = rng();
            tree[id].value = value;
            log[value] = id;
        }

        tree[id].size = 1;

        return id;
    }

    void push_up(int u)
    {
        tree[u].size = tree[tree[u].ls].size + tree[tree[u].rs].size + 1;

        tree[u].fa = 0;

        if (tree[u].ls)
            tree[tree[u].ls].fa = u;

        if (tree[u].rs)
            tree[tree[u].rs].fa = u;
    }

    void split(int u, llong value, int& rx, int& ry)
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
            return push_up(u + v), u + v;

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

    // Return index of root of value in the tree
    int find_root(llong value)
    {
        int u = log[value];

        while (tree[u].fa)
            u = tree[u].fa;

        return u;
    }

    // __nd is an index in the tree
    void insert(int& rt, int nd)
    {
        int x, y;
        split(rt, tree[nd].value, x, y);
        rt = merge(x, merge(nd, y));
    }

    // Split a set into three sets: {<value}, {=value}, {>value}
    void split_three_set(llong value)
    {
        int rt = find_root(value);

        int x, y, z;
        split(rt, value - 1, x, y);
        split(y, value, y, z);
    }

    // The maximum value of the __fst set is less than or equal to the minimum value of the __sst set
    void merge_two_set(llong fst, llong sst)
    {
        merge(find_root(fst), find_root(sst));
    }

    // Insert a value into the set
    void insert_to_set(llong set, llong value)
    {
        int rt = find_root(set);
        insert(rt, log[value]);
    }

    bool in_same_set(llong lv, llong rv)
    {
        return find_root(lv) == find_root(rv);
    }

    int size(llong value)
    {
        return tree[find_root(value)].size;
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

    llong q, k;
    std::cin >> q >> k;

    MultiTreap tree;
    std::set<llong> st;

    llong opt, x;

    while (q--)
    {
        std::cin >> opt >> x;

        if (opt == 1)
        {
            auto it = st.find(x);

            if (it != st.end())
            {
                tree.split_three_set(x);

                if (it != st.begin())
                {
                    auto pit = std::prev(it);
                    auto nit = std::next(it);

                    if (nit != st.end() and std::abs(*nit - *pit) <= k)
                    {
                        tree.merge_two_set(*pit, *nit);
                    }
                }

                st.erase(x);
            }
            else
            {
                it = st.insert(x).first;
                tree.apply_node(x);

                bool merged = false;

                if (auto nit = std::next(it); nit != st.end())
                {
                    if (std::abs(*nit - x) <= k)
                    {
                        tree.insert_to_set(*nit, x);
                        merged = true;
                    }
                }

                if (it != st.begin())
                {
                    auto pit = std::prev(it);

                    if (std::abs(*pit - x) <= k and tree.in_same_set(*pit, x) == false)
                    {
                        if (merged)
                            tree.merge_two_set(*pit, x);
                        else
                            tree.insert_to_set(*pit, x);
                    }
                }
            }
        }
        else // if opt == 2
        {
            std::cout << tree.size(x) << '\n';
        }
    }

    return 0;
}