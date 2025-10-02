#include "src/ban.hpp"

using namespace Ban;

auto main() -> int {
    auto ban1 = Bassn(b(1234567890));
    std::println("ban1: {}", ban1);
    // auto thing = std::format("{:b}", std::stoull("123"));
    // std::println("{}", thing);
}