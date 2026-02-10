using hash_result_type = uint64;

constexpr hash_result_type hash_base = std::array{449, 100003, 1000003, 1000000007}[0];
constexpr hash_result_type hash_mod  = std::array{998244353ULL, 4294967291ULL}[0];

static_assert(hash_base < hash_mod);
static_assert(hash_mod <= std::numeric_limits<hash_result_type>::max() / hash_mod);

template<typename _Tp>
struct Hash : std::hash<_Tp>
{ using value_type = _Tp; };

template<std::integral _Tp>
struct Hash<_Tp>
{
    using value_type = _Tp;

    [[nodiscard]] static constexpr
    hash_result_type
    splitmix64(hash_result_type __value) noexcept
    {
        __value += 0x9e3779b97f4a7c15;
        __value = (__value ^ (__value >> 30)) * 0xbf58476d1ce4e5b9;
        __value = (__value ^ (__value >> 27)) * 0x94d049bb133111eb;
        return __value ^ (__value >> 31);
    }

    [[nodiscard]]
    hash_result_type
    operator()(value_type __value) const noexcept
    {
        static const hash_result_type fixed_random =
            std::chrono::steady_clock::now().time_since_epoch().count();

        return splitmix64(fixed_random + __value);
    }
};

template<typename _Ft, typename _St>
struct Hash<std::pair<_Ft, _St>>
{
    using value_type = std::pair<_Ft, _St>;

    [[nodiscard]] constexpr
    hash_result_type
    operator()(const value_type& __value) const noexcept
    {
        return (Hash<_Ft>{}(__value.first) % hash_mod * hash_base % hash_mod + Hash<_St>{}(__value.second) % hash_mod) % hash_mod;
    }
};

template<typename... _Args>
struct Hash<std::tuple<_Args...>>
{
    using value_type = std::tuple<_Args...>;

    [[nodiscard]] constexpr
    hash_result_type
    operator()(const value_type& __value) const noexcept
    {
        return std::apply([](auto&&... args) -> hash_result_type
        {
            hash_result_type result = 0;

            for (const hash_result_type& i : std::array{{Hash<_Args...>{}(args)...}})
            {
                result *= hash_base;
                result %= hash_mod;
                result += i % hash_mod;
                result %= hash_mod;
            }

            return result;
        }, __value);
    }
};

template<std::ranges::input_range _Tp>
struct Hash<_Tp>
{
    using value_type = _Tp;

    [[nodiscard]] constexpr
    hash_result_type
    operator()(const value_type& __value) const noexcept
    {
        hash_result_type result = 0;

        auto begin = std::ranges::begin(__value);
        auto end   = std::ranges::end(__value);

        if constexpr (
            std::is_array_v<std::remove_reference_t<value_type>> and
            std::is_same_v<std::remove_extent_t<std::remove_reference_t<value_type>>, char>)
        {
            --end;
        }

        for (; begin != end; ++begin)
        {
            const auto& i = *begin;

            result *= hash_base;
            result %= hash_mod;

            if constexpr (requires{ value_type::value_type; })
            {
                result += Hash<typename _Tp::value_type>{}(i) % hash_mod;
            }
            else
            {
                result += Hash<std::remove_reference_t<decltype(i)>>{}(i) % hash_mod;
            }

            result %= hash_mod;
        }

        return result;
    }
};

template<>
struct Hash<void>
{
    template<typename _Tp>
    [[nodiscard]] constexpr
    hash_result_type
    operator()(const _Tp& __value) const noexcept
    {
        return Hash<_Tp>{}(__value);
    }
};

class RangeHash
{
public:

    using container_type = std::vector<std::pair<hash_result_type, hash_result_type>>;
    using size_type = std::size_t;

    static constexpr auto npos = static_cast<size_type>(-1);

    RangeHash() noexcept
        : _M_c{{0, 1}}
    { };

    template<std::input_iterator _Iter, std::sentinel_for<_Iter> _Sent>
    RangeHash(_Iter __first, _Sent __last)
        : RangeHash()
    { append(__first, __last); }

    template<std::ranges::input_range _Range>
    RangeHash(_Range&& __r)
        : RangeHash()
    { append(std::forward<_Range>(__r)); }

    template<typename _Tp>
    void
    push_back(const _Tp& __value)
    {
        _M_c.emplace_back(
            (_M_c.back().first * hash_base % hash_mod + Hash<void>{}(__value) % hash_mod) % hash_mod,
            _M_c.back().second * hash_base % hash_mod);
    }

    template<std::input_iterator _Iter, std::sentinel_for<_Iter> _Sent>
    void
    append(_Iter __first, _Sent __last)
    {
        if constexpr (
            std::sized_sentinel_for<_Sent, _Iter> and
            requires(container_type c) { c.reserve(std::size_t{}); })
        {
            _M_c.reserve(_M_c.size() + static_cast<std::size_t>(std::ranges::distance(__first, __last)));
        }

        for (; __first != __last; ++__first)
        {
            push_back(*__first);
        }
    }

