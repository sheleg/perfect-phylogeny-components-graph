//
// Created by Pavel Tyletsky on 22/8/20.
//

#pragma once

#include "AlleleColumn.h"

#include <boost/graph/adjacency_list.hpp>


class PerfectPhylogenyGraph {
    using matrix_t = std::vector<AlleleColumn>;
    using graph_t = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS>;

public:
    explicit PerfectPhylogenyGraph(matrix_t const &input) :
            graph(create_prefect_phylogeny_graph(input)) {}

    static graph_t create_prefect_phylogeny_graph(const matrix_t &data);

    int get_strong_components() const;

private:
public:
    virtual ~PerfectPhylogenyGraph();

private:
    graph_t graph;
};
