#pragma once

#include "Constants.hpp"

#include <string>
#include <unordered_set>

namespace RE {

class RegularExpression {
public:
    explicit RegularExpression(
        std::string const& rpnString,
        std::unordered_set<char> const& alphabet = defaultAlphabet
    );

    bool acceptsWordWithSuffix(char suffixSymbol, int repeatCount) const;

private:
    bool isCorrect() const;

    std::string _rpnString;
    std::unordered_set<char> _alphabet;
};

}
