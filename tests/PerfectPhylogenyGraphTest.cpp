//
// Created by Pavel Tyletsky on 22/8/20.
//

#include <catch2/catch.hpp>
#include <PerfectPhylogenyGraph.h>

TEST_CASE("Simple graph") {
    AlleleColumn ac({1});
    PerfectPhylogenyGraph g(
            PerfectPhylogenyGraph::matrix_t{ac});
    std::vector<int> c;
    REQUIRE(g.get_strong_components(c) == 1);
}
