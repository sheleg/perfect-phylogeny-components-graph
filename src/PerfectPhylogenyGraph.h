//
// Created by Pavel Tyletsky on 22/8/20.
//

#ifndef MATCHING_SEARCH_PERFECTPHYLOGENYGRAPH_H
#define MATCHING_SEARCH_PERFECTPHYLOGENYGRAPH_H

#include "AlleleColumn.h"

class PerfectPhylogenyGraph {
    using matrix_t = std::vector<AlleleColumn>;
    // lower triangle adjacency matrix
    using graph_t = std::vector<std::vector<bool>>;

public:
    explicit PerfectPhylogenyGraph(matrix_t const &input) :
            graph(create_prefect_phylogeny_graph(input)) {}

    static graph_t create_prefect_phylogeny_graph(const matrix_t &data);

private:
    graph_t graph;
};

#endif //MATCHING_SEARCH_PERFECTPHYLOGENYGRAPH_H
