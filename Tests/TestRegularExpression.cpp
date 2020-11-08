#include <gtest/gtest.h>
#include <unordered_set>
#include <vector>
#include <tuple>

#include <RE/RegularExpression.hpp>

TEST(RegularExpression, CreationAndCorrectness) {
    std::vector<std::tuple<std::string, std::unordered_set<char>, bool>> testCases = {
        {"ab+c.aba.*.bac.+.+*", {'a', 'b', 'c'}, true},
        {"ab+c.aba.*.bac.+.+*", {'a', 'b'}, false},
        {"ab+c.aba.*.bac..+*", {'a', 'b', 'c'}, false},
        {"acb..bab.c.*.ab.ba.+.+*a.", {'a', 'b', 'c'}, true},
        {"a", {'a'}, true},
        {"aa.", {'a'}, true},
        {"aa+", {'a'}, true},
        {"a*", {'a'}, true},
        {"aa*", {'a'}, false},
        {"aa++", {'a', 'b'}, false},
        {"aa+b+", {'a', 'b'}, true},
        {"aa.a.a.a.a.b.a.b.b.a.b.a.b.a.b.a.", {'a', 'b'}, true},
        {"*", {'a'}, false}
    };

    for (auto const& [rpnString, alphabet, result]: testCases) {
        if (result) {
            EXPECT_NO_THROW(RE::RegularExpression(rpnString, alphabet));
        } else {
            EXPECT_THROW(RE::RegularExpression(rpnString, alphabet), std::runtime_error);
        }
    }
}

TEST(RegularExpression, AcceptsWordWithSuffix) {
    std::vector<std::tuple<std::string, std::unordered_set<char>, char, int, bool>> testCases = {
        {"ab+c.aba.*.bac.+.+*", {'a', 'b', 'c'}, 'a', 1, false},
        {"ab+c.aba.*.bac.+.+*", {'a', 'b', 'c'}, 'c', 1, true},
        {"aa.", {'a'}, 'a', 0, true},
        {"aa.", {'a'}, 'a', 1, true},
        {"aa.", {'a'}, 'a', 2, true},
        {"aa.", {'a'}, 'a', 3, false},
        {"aa.", {'a'}, 'b', 0, true},
        {"aa.", {'a'}, 'b', 1, false},
        {"a*", {'a'}, 'a', 1'000'000, true},
        {"ca*b+.b+", {'a', 'b', 'c'}, 'a', 1000, true},
        {"ca*b+.b+", {'a', 'b', 'c'}, 'b', 1, true},
        {"cc*.c.", {'c'}, 'c', 100, true},
        {"a*b.", {'a', 'b'}, 'a', 100, false},
        {"ba*.", {'a', 'b'}, 'a', 100, true},
        {"a1.", {'a'}, 'a', 1, true}
    };

    for (auto const& [rpnString, alphabet, suffixSymbol, repeatCount, result]: testCases) {
        RE::RegularExpression re(rpnString, alphabet);
        EXPECT_EQ(re.acceptsWordWithSuffix(suffixSymbol, repeatCount), result);
    }
}
