#include <iostream>

#include <eyos/eyos.hpp>

int main() {
    const auto value = eyos::calculate_value();
    if (value == 42) {
        std::cout << "We calculated the value correctly\n";
        return 0;
    } else {
        std::cout << "The value was incorrect!\n";
        return 1;
    }
}
