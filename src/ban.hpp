#pragma once

namespace Ban {
#define _BAN_PREFIX(x) #x
// Takes a number like thing and put double quotes around it
#define b(x) _BAN_PREFIX(x)

class Ban {
  public:
    Ban() = default;
    Ban(std::string_view input);
    ~Ban() = default;

  private:
    std::bitset<256> m_Data;
};
} // namespace Ban