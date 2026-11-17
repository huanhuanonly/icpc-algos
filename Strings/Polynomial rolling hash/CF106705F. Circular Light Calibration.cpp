/**
 * The 2026 ICPC China Guizhou Provincial Contest
 *
 * => F. Circular Light Calibration
 *
 * -> https://codeforces.com/gym/106705/problem/F
 *
 * Submissions ~> https://codeforces.com/gym/106705/submission/391802717 By huanhuanonly
 *
 * @b Polynomial-rolling-hash
 *
 * ----September 24, 2026 [00h:51m:39s]----
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

    int _;
    std::cin >> _;

    while (_--)
    {
        int n, k;
        std::cin >> n >> k;

        std::string a, b;
        std::cin >> a >> b;

        a = ' ' + a + a;
        b = ' ' + b + b;

        constexpr uint128 base = 911382323ULL;
        constexpr uint128 mod = 1ULL << 60;

        std::vector<uint64> p(a.size(), 1);
        std::vector<uint64> ha(a.size()), hb(b.size());
        std::vector<uint64> hra(a.size());

        constexpr uint64 hc0 = 7, hc1 = 13;

        for (int i = 1; i < a.size(); ++i)
        {
            p[i] = p[i - 1] * base % mod;
            ha[i] = (ha[i - 1] * base + (a[i] == '0' ? hc0 : hc1)) % mod;
            hb[i] = (hb[i - 1] * base + (b[i] == '0' ? hc0 : hc1)) % mod;

            hra[i] = (hra[i - 1] * base + (a[i] == '1' ? hc0 : hc1)) % mod;
        }

        auto $ = [&](const auto& h, int l, int r) -> uint64
        {
            return (h[r] + mod - uint128(h[l - 1]) * p[r - l + 1] % mod) % mod;
        };

        std::map<uint64, int> cnt;

        for (int i = 1; i <= n; ++i)
        {
            ++cnt[$(hb, i, i + n - 1)];
        }

        uint64 ans = 0;

        for (int l = 1; l <= n; ++l)
        {
            const int r = l + k - 1;
            ans += cnt[($(hra, l, r) + uint128(p[k]) * $(ha, r + 1, l + n - 1) % mod) % mod];
        }

        std::cout << ans << '\n';
    }

    return 0;
}