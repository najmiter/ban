#pragma once

#include <algorithm>
#include <bitset>
#include <print>
#include <stdexcept>
#include <string_view>
#include <vector>

namespace Ban {
#define _BAN_PREFIX(x) #x
// Takes a number-like thing and puts double quotes around it
// (wesy ak keystroke extra e h. pr thora asy lgta a jsy nmbr likh rhy hn.
// to bs es liye)
#define b(x) _BAN_PREFIX(x)

template <std::size_t N = 256> class Bassn {
  public:
    Bassn() = default;
    // throws invalid_argument if not valid decimal string
    Bassn(std::string input);
    ~Bassn() = default;

    std::string add_binary(std::string_view, std::string_view);
    std::string decimal_to_binary(std::string &);
    std::string to_string() const noexcept;

    const std::bitset<N> &data() const noexcept { return m_Data; }

  private:
    std::bitset<N> m_Data;
};
} // namespace Ban

namespace Ban {
template <std::size_t N>
Bassn<N>::Bassn(std::string input)
    : /* probably the slowest shit possible but i didn't like that chunks thing
         or whatever it is cool kids do */
      m_Data{decimal_to_binary(input)} {}

template <std::size_t N>
inline std::string Bassn<N>::add_binary(std::string_view a,
                                        std::string_view b) {
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
template <std::size_t N>
inline std::string Bassn<N>::decimal_to_binary(std::string &num) {
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
template <std::size_t N>
inline std::string Bassn<N>::to_string() const noexcept {
    auto str = m_Data.to_string();
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
    for (char bit : str) {
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
} // namespace Ban

namespace std {
template <std::size_t N> struct formatter<Ban::Bassn<N>> {
    // no special format specifiers at the moment, probably aynda b ni hoga kch
    constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

    template <typename FormatContext>
    auto format(const Ban::Bassn<N> &b, FormatContext &ctx) const {
        auto str = b.to_string();
        return std::format_to(ctx.out(), "{}", str);
    }
};
} // namespace std