/**
 * Educational DP Contest
 * 
 * => R - Walk ( @c 100 )
 * 
 * -> https://atcoder.jp/contests/dp/tasks/dp_r
 * 
 * Submissions ~> https://atcoder.jp/contests/dp/submissions/75006544 By huanhuanonly
 * 
 * @b Matrix-DP and @b Matrix-exponentiation
 * 
 * ----April 17, 2026 [09h:55m:02s]----
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

    uint64 n, k;
    std::cin >> n >> k;

    constexpr uint64 mod = 1e9 + 7;

    struct Matrix
    {
        std::vector<std::vector<uint64>> matrix;

        explicit Matrix(std::size_t n)
            : matrix(n, std::vector<uint64>(n))
        { }

        std::size_t size() const
        { return matrix.size(); }

        Matrix operator*(const Matrix& other) const
        {
            Matrix res(matrix.size());

            for (std::size_t i = 0; i < size(); ++i)
            {
                for (std::size_t k = 0; k < size(); ++k)
                {
                    const auto& mik = matrix[i][k];
                    for (std::size_t j = 0; j < size(); ++j)
                    {
                        (res.matrix[i][j] += mik * other.matrix[k][j] % mod) %= mod;
                    }
                }
            }

            return res;
        }

        Matrix pow(uint64 n)
        {
            Matrix res(size());

            for (std::size_t i = 0; i < size(); ++i)
            {
                res.matrix[i][i] = 1;
            }

            for (; n; *this = *this * *this, n >>= 1)
            {
                if (n & 1)
                {
                    res = res * *this;
                }
            }

            return res;
        }
    };

    Matrix m(n);

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            std::cin >> m.matrix[i][j];
        }
    }

    m = m.pow(k);

    uint64 sum = 0;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            (sum += m.matrix[i][j]) %= mod;
        }
    }

    std::cout << sum << '\n';

    return 0;
}