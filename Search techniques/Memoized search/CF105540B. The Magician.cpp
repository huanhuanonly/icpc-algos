/**
 * 2024 China Collegiate Programming Contest (CCPC) Jinan Site (The 3rd Universal Cup. Stage 17: Jinan)
 *
 * => B. The Magician
 *
 * -> https://codeforces.com/gym/105540/problem/B
 *
 * Submissions ~> https://codeforces.com/gym/105540/submission/397267124 By huanhuanonly
 *
 * @b Memoized-search
 *
 * ----November 04, 2026 [02h:05m:45s]----
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
        int n;
        std::cin >> n;

        std::array<int, 4> card{};

        {
            std::string s;
            for (int i = 0; i < n; ++i)
            {
                std::cin >> s;

                if (s[1] == 'D')
                {
                    ++card[0];
                }
                else if (s[1] == 'C')
                {
                    ++card[1];
                }
                else if (s[1] == 'H')
                {
                    ++card[2];
                }
                else
                {
                    ++card[3];
                }
            }
        }

        std::array<int, 6> t;

        for (std::size_t i = 0; i < t.size(); ++i)
        {
            std::cin >> t[i];
        }

        for (auto& i : t | std::views::take(card.size()))
        {
            if (i)
            {
                i = 3;
            }
        }

        if (t[t.size() - 2])
        {
            t[t.size() - 2] = 0;
            ++t.back();
        }

        int total = 0;

        for (auto& i : card)
        {
            total += i / 5;
            i %= 5;
        }

        std::map<std::pair<decltype(card), decltype(t)>, int> record;

        auto dfs = [&](const auto& self, const decltype(card)& card, const decltype(t)& t) -> int
        {
            if (const auto it = record.find(std::pair(card, t)); it != record.end())
            {
                return it->second;
            }

            int& max = record[std::pair(card, t)];

            for (const auto& i : card)
            {
                max += i / 5;
            }

            if (not std::ranges::any_of(t, std::identity{}))
            {
                return max;
            }

            for (std::size_t i = 0; i < card.size(); ++i)
            {
                if (card[i])
                {
                    for (std::size_t j = 0; j < card.size(); ++j)
                    {
                        if (i != j)
                        {
                            if (t[j])
                            {
                                auto card_ = card;
                                auto t_ = t;

                                --card_[i], ++card_[j];
                                --t_[j];

                                max = std::max(max, self(self, card_, t_));
                            }

                            if (t.back())
                            {
                                auto card_ = card;
                                auto t_ = t;

                                --card_[i], ++card_[j];
                                --t_.back();

                                max = std::max(max, self(self, card_, t_));
                            }
                        }
                    }
                }
            }

            return max;
        };

        std::cout << total + dfs(dfs, card, t) << '\n';
    }

    return 0;
}