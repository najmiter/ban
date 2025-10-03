#include "src/ban.hpp"

using namespace Ban;

auto main() -> int {
    auto ban1 = bt(5000, 124781947192419038910222479123901831902389012);
    auto ban2 = b(124781947192419038910222479123901831902389012);
    auto ban3 = Bassn<512>(ban1.c_MaxValue) +
                Bassn<512>("124781947192419038910222479123901831902389012");

    // std::println("max value: {}", ban1.c_MaxValue);
    std::println("ban1: {}", ban1);
    // std::println("ban2: {}", ban2);
    // std::println("ban3: {}", ban3);
}