/**
 * The 13th Shandong ICPC Provincial Collegiate Programming Contest
 * 
 * => K. Difficult Constructive Problem
 * 
 * -> https://codeforces.com/gym/104417/problem/K
 * 
 * Submissions ~> https://codeforces.com/gym/104417/submission/361147831 By huanhuanonly
 * 
 * @b Constructive and @b Classification-discussion
 * 
 * ----February 02, 2026 [22h:05m:01s]----
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
        
        auto compute = [&](std::string s, const char front) -> bool
        {
            s.front() = front;

            const int len = n - 1 - s.find_last_not_of('?');

            int min = 0, max = len;

            std::vector<std::string_view> list;

            static auto $ = [](const char& c) -> char&
            {
                return const_cast<char&>(c);
            };

            for (int i = 1; i < n - len; ++i)
            {
                if (s[i] == '?')
                {
                    int j = i--;
                    for (; s[j] == '?'; ++j);

                    if (s[i] == s[j])
                    {
                        max += (j - i - 1) + (j - i - 1 & 1);
                    }
                    else
                    {
                        ++min;
                        max += (j - i - 1) + (j - i - 1 & 1 ^ 1);
                    }

                    list.emplace_back(s.begin() + i, s.begin() + j + 1);
                    i = j;
                }
                else if (s[i - 1] != '?' and s[i - 1] != s[i])
                {
                    ++min;
                    ++max;
                }
            }

            if (not (min <= k and k <= max))
            {
                return false;
            }

            auto case00 = [&](std::string_view t) -> void
            {
                if (t.size() & 1 ^ 1)
                {
                    $(t.front()) = '0';
                    t.remove_prefix(1);
                }

                for (int i = 0; i < t.size(); i += 2)
                {
                    if (max - 2 >= k)
                    {
                        $(t[i]) = '0';
                        max -= 2;
                    }
                    else
                    {
                        $(t[i]) = '1';
                        min += 2;
                    }

                    if (i + 1 < t.size())
                    {
                        $(t[i + 1]) = '0';
                    }
                }
            };

            auto case01 = [&](std::string_view t) -> void
            {
                if (t.size() & 1)
                {
                    $(t.front()) = '0';
                    t.remove_prefix(1);
                }
                
                if (not t.empty())
                {
                    $(t.back()) = '0';
                    t.remove_suffix(1);
    
                    case00(t);
                }
            };

            auto case10 = [&](std::string_view t) -> void
            {
                $(t.front()) = '0';
                t.remove_prefix(1);

                if (not t.empty())
                {
                    case00(t);
                }
            };

            auto case11 = [&](std::string_view t) -> void
            {
                if (t.size() & 1 ^ 1 and min + 2 <= k)
                {
                    $(t.front()) = '0';
                    min += 2;
                    case01(t.substr(1, t.size() - 1));
                }
                else if (min + 2 <= k)
                {
                    $(t.front()) = $(t.back()) = '0';
                    min += 2;

                    if (t.size() > 2)
                    {
                        case00(t.substr(1, t.size() - 2));
                    }
                }
                else
                {
                    for (int i = 0; i < t.size(); ++i)
                    {
                        $(t[i]) = '1';
                    }

                    max -= t.size() + (t.size() & 1);
                }
            };

            for (const auto& t : list)
            {
                if (t.front() == t.back())
                {
                    if (t.front() == '0')
                    {
                        case00(t.substr(1, t.size() - 2));
                    }
                    else
                    {
                        case11(t.substr(1, t.size() - 2));
                    }
                }
                else
                {
                    if (t.front() == '0')
                    {
                        case01(t.substr(1, t.size() - 2));
                    }
                    else
                    {
                        case10(t.substr(1, t.size() - 2));
                    }
                }
            }

            if (min <= k and len)
            {
                int i = n - len;

                if (s[i - 1] == '1')
                {
                    if (min + 1 <= k)
                    {
                        s[i++] = '0';
                        ++min;
                    }
                    else
                    {
                        for (; i < n; ++i)
                        {
                            s[i] = '1';
                        }

                        max -= len;
                    }
                }

                if (k < max)
                {
                    std::ranges::fill(s.begin() + i, s.begin() + (i + max - k), '0');
                    i += max - k;
                    max = k;
                }

                for (; i < n; ++i)
                {
                    if (s[i - 1] == '1')
                    {
                        s[i] = '0';
                    }
                    else
                    {
                        s[i] = '1';
                    }

                    ++min;
                }
            }

            if (min == k)
            {
                assert(min == max);
                
                assert([&]() -> bool
                {
                    int cnt = 0;

                    for (int i = 1; i < n; ++i)
                    {
                        cnt += s[i] != s[i - 1];
                    }

                    return cnt == k;
                }());

                std::cout << s << '\n';
                return true;
            }
            else
            {
                return false;
            }
        };

        std::string s;
        std::cin >> s;
        
        if (s.front() == '?')
        {
            if (not compute(s, '0') and not compute(s, '1'))
            {
                std::cout << "Impossible\n";
            }
        }
        else
        {
            if (not compute(s, s.front()))
            {
                std::cout << "Impossible\n";
            }
        }
    }

    return 0;
}