#pragma once

#include <unordered_set>

namespace RE {

std::unordered_set<char> const defaultAlphabet = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
};

constexpr char zero = '0';
constexpr char one = '1';

enum class BinaryOperation: char {
    add = '+',
    multiply = '.'
};

enum class UnaryOperation: char {
    star = '*'
};

}
