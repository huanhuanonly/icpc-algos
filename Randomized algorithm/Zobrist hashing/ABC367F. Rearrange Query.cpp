/**
 * AtCoder Beginner Contest 367
 *
 * => F - Rearrange Query ( @c 500 )
 *
 * -> https://atcoder.jp/contests/abc367/tasks/abc367_f
 *
 * Submissions ~> https://atcoder.jp/contests/abc367/submissions/56934180 By huanhuanonly
 *
 * @b Zobrist-hashing
 *
 * ----August 21, 2024 [00h:00m:55s]----
*/

#include <bits/stdc++.h>

using uint    = unsigned int;
using llong   = long long int;
using ullong  = unsigned long long int;
using ldouble = long double;

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

#ifdef __localhost
    ::freopen("in", "r", stdin);
    ::freopen("out", "w", stdout);
#endif

    int n, q;
    std::cin >> n >> q;

    std::vector<ullong> a(n + 1), b(n + 1);

    std::vector<ullong> hash(n + 1);
    std::for_each(hash.begin(), hash.end(), [rng = std::mt19937()](ullong& value) mutable -> void { value = rng(); });

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> a[i];
        a[i] = a[i - 1] + hash[a[i]];
    }

    for (int i = 1; i <= n; ++i)
    {
        std::cin >> b[i];
        b[i] = b[i - 1] + hash[b[i]];
    }

    while (q--)
    {
        int l1, r1, l2, r2;
        std::cin >> l1 >> r1 >> l2 >> r2;

        if (a[r1] - a[l1 - 1] == b[r2] - b[l2 - 1])
            std::cout << "Yes\n";
        else
            std::cout << "No\n";
    }

    return 0;
}