#include "Utility.hpp"

namespace RE {

bool isAlphabetSymbol(char symbol, std::unordered_set<char> const& alphabet) {
    return alphabet.count(symbol) == 1 || symbol == one;
}

bool isBinaryOperation(char symbol) {
    return static_cast<char>(BinaryOperation::add) == symbol ||
        static_cast<char>(BinaryOperation::multiply) == symbol;
}

bool isUnaryOperation(char symbol) {
    return static_cast<char>(UnaryOperation::star) == symbol;
}

}
