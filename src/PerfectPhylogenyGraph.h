//
// Created by Pavel Tyletsky on 22/8/20.
//

#pragma once

#include "AlleleColumn.h"

#include <boost/graph/adjacency_list.hpp>


class PerfectPhylogenyGraph {
public:
    using matrix_t = std::vector<AlleleColumn>;
    using graph_t = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS>;

    explicit PerfectPhylogenyGraph(matrix_t const &input, bool dump = true) :
            graph(create_prefect_phylogeny_graph(input, dump)) {}

    explicit PerfectPhylogenyGraph(size_t size) :
            graph(size) {}

    static graph_t create_prefect_phylogeny_graph(
            const matrix_t &data,
            bool dump);

    [[nodiscard]] int get_strong_components(std::vector<int> &c) const;

    void load(std::string const &filename);

    [[nodiscard]] int max_component_size() const;

private:
    graph_t graph;
};
