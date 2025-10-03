#include "src/ban.hpp"

using namespace Ban;

auto main() -> int {
    auto ban1 = b(1223490284902349032);
    auto ban2 = b(124781947192419038910222479123901831902389012);
    auto ban3 = ban1 + ban2;
    ban2 += b(1);
    std::println("ban3: {}", ban2);
    // std::println("ban1: {}", ban1);
    // auto thing = std::format("{:b}", std::stoull("123"));
    // std::println("{}", thing);
}