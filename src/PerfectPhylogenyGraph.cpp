//
// Created by Pavel Tyletsky on 22/8/20.
//

#include "PerfectPhylogenyGraph.h"
#include "PhylogenyHelpers.h"
#include <fstream>
#include <boost/graph/strong_components.hpp>
#include <thread>

void calculate_part(
        PerfectPhylogenyGraph::matrix_t const &data,
        std::vector<std::vector<bool>> &res,
        size_t from,
        size_t to) {
    for (int i = from; i < to; ++i) {
        std::cout << "c" << i << std::endl;
        for (int j = 0; j < i; ++j) {
            if (!is_perfect_phylogeny_pair(data[i], data[j])) {
                res[i].push_back(j);
            }
        }
    }
}

PerfectPhylogenyGraph::graph_t PerfectPhylogenyGraph::create_prefect_phylogeny_graph(
        matrix_t const &data,
        bool dump = true) {
    graph_t result;
    std::ofstream fout;
    if (dump) fout = std::ofstream("graph.txt");

    std::vector<std::vector<bool>> res;
    res.resize(data.size());

    std::vector<std::thread> threads;
    const size_t total = data.size();
    const size_t count = 4;
    size_t from = 0, to;
    for (int k = 0; k < count; ++k) {
//        (from + to) * (to - from) == total * total / count
//        to2 - from2 == c
//        to2 = c + from2
        to = std::min((size_t) ceil(sqrt(total * total / count + from * from)), total);
        threads.emplace_back([&, from, to]() {
            calculate_part(data, res, from, to);
        });
        from = to;
    }

    for (auto &thread : threads) {
        thread.join();
    }

    for (int i = 0; i < res.size(); ++i) {
        std::cout << "r" << i << std::endl;
        for (int j = 0; j < res[i].size(); ++j) {
            if (dump) fout << j << " ";
            boost::add_edge(i, j, result);
            boost::add_edge(j, i, result);
        }
        if (dump) fout << std::endl;
    }

    std::cout << "graph created" << std::endl;
    return result;
}

int PerfectPhylogenyGraph::get_strong_components(std::vector<int> &c) const {
    c = std::vector<int>(graph.m_vertices.size());
    int components =
            boost::strong_components(
                    graph,
                    make_iterator_property_map(
                            c.begin(), get(boost::vertex_index, graph), c[0]));

    return components;
}

int PerfectPhylogenyGraph::max_component_size() const {
    std::vector<int> c;
    get_strong_components(c);

    std::vector<int> counts(c.size(), 0);
    for (auto el : c) {
        ++counts[el];
    }

    auto it = std::max_element(counts.begin(), counts.end());
    return *it;
}

void PerfectPhylogenyGraph::load(const std::string &filename) {
    if (!graph.m_edges.empty()) {
        throw std::invalid_argument("Graph is already initialized");
    }

    std::ifstream fin(filename);
    for (int i = 0; i < graph.m_vertices.size(); ++i) {
        std::cout << "c" << i << std::endl;
        std::string line;
        std::getline(fin, line);
        std::istringstream myStream(line);
        std::istream_iterator<int> begin(myStream), eof;
        std::vector<int> numbers(begin, eof);

        for (auto n : numbers) {
            boost::add_edge(i, n, graph);
            boost::add_edge(n, i, graph);
        }
    }
}
