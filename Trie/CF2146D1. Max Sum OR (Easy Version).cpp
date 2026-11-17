/**
 * Codeforces Round 1052 (Div. 2)
 *
 * => D1. Max Sum OR (Easy Version) ( @c 1500 )
 *
 * -> https://codeforces.com/contest/2146/problem/D1
 *
 * Submissions ~> https://codeforces.com/contest/2146/submission/339767383 By huanhuanonly
 *
 * @b Binary-trie
 *
 * ----September 24, 2025 [01h:31m:47s]----
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

#ifdef __GNUC__
using int128 = __int128;
using uint128 = unsigned __int128;
#endif

using real32 = float;
using real64 = double;
using real128 = long double;

class Trie
{
public:

    struct node
    {
        std::array<int, 2> word;
        int id;
        int cnt;
    };

    std::vector<node> tree;
    int size;

    Trie() : tree(1), size(0) { }

    int apply_node()
    {
        tree.push_back({});
        return tree.size() - 1;
    }

    void insert(int n, int id)
    {
        ++size;

        int cur = 0;

        for (int i = (1 << 30 - 1); i >= 1; i >>= 1)
        {
            const bool c = n & i;

            if (tree[cur].word[c] == 0)
            {
                tree[cur].word[c] = apply_node();
            }

            cur = tree[cur].word[c];
            ++tree[cur].cnt;
        }

        tree[cur].id = id;
    }

    void erase(int n)
    {
        --size;

        int cur = 0;

        for (int i = (1 << 30 - 1); i >= 1; i >>= 1)
        {
            const bool c = n & i;

            cur = tree[cur].word[c];
            --tree[cur].cnt;
        }
    }

    int find_max(int n)
    {
        if (size == 0)
        {
            return 0;
        }

        int cur = 0;

        for (int i = (1 << 30 - 1); i >= 1; i >>= 1)
        {
            const bool c = not (n & i);

            if (tree[cur].word[c] and tree[tree[cur].word[c]].cnt)
            {
                cur = tree[cur].word[c];
            }
            else
            {
                cur = tree[cur].word[not c];
            }
        }

        return tree[cur].id;
    }
};

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __huanhuanonly_localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int _;
    std::cin >> _;

    while (_--)
    {
        int l, r;
        std::cin >> l >> r;

        std::vector<int> v(r - l + 1);
        std::iota(v.begin(), v.end(), l);

        Trie trie;

        for (int i = l; i <= r; ++i)
        {
            trie.insert(i, i);
        }

        uint64 sum = 0;

        std::set<int> st;

        for (int i = r; i >= l; --i)
        {
            if (not st.contains(i))
            {
                st.insert(i);
                trie.erase(i);

                int value = trie.find_max(i);
                trie.erase(value);

                st.insert(value);
                sum += (value | i) * 2;
                std::swap(v[value], v[i]);
            }
        }

        std::cout << sum << '\n';

        for (int i = 0; i < v.size(); ++i)
        {
            std::cout << v[i] << ' ';
        }

        std::cout.put('\n');
    }

    return 0;
}