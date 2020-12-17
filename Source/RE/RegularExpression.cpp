#include "RegularExpression.hpp"

#include "Utility.hpp"

#include <exception>
#include <limits>
#include <stack>

namespace RE {

RegularExpression::RegularExpression(
    std::string const& rpnString,
    std::unordered_set<char> const& alphabet
):
    _rpnString(rpnString),
    _alphabet(alphabet)
{
    if (!isCorrect()) {
        throw std::runtime_error("Regular expression is incorrect\n");
    }
}

bool RegularExpression::acceptsWordWithSuffix(char suffixSymbol, int repeatCount) const {
    int infinity = std::numeric_limits<int>::max();
    auto sum = [&](int lhs, int rhs) {
        return lhs == infinity || rhs == infinity ? infinity : lhs + rhs;
    };

    struct REInfo {
        int maxSuffixLength;
        int maxWordLength;
    };
    std::stack<REInfo> reInfo;

    for (auto symbol: _rpnString) {
        if (isBinaryOperation(symbol)) {
            auto rhs = reInfo.top();
            reInfo.pop();
            auto lhs = reInfo.top();
            reInfo.pop();

            if (symbol == static_cast<char>(BinaryOperation::add)) {
                reInfo.push({
                    std::max(lhs.maxSuffixLength, rhs.maxSuffixLength),
                    std::max(lhs.maxWordLength, rhs.maxWordLength)
                });
            } else if (symbol == static_cast<char>(BinaryOperation::multiply)) {
                if (rhs.maxWordLength > -1) {
                    reInfo.push({
                        std::max(rhs.maxSuffixLength, sum(lhs.maxSuffixLength, rhs.maxWordLength)),
                        lhs.maxWordLength > -1 ? sum(lhs.maxWordLength, rhs.maxWordLength) : -1
                    });
                } else {
                    reInfo.push(rhs);
                }
            }
        } else if (isUnaryOperation(symbol)) {
            auto operand = reInfo.top();
            reInfo.pop();

            if (symbol == static_cast<char>(UnaryOperation::star)) {
                reInfo.push(operand.maxWordLength > 0 ? REInfo{infinity, infinity} : operand);
            }
        } else if (isAlphabetSymbol(symbol, _alphabet)) {
            if (symbol == RE::one) {
                reInfo.push({0, 0});
            } else {
                reInfo.push({symbol == suffixSymbol, symbol == suffixSymbol ? 1 : -1});
            }
        }
    }

    return reInfo.top().maxSuffixLength >= repeatCount;
}

bool RegularExpression::isCorrect() const {
    int operandStackSize = 0;

    for (auto symbol: _rpnString) {
        if (isBinaryOperation(symbol)) {
            if (operandStackSize < 2) {
                return false;
            }
            --operandStackSize;
        } else if (isUnaryOperation(symbol)) {
            if (operandStackSize < 1) {
                return false;
            }
        } else if (isAlphabetSymbol(symbol, _alphabet)) {
            ++operandStackSize;
        } else {
            return false;
        }
    }

    return operandStackSize == 1;
}

}
