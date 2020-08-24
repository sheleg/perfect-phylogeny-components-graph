//
// Created by Pavel Tyletsky on 22/8/20.
//

#include "PerfectPhylogenyGraph.h"
#include "PhylogenyHelpers.h"
#include <fstream>
#include <boost/graph/strong_components.hpp>

PerfectPhylogenyGraph::graph_t PerfectPhylogenyGraph::create_prefect_phylogeny_graph(
        matrix_t const &data) {
    graph_t res;
    std::ofstream fout("graph.txt");
    for (int i = 0; i < data.size(); ++i) {
        std::cout << "c" << i << std::endl;
        for (int j = 0; j < i; ++j) {
            if (!is_perfect_phylogeny_pair(data[i], data[j])) {
                fout << j << " ";
                boost::add_edge(i, j, res);
                boost::add_edge(j, i, res);
            }
        }
        fout << std::endl;
    }

    std::cout << "graph created" << std::endl;
    return res;
}

int PerfectPhylogenyGraph::get_strong_components() const {
    std::vector<int> c(graph.m_vertices.size());
    int components =
            boost::strong_components(
                    graph,
                    make_iterator_property_map(
                            c.begin(), get(boost::vertex_index, graph), c[0]));

    return components;
}

PerfectPhylogenyGraph::~PerfectPhylogenyGraph() {
    graph.clear();
}
