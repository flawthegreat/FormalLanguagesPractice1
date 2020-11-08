#include <string>
#include <iostream>

#include <RE/RegularExpression.hpp>

int main() {
    std::string rpnString;
    std::cout << "Regular expression in reverse polish notation: ";
    std::cin >> rpnString;

    try {
        RE::RegularExpression re(rpnString, {'a', 'b', 'c'});

        char suffixSymbol = 0;
        int repeatCount = 0;
        std::cout << "Suffix symbol: ";
        std::cin >> suffixSymbol;
        std::cout << "Symbol repeat count: ";
        std::cin >> repeatCount;

        bool result = re.acceptsWordWithSuffix(suffixSymbol, repeatCount);
        std::cout << (result ? "YES" : "NO") << std::endl;
    } catch (...) {
        std::cout << "ERROR" << std::endl;
    }

    return 0;
}
