#pragma once

#include <bitset>
#include <format>
#include <print>
#include <stdexcept>
#include <string_view>

namespace Ban {
#define _BAN_PREFIX(x) #x
// Takes a number-like thing and puts double quotes around it
#define b(x) _BAN_PREFIX(x)

template <std::size_t N = 256> class Bassn {
  public:
    Bassn() = default;
    Bassn(std::string_view input);
    ~Bassn() = default;

    const std::bitset<N> &data() const noexcept { return m_Data; }

  private:
    std::bitset<N> m_Data;
};
} // namespace Ban

#define BAN_IMPLEMENTATION // bd me remove krdu ga
#ifdef BAN_IMPLEMENTATION
namespace Ban {
template <std::size_t N> Bassn<N>::Bassn(std::string_view input) {
    for (auto i = 0; const char &c : input) {
        if (c >= '0' && c <= '9') {
            std::println("char: {}, i: {}", c, i);
            m_Data.set(i++, c % 2);
        } else {
            throw std::invalid_argument("Input must be a number-like string");
        }
    }
}
} // namespace Ban
#endif // BAN_IMPLEMENTATION

namespace std {
template <std::size_t N> struct formatter<Ban::Bassn<N>> {
    // no special format specifiers at the moment
    constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const Ban::Bassn<N> &b, FormatContext &ctx) const {
        auto str = b.data().to_string();
        return std::format_to(ctx.out(), "{}", str);
    }
};
} // namespace std