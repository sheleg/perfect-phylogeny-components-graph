#include "AlleleColumn.h"
#include "Sequence.h"
#include "PerfectPhylogenyGraph.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using input_data_t = std::vector<Sequence>;
using data_t = std::vector<AlleleColumn>;

input_data_t read_fasta(std::string const &filename) {
    std::ifstream fin(filename);
    if (!fin.good()) {
        std::cerr << "Error opening '" << filename << "'. Bailing out." << std::endl;
        exit(1);
    }

    input_data_t data;
    std::string name, base;
    while (fin >> name >> base) {
        std::cout << name << " : " << base.length() << " : " << base << std::endl;
        data.emplace_back(base, name);
    }

    return data;
}

int main(int argc, char **argv) {
    if (argc <= 1) {
        std::cerr << "Usage: " << argv[0] << " [infile]" << std::endl;
        return -1;
    }

    auto input_data = read_fasta(argv[1]);
    data_t data;
    for (int i = 0; i < input_data[0].size(); ++i) {
        allele_column_t allele;
        for (auto &row : input_data) {
            allele.push_back(row[i]);
        }
        data.emplace_back(std::move(allele));
    }

    PerfectPhylogenyGraph graph(data);

    return 0;
}
