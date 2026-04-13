class Kmp
{
public:

    using value_type = std::string::value_type;
    using size_type = int;
    
    static constexpr size_type npos = size_type(-1);

    Kmp() noexcept = default;

    Kmp(std::string __pattern)
        : _M_pattern(std::move(__pattern)), _M_lps(_M_pattern.size())
    { _M_build(); }

    [[nodiscard]] size_type
    size() const noexcept
    { return static_cast<size_type>(_M_pattern.size()); }
    
    [[nodiscard]] bool
    empty() const noexcept
    { return size() == 0; }
    
    [[nodiscard]] size_type
    longest_prefix_suffix(size_type __i) const noexcept
    { return _M_lps[__i]; }

    [[nodiscard]] size_type
    lps(size_type __i) const noexcept
    { return _M_lps[__i]; }

    [[nodiscard]] std::string_view
    pattern() const noexcept
    { return _M_pattern; }
    
    [[nodiscard]] size_type
    find(std::string_view __s) const
    {
        if (empty())
        {
            return 0;
        }

        for (size_type i = 0, c = 0; i < size_type(__s.size()); ++i)
        {
            while (c > 0 and __s[i] != _M_pattern[c])
            {
                c = _M_lps[c - 1];
            }

            if (__s[i] == _M_pattern[c])
            {
                ++c;
            }

            if (c == size())
            {
                return i + 1 - size();
            }
        }

        return npos;
    }

    template<std::output_iterator<size_type> _Out>
    _Out
    find_all(std::string_view __s, _Out __result) const
    {
        if (empty())
        {
            return std::ranges::copy(std::views::iota(size_type(0), size_type(__s.size() + 1)), __result).out;
        }

        for (size_type i = 0, c = 0; i < size_type(__s.size()); ++i)
        {
            while (c > 0 and __s[i] != _M_pattern[c])
            {
                c = _M_lps[c - 1];
            }

            if (__s[i] == _M_pattern[c])
            {
                ++c;
            }

            if (c == size())
            {
                *__result = i + 1 - size();
                ++__result;
                c = _M_lps[c - 1];
            }
        }

        return __result;
    }

#if __has_include(<generator>) && defined(__cpp_lib_generator)
    [[nodiscard]] std::generator<size_type>
    find_all(std::string_view __s) const
    {
        if (empty())
        {
            for (size_type i = 0; i <= size_type(__s.size()); ++i)
            {
                co_yield i;
            }

            co_return;
        }

        for (size_type i = 0, c = 0; i < size_type(__s.size()); ++i)
        {
            while (c > 0 and __s[i] != _M_pattern[c])
            {
                c = _M_lps[c - 1];
            }

            if (__s[i] == _M_pattern[c])
            {
                ++c;
            }

            if (c == size())
            {
                co_yield i + 1 - size();
                c = _M_lps[c - 1];
            }
        }
    }
#endif

    [[nodiscard]] bool
    contains(std::string_view __s) const
    { return find(__s) != npos; }

    [[nodiscard]] size_type
    count_matches(std::string_view __s) const
    {
        if (empty())
        {
            return size_type(__s.size() + 1);
        }

        size_type cnt = 0;

        for (size_type i = 0, c = 0; i < size_type(__s.size()); ++i)
        {
            while (c > 0 and __s[i] != _M_pattern[c])
            {
                c = _M_lps[c - 1];
            }

            if (__s[i] == _M_pattern[c])
            {
                ++c;
            }

            if (c == size())
            {
                ++cnt;
                c = _M_lps[c - 1];
            }
        }

        return cnt;
    }

private:

    void
    _M_build()
    {
        for (size_type i = 1; i < size(); ++i)
        {
            size_type len = _M_lps[i - 1];

            while (len > 0 and _M_pattern[len] != _M_pattern[i])
            {
                len = _M_lps[len - 1];
            }

            if (_M_pattern[len] == _M_pattern[i])
            {
                ++len;
            }

            _M_lps[i] = len;
        }
    }

private:
    
    std::string _M_pattern;
    std::vector<size_type> _M_lps;
};