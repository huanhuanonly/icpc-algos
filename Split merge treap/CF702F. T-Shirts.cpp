/**
 * Educational Codeforces Round 15
 *
 * => F. T-Shirts ( @c 2800 )
 *
 * -> https://codeforces.com/contest/702/problem/F
 *
 * Submissions ~> https://codeforces.com/contest/702/submission/259762270 By huanhuanonly
 *
 * @b Split-merge-treap
 *
 * @from: https://www.luogu.com.cn/training/147262#problems
 *
 * ----May 06, 2024 [22h:08m:15s]----
*/

#include <bits/stdc++.h>

using uint    = unsigned int;
using llong   = long long int;
using ullong  = unsigned long long int;
using ldouble = long double;

class Treap
{
public:

    struct node
    {
        int ls, rs;
        int key, value;

        int lazy, lazy2;

        int id, cnt;
    };

    std::vector<node> tree;
    int root = 0;

    Treap() : tree(1) { }

    int push_node(int value, int id)
    {
        static std::mt19937 rng;

        tree.push_back(node{0, 0, int(rng()), value, 0, 0, id, 0});
        return tree.size() - 1;
    }

    void push_down(int u)
    {
        if (tree[u].lazy)
        {
            tree[u].value -= tree[u].lazy;
            tree[u].cnt += tree[u].lazy2;

            tree[tree[u].ls].lazy += tree[u].lazy;
            tree[tree[u].rs].lazy += tree[u].lazy;

            tree[tree[u].ls].lazy2 += tree[u].lazy2;
            tree[tree[u].rs].lazy2 += tree[u].lazy2;

            tree[u].lazy = 0;
            tree[u].lazy2 = 0;
        }
    }

    void split(int u, int value, int& rx, int& ry)
    {
        if (u == 0)
        {
            rx = ry = 0;
            return;
        }

        push_down(u);

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
    }

    int merge(int u, int v)
    {
        if (u == 0 or v == 0)
            return u + v;

        if (tree[u].key > tree[v].key)
        {
            push_down(u);
            tree[u].rs = merge(tree[u].rs, v);
            return u;
        }
        else
        {
            push_down(v);
            tree[v].ls = merge(u, tree[v].ls);
            return v;
        }
    }

    void insert(int value, int id)
    {
        int x, y;
        split(root, value, x, y);

        root = merge(x, merge(push_node(value, id), y));
    }

    void postorder(int u, auto func)
    {
        if (u == 0)
            return;

        push_down(u);

        postorder(tree[u].ls, func);
        postorder(tree[u].rs, func);

        func(u);
    }

    void update(int value)
    {
        int x, y, z;
        split(root, value - 1, x, y);
        split(y, value * 2, y, z);

        tree[y].lazy += value;
        tree[y].lazy2 += 1;

        postorder(y, [&](int u) -> void
        {
            int l, r;
            split(x, tree[u].value, l, r);

            tree[u].ls = tree[u].rs = 0;
            x = merge(l, merge(u, r));
        });

        tree[z].lazy += value;
        tree[z].lazy2 += 1;

        root = merge(x, z);
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

    int n;
    std::cin >> n;

    std::vector<std::pair<int, int>> v(n);

    for (auto& [i, j] : v)
        std::cin >> i >> j;

    std::sort(v.begin(), v.end(), [](const auto& lv, const auto& rv) -> bool
    {
        if (lv.second != rv.second)
            return lv.second > rv.second;
        else
            return lv.first < rv.first;
    });

    Treap tree;

    int k;
    std::cin >> k;

    for (int i = 0, x; i < k; ++i)
    {
        std::cin >> x;

        tree.insert(x, i);
    }

    for (int i = 0; i < n; ++i)
    {
        tree.update(v[i].first);
    }

    std::vector<int> ans(k);

    tree.postorder(tree.root, [&](int u) -> void
    {
        ans[tree.tree[u].id] = tree.tree[u].cnt;
    });

    for (const auto& i : ans)
        std::cout << i << ' ';

    return 0;
}

/**
 * @file check.py
 *
 * import sys
 * sys.stdin  = open('Input.txt', 'r')
 *
 * n = int(input())
 *
 * data = []
 *
 * for i in range(n):
 *     data.append(list(map(int, input().split())))
 *
 * import functools
 *
 * def cmp(lv, rv):
 *     if lv[1] != rv[1]:
 *         return 1 if lv[1] > rv[1] else -1
 *     elif lv[0] != rv[0]:
 *         return 1 if lv[0] < rv[0] else -1
 *     else:
 *         return 0
 *
 * data.sort(key = functools.cmp_to_key(cmp), reverse = True)
 *
 * k = int(input())
 * b = list(map(int, input().split()))
 *
 * ans = []
 *
 * for i in b:
 *     cnt = 0
 *     ct = i
 *     for d in data:
 *         if ct >= d[0]:
 *             ct -= d[0]
 *             cnt += 1
 *     ans.append(cnt)
 *
 * sys.stdin.close()
 * sys.stdin = open('Output.txt', 'r')
 *
 * out = list(map(int, input().split()))
 *
 * sys.stdin.close()
 * sys.stdout = open('Output.txt', 'a')
 *
 * if ans == out:
 *     print('\n--AC--')
 * else:
 *     print("\n--WA--")
 *     print(*ans)
*/