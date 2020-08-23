//
// Created by Pavel Tyletsky on 22/8/20.
//

#include "PerfectPhylogenyGraph.h"
#include "PhylogenyHelpers.h"

PerfectPhylogenyGraph::graph_t PerfectPhylogenyGraph::create_prefect_phylogeny_graph(
        matrix_t const &data) {
    graph_t res(data.size());
    for (int i = 0; i < data.size(); ++i) {
        res[i].resize(i);
        for (int j = 0; j < i; ++j) {
            res[i][j] = is_perfect_phylogeny_pair(data[i], data[j]);
        }
    }

    return res;
}