    template<std::ranges::input_range _Range>
    void
    append(_Range&& __r)
    { append(std::ranges::begin(__r), std::ranges::end(__r)); }

    void
    pop_back(size_type __n = 1)
    { _M_c.resize(_M_c.size() - std::min(__n, _M_c.size() - 1)); }

    [[nodiscard]] size_type
    size() const noexcept
    { return _M_c.size() - 1; }

    [[nodiscard]] bool
    empty() const noexcept
    { return size() == 0; }

    [[nodiscard]] hash_result_type
    operator()() const noexcept
    { return _M_c.back().first; }

    [[nodiscard]] hash_result_type
    operator()(size_type __pos, size_type __n) const noexcept
    {
        if (__pos >= size())
        {
            return 0;
        }

        if (__pos + __n >= _M_c.size())
        {
            __n = _M_c.size() - __pos - 1;
        }

        return (_M_c[__pos + __n].first + hash_mod - _M_c[__pos].first * _M_c[__n].second % hash_mod) % hash_mod;
    }

    [[nodiscard]] hash_result_type
    operator[](size_type __i) const noexcept
    { return (*this)(__i, __i); }

    [[nodiscard]] hash_result_type
    front(size_type __n = 1) const noexcept
    { return _M_c[std::min(__n, size())].first; }

    [[nodiscard]] hash_result_type
    back(size_type __n = 1) const noexcept
    { return empty() ? 0 : (*this)(size() - std::min(__n, size()), std::min(__n, size())); }

    [[nodiscard]] bool
    operator==(const RangeHash& __rhs) const noexcept
    { return (*this)() == __rhs(); }

    [[nodiscard]] bool
    operator!=(const RangeHash& __rhs) const noexcept
    { return (*this)() != __rhs(); }

    [[nodiscard]] bool
    operator<(const RangeHash& __rhs) const noexcept
    { return (*this)() < __rhs(); }

    [[nodiscard]] bool
    operator<=(const RangeHash& __rhs) const noexcept
    { return (*this)() <= __rhs(); }

    [[nodiscard]] bool
    operator>(const RangeHash& __rhs) const noexcept
    { return (*this)() > __rhs(); }

    [[nodiscard]] bool
    operator>=(const RangeHash& __rhs) const noexcept
    { return (*this)() >= __rhs(); }

    [[nodiscard]] bool
    matches(const RangeHash& __h, size_type __pos) const noexcept
    { return (*this)(__pos, __h.size()) == __h(); }

    [[nodiscard]] bool
    starts_with(const RangeHash& __h) const noexcept
    { return matches(__h, 0); }

    [[nodiscard]] bool
    ends_with(const RangeHash& __h) const noexcept
    { return matches(__h, size() - std::min(__h.size(), size())); }

    [[nodiscard]] size_type
    find(const RangeHash& __h, size_type __pos = 0) const noexcept
    {
        const auto n1 = size(), n2 = __h.size();

        for (; __pos + n2 <= n1; ++__pos)
        {
            if (matches(__h, __pos))
            {
                return __pos;
            }
        }

        return npos;
    }

    [[nodiscard]] size_type
    rfind(const RangeHash& __h, size_type __pos = std::numeric_limits<size_type>::max()) const noexcept
    {
        const auto n1 = size(), n2 = __h.size();

        if (__pos >= size())
        {
            __pos = size();
        }
        else
        {
            ++__pos;
        }

        while (__pos--)
        {
            if (matches(__h, __pos))
            {
                return __pos;
            }
        }

        return npos;
    }

    [[nodiscard]] bool
    contains(const RangeHash& __h) const noexcept
    { return find(__h) != npos; }

    enum OverlapMode
    {
        AllowOverlap,
        NoOverlap
    };

    [[nodiscard]] size_type
    count(const RangeHash& __h, OverlapMode __mode = AllowOverlap) const noexcept
    {
        if (__h.size() == 0)
        {
            return 0;
        }

        size_type cnt = 0;

        if (__mode == AllowOverlap)
        {
            for (size_type pos = find(__h); pos != npos; ++cnt, pos = find(__h, pos + 1));
        }
        else
        {
            for (size_type pos = find(__h); pos != npos; ++cnt, pos = find(__h, pos + __h.size()));
        }

        return cnt;
    }

    [[nodiscard]] size_type
    longest_suffix_prefix_overlap(const RangeHash& __h) const noexcept
    {
        for (size_type i = std::min(size(), __h.size()); i > 0; --i)
        {
            if (back(i) == __h.front(i))
            {
                return i;
            }
        }

        return 0;
    }

private:

    container_type _M_c;
};