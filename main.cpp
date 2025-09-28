#include "src/ban.hpp"
#include <iostream>

using namespace Ban;

auto main() -> int {
    Bassn ban1(b(123));
    std::println("Input '123': {}", ban1);
}