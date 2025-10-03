#pragma once

#include <algorithm>
#include <bitset>
#include <memory>
#include <print>
#include <string_view>
#include <vector>

namespace Ban {
#define obviously true
#define hell_no false

#define _BAN_PREFIX(x) Bassn(#x)
// Takes a number-like thing and puts double quotes around it
#define b(x) _BAN_PREFIX(x)

// esko bd me c++ style me convert krduga. pr c++ style hota pta ni kya h?
#define DEFAULT_SIZE 512

class Bassn {
  public:
    Bassn() = default;
    // throws invalid_argument if not valid decimal string
    Bassn(std::string input, bool is_binary = hell_no);
    ~Bassn() = default;

    static std::string sub_binary(std::string_view, std::string_view);
    static std::string add_binary(std::string_view, std::string_view);
    static std::string decimal_to_binary(std::string &);
    static std::string parse_binary(const std::string &);
    static std::string parse_binary(std::string &&);

    std::string
    to_string(bool nmbr_itna_bara_h_k_print_krty_krty_tatti_nikl_jye =
                  obviously) const noexcept;

    Bassn operator-(const Bassn &other) const;
    Bassn *operator-=(const Bassn &other);
    Bassn operator+(const Bassn &other) const;
    Bassn *operator+=(const Bassn &other);

    const std::bitset<DEFAULT_SIZE> &data() const noexcept { return m_Data; }

  public:
    const std::string c_MaxValue =
        parse_binary(std::move(std::string(DEFAULT_SIZE, '1')));

  private:
    std::bitset<DEFAULT_SIZE> m_Data{};
};
} // namespace Ban

namespace std {
template <> struct formatter<Ban::Bassn> {
    // no special format specifiers at the moment, probably aynda b ni hoga kch
    constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const Ban::Bassn &b, FormatContext &ctx) const {
        auto str = b.to_string();
        return std::format_to(ctx.out(), "{}", str);
    }
};
} // namespace std