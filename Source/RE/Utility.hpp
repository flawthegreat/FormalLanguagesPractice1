#pragma once

#include "Constants.hpp"

#include <unordered_set>

namespace RE {

bool isAlphabetSymbol(char symbol, std::unordered_set<char> const& alphabet = defaultAlphabet);
bool isBinaryOperation(char symbol);
bool isUnaryOperation(char symbol);

}
