#include <gtest/gtest.h>
#include <unordered_set>
#include <vector>
#include <utility>

#include <RE/Utility.hpp>

TEST(Utility, IsAlphabetSymbol) {
    for (auto symbol: RE::defaultAlphabet) {
        EXPECT_TRUE(RE::isAlphabetSymbol(symbol));
    }

    std::vector<std::pair<char, bool>> testCases = {
        {RE::one, true},
        {'A', false},
        {'+', false},
        {'\0', false}
    };

    for (auto [symbol, isAlphabetSymbol]: testCases) {
        EXPECT_EQ(RE::isAlphabetSymbol(symbol), isAlphabetSymbol);
    }

    std::unordered_set<char> customAlphabet = {'a', 'b', '&'};
    testCases = {
        {RE::one, true},
        {'a', true},
        {'&', true},
        {'-', false}
    };

    for (auto [symbol, isAlphabetSymbol]: testCases) {
        EXPECT_EQ(RE::isAlphabetSymbol(symbol, customAlphabet), isAlphabetSymbol);
    }
}

TEST(Utility, IsBinaryOperation) {
    std::vector<std::pair<char, bool>> testCases = {
        {'+', true},
        {'.', true},
        {'*', false},
        {'-', false},
        {'/', false},
        {'%', false}
    };

    for (auto [symbol, isBinaryOperation]: testCases) {
        EXPECT_EQ(RE::isBinaryOperation(symbol), isBinaryOperation);
    }
}

TEST(Utility, IsUnaryOperation) {
    std::vector<std::pair<char, bool>> testCases = {
        {'+', false},
        {'.', false},
        {'*', true},
        {'-', false},
        {'/', false},
        {'%', false}
    };

    for (auto [symbol, isUnaryOperation]: testCases) {
        EXPECT_EQ(RE::isUnaryOperation(symbol), isUnaryOperation);
    }
}
