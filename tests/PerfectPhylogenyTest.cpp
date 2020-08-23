//
// Created by Pavel Tyletsky on 22/8/20.
//

#include <catch2/catch.hpp>
#include "../src/PhylogenyHelpers.h"
#include "../src/Sequence.h"

TEST_CASE("is_perfect_phylogeny_pair") {
    REQUIRE(is_perfect_phylogeny_pair(
            AlleleColumn({1, 1, 1, 1}),
            AlleleColumn({1, 1, 1, 1})));
    REQUIRE(is_perfect_phylogeny_pair(
            AlleleColumn({0, 0, 1, 0}),
            AlleleColumn({0, 0, 1, 0})));
    REQUIRE(is_perfect_phylogeny_pair(
            AlleleColumn({0, 1, 1, 0}),
            AlleleColumn({0, 1, 1, 0})));
    REQUIRE(is_perfect_phylogeny_pair(
            AlleleColumn({1, 1, 0, 0}),
            AlleleColumn({0, 0, 1, 1})));
    REQUIRE(is_perfect_phylogeny_pair(
            AlleleColumn({0, 0, 1, 1}),
            AlleleColumn({0, 1, 0, 0})));
}

TEST_CASE("is_perfect_phylogeny_pair negative") {
    REQUIRE_FALSE(is_perfect_phylogeny_pair(
            AlleleColumn({0, 1, 0, 1}),
            AlleleColumn({0, 0, 1, 1})
    ));
}
