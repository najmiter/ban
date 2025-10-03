#pragma once

#include <algorithm>
#include <bitset>
#include <memory>
#include <print>
#include <stdexcept>
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

    std::string to_string(
        bool nmbr_itna_bara_h_k_tatti_nikl_jye = obviously) const noexcept;

    Bassn operator-(const Bassn &other) const;
    Bassn *operator-=(const Bassn &other);
    Bassn operator+(const Bassn &other) const;
    Bassn *operator+=(const Bassn &other);

    const std::bitset<DEFAULT_SIZE> &data() const noexcept { return m_Data; }

  public:
    const std::string c_MaxValue{
        parse_binary(std::move(std::string(DEFAULT_SIZE, '1')))};

  private:
    std::bitset<DEFAULT_SIZE> m_Data{};
};
} // namespace Ban

namespace Ban {
Bassn::Bassn(std::string input, bool is_binary)
    : /* probably the slowest shit possible but i didn't like that chunks thing
         or whatever it is cool kids do */
      m_Data{is_binary ? input : decimal_to_binary(input)} {}

inline std::string Bassn::sub_binary(std::string_view a, std::string_view b) {
    int i = (int)a.length() - 1;
    int j = (int)b.length() - 1;
    auto borrow = 0;
    std::string result = "";

    while (i >= 0 || j >= 0 || borrow) {
        auto digitA = i >= 0 ? a[i] - '0' : 0;
        auto digitB = j >= 0 ? b[j] - '0' : 0;

        auto diff = digitA - digitB - borrow;
        if (diff < 0) {
            diff += 2;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result = std::to_string(diff) + result;

        i--;
        j--;
    }

    return result;
}

inline std::string Bassn::add_binary(std::string_view a, std::string_view b) {
    int i = (int)a.length() - 1;
    int j = (int)b.length() - 1;
    auto carry = 0;
    std::string result = "";

    while (i >= 0 || j >= 0 || carry) {
        auto digitA = i >= 0 ? a[i] - '0' : 0;
        auto digitB = j >= 0 ? b[j] - '0' : 0;

        auto sum = digitA + digitB + carry;
        result = std::to_string(sum % 2) + result;
        carry = std::floor(sum / 2);

        i--;
        j--;
    }

    return result;
}

inline std::string Bassn::decimal_to_binary(std::string &num) {
    if (num == "0")
        return "0";

    std::string result;

    // socha ni tha k 2 nmbrs divide krny py itni khushi 2 class k bd b kbi
    // zindgi me ho ge 🥹
    while (!(num.size() == 1 && num[0] == '0')) {
        std::string next;
        int carry = 0;

        for (char c : num) {
            if (!(c >= '0' && c <= '9')) {
                throw std::invalid_argument(
                    "Invalid character in input string");
            }
            int cur = carry * 10 + (c - '0');
            next.push_back((cur / 2) + '0');
            carry = cur % 2;
        }

        result.push_back('0' + carry); // remainder is the next binary digit bcz
                                       // 2 se divide kia tha to ak hoga ya zero

        auto pos = next.find_first_not_of('0');
        if (pos == std::string::npos) {
            num = "0";
        } else {
            num = next.substr(pos);
        }
    }

    std::reverse(result.begin(), result.end());
    return result;
}

inline std::string Bassn::parse_binary(const std::string &bits) {
    auto multiply_by_two = [](const std::string &num) {
        std::string result;
        int carry = 0;
        for (int i = (int)num.size() - 1; i >= 0; --i) {
            int d = (num[i] - '0') * 2 + carry;
            result.push_back('0' + (d % 10));
            carry = d / 10;
        }
        if (carry) {
            result.push_back('0' + carry);
        }
        std::reverse(result.begin(), result.end());
        return result;
    };
    auto add_one = [](const std::string &num) {
        std::string result = num;
        int carry = 1;
        for (int i = (int)result.size() - 1; i >= 0 && carry; --i) {
            int d = (result[i] - '0') + carry;
            result[i] = '0' + (d % 10);
            carry = d / 10;
        }
        if (carry) {
            result.insert(result.begin(), '1');
        }
        return result;
    };
    std::string result = "0";
    for (char bit : bits) {
        // shift left = multiply by 2
        result = multiply_by_two(result);
        // if bit = 1, add one
        if (bit == '1') {
            result = add_one(result);
        }
    }
    // wesy agr yhi krna tha to itni conversions ki kya zrurt thi
    // rethinking my life choices. dam
    return result;
}

inline std::string Bassn::parse_binary(std::string &&bits) {
    return parse_binary(bits);
}

inline std::string
Bassn::to_string(bool nmbr_itna_bara_h_k_tatti_nikl_jye) const noexcept {
    auto str = m_Data.to_string();
    if (nmbr_itna_bara_h_k_tatti_nikl_jye && str.size() > 4096) {
        return "\xF0\x9F\x92\xA9 \xF0\x9F\x92\xA9 \xF0\x9F\x92\xA9";
    }
    return parse_binary(str);
}

inline Bassn Bassn::operator-(const Bassn &other) const {
    return Bassn(sub_binary(this->m_Data.to_string(), other.m_Data.to_string()),
                 obviously);
}

inline Bassn *Bassn::operator-=(const Bassn &other) {
    this->m_Data = std::bitset<DEFAULT_SIZE>(
        sub_binary(this->m_Data.to_string(), other.m_Data.to_string()));
    return this;
}

inline Bassn Bassn::operator+(const Bassn &other) const {
    return Bassn(add_binary(this->m_Data.to_string(), other.m_Data.to_string()),
                 obviously);
}

inline Bassn *Bassn::operator+=(const Bassn &other) {
    this->m_Data = std::bitset<DEFAULT_SIZE>(
        add_binary(this->m_Data.to_string(), other.m_Data.to_string()));
    return this;
}
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