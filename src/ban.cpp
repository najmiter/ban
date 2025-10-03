#include "ban.hpp"

#include <stdexcept>

namespace Ban {
Bassn::Bassn(std::string input, bool is_binary)
    : /* probably the slowest shit possible but i didn't like that chunks thing
         or whatever it is cool kids do */
      m_Data{is_binary ? input : decimal_to_binary(input)} {}

std::string Bassn::sub_binary(std::string_view a, std::string_view b) {
    int i = (int)a.size() - 1;
    int j = (int)b.size() - 1;
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

std::string Bassn::add_binary(std::string_view a, std::string_view b) {
    int i = (int)a.size() - 1;
    int j = (int)b.size() - 1;
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

std::string Bassn::decimal_to_binary(std::string &num) {
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

std::string Bassn::parse_binary(const std::string &bits) {
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

std::string Bassn::parse_binary(std::string &&bits) {
    return parse_binary(bits);
}

std::string Bassn::to_string(
    bool nmbr_itna_bara_h_k_print_krty_krty_tatti_nikl_jye) const noexcept {
    auto str = m_Data.to_string();
    if (nmbr_itna_bara_h_k_print_krty_krty_tatti_nikl_jye &&
        str.size() > 4096) {
        return "\xF0\x9F\x92\xA9 \xF0\x9F\x92\xA9 \xF0\x9F\x92\xA9";
    }
    return parse_binary(str);
}

Bassn Bassn::operator-(const Bassn &other) const {
    return Bassn(sub_binary(this->m_Data.to_string(), other.m_Data.to_string()),
                 obviously);
}

Bassn *Bassn::operator-=(const Bassn &other) {
    this->m_Data = std::bitset<DEFAULT_SIZE>(
        sub_binary(this->m_Data.to_string(), other.m_Data.to_string()));
    return this;
}

Bassn Bassn::operator+(const Bassn &other) const {
    return Bassn(add_binary(this->m_Data.to_string(), other.m_Data.to_string()),
                 obviously);
}

Bassn *Bassn::operator+=(const Bassn &other) {
    this->m_Data = std::bitset<DEFAULT_SIZE>(
        add_binary(this->m_Data.to_string(), other.m_Data.to_string()));
    return this;
}
} // namespace Ban
