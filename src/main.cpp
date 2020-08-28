#include "AlleleColumn.h"
#include "Sequence.h"
#include "PerfectPhylogenyGraph.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using input_data_t = std::vector<Sequence>;
using data_t = std::vector<AlleleColumn>;

const size_t ROWS_COUNT = 32314;
const size_t COLUMNS_COUNT = 29903;

input_data_t read_fasta(std::string const &filename) {
    std::ifstream fin(filename);
    if (!fin.good()) {
        std::cerr << "Error opening '" << filename << "'. Bailing out." << std::endl;
        exit(1);
    }

    input_data_t data;
    data.reserve(ROWS_COUNT);
    std::string name, base;
    while (fin >> name >> base) {
//        std::cout << name << " : " << base.length() << " : " << base << std::endl;
        data.emplace_back(base, name);
    }

    std::cout << data.size();

    return data;
}

int process_data(int argc, char **argv) {
    if (argc <= 1) {
        std::cerr << "Usage: " << argv[0] << " [infile]" << std::endl;
        return -1;
    }

    auto input_data = read_fasta(argv[1]);
    data_t data;
    data.reserve(COLUMNS_COUNT);
    for (int i = 0; i < input_data[0].size(); ++i) {
        allele_column_t allele;
        for (auto &row : input_data) {
            allele.push_back(row[i]);
        }
        data.emplace_back(std::move(allele));
    }
    input_data.resize(0, Sequence("", ""));

    PerfectPhylogenyGraph graph(data);
    data.resize(0, AlleleColumn(std::vector<Nucleotide>{Nucleotide::A}));
}

int analysis() {
    PerfectPhylogenyGraph res(COLUMNS_COUNT);
    res.load("graph.txt");
    std::vector<int> c;
    int components = res.get_strong_components(c);
    std::cout << components << " strong components" << std::endl;
    std::cout << res.max_component_size() << " max component size" << std::endl;
    return 0;
}

int main(int argc, char **argv) {
    return process_data(argc, argv);
//    return analysis();
}
