/**
 * 牛客周赛 Round 149
 *
 * => F-小红的树 ( @c 2100 )
 *
 * -> https://ac.nowcoder.com/acm/contest/136720/F
 *
 * Submissions ~> https://ac.nowcoder.com/acm/contest/view-submission?submissionId=83900034 By huanhuanonly
 *
 * @b Heavy-Light-decomposition
 * @b Tree-DP
 *
 * ----June 22, 2026 [10h:17m:11s]----
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

    std::string s;
    std::cin >> s;

    s.insert(s.begin(), ' ');

    std::vector<std::vector<int>> e(n + 1);

    for (int i = 0; i < n - 1; ++i)
    {
        int u, v;
        std::cin >> u >> v;

        e[u].push_back(v);
        e[v].push_back(u);
    }

    struct node
    {
        int parent;
        int depth;
        int size;
        int head;
        int wson;

        int blocked;

        int cnt;
        uint64 cost;
    };

    std::vector<node> tree(n + 1);

    std::map<int, std::vector<std::pair<int, int>>> pos;

    uint64 cnt = 0;

    auto build = [&](const auto& self, int u) -> void
    {
        tree[u].size = 1;
        tree[u].cnt = s[u] == '1';
        tree[u].cost = s[u] == '0';

        for (int v : e[u])
        {
            if (v != tree[u].parent)
            {
                tree[v].parent = u;
                tree[v].depth = tree[u].depth + 1;

                self(self, v);

                tree[u].size += tree[v].size;
                tree[u].cnt += tree[v].cnt;
                tree[u].cost += s[v] == '0' ? tree[v].cost : 0;

                if (tree[v].cnt)
                {
                    ++tree[u].blocked;
                }

                if (tree[v].size > tree[tree[u].wson].size)
                {
                    tree[u].wson = v;
                }
            }
        }

        if (s[u] == '1')
        {
            cnt += tree[u].cost;
        }

        if (tree[u].cnt == 0)
        {
            tree[u].cost = 0;
        }

        if (tree[u].blocked >= 2)
        {
            if (s[u] == '0')
            {
                cnt += tree[u].cost;
            }

            tree[u].cost = 0;
        }
    };

    auto build_head = [&](const auto& self, int u, int head) -> void
    {
        tree[u].head = head;

        if (s[u] == '1' or tree[u].blocked >= 2)
        {
            pos[head].emplace_back(tree[u].depth, u);
        }

        if (tree[u].wson)
        {
            self(self, tree[u].wson, head);

            for (int v : e[u])
            {
                if (v != tree[u].parent and v != tree[u].wson)
                {
                    self(self, v, v);
                }
            }
        }
    };

    const int root = s.find('1');

    if (root == -1)
    {
        while (q--)
        {
            std::cout << "2\n";
        }

        return 0;
    }

    build(build, root);
    build_head(build_head, root, root);

    for (auto& [key, value] : pos)
    {
        std::ranges::reverse(value);
    }

    auto jump_up = [&](int u) -> int
    {
        while (u)
        {
            auto it = std::ranges::lower_bound(pos[tree[u].head], std::pair{tree[u].depth, std::numeric_limits<int>::max()}, std::ranges::greater{});

            if (it != pos[tree[u].head].end())
            {
                return it->second;
            }

            u = tree[tree[u].head].parent;
        }

        return u;
    };

    while (q--)
    {
        int u, v;
        std::cin >> u >> v;

        if (tree[u].depth > tree[v].depth)
        {
            std::swap(u, v);
        }

        if (tree[v].cnt == 0)
        {
            std::cout << cnt + 1 << '\n';
            continue;
        }

        uint64 ans = cnt;

        if (s[v] == '0')
        {
            ans -= tree[v].cost;
        }

        if (s[u] == '0' and tree[u].blocked < 2)
        {
            ans -= tree[u].depth - tree[jump_up(u)].depth;
        }

        std::cout << ans << '\n';
    }

    return 0;
}