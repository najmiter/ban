#include "src/ban.hpp"

using namespace Ban;

auto main() -> int {
    auto ban1 = b(1223490284902349032);
    auto ban2 = b(124781947192419038910222479123901831902389012);
    auto ban3 = b(3) - b(1);
    ban2 -= b(1);

    std::println("ban1: {}", ban1);
    std::println("ban2: {}", ban2);
    std::println("ban3: {}", ban3);
}