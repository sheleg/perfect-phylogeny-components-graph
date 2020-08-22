//
// Created by Vlada Sheleg on 8/21/20.
//

#pragma once

#include "Nucleotide.h"

#include <iostream>
#include <map>
#include <vector>

using allele_column_t = std::vector<Nucleotide>;
using nucleotide_counter_t = std::map<Nucleotide, int>;

class AlleleColumn {
public:
    explicit AlleleColumn(allele_column_t const& data);

    Nucleotide get_consensus() const;

    friend std::ostream& operator<<(std::ostream& os, AlleleColumn const& allele);
private:
    Nucleotide consensus;

    std::vector<bool> data;
};

inline std::ostream& operator<<(std::ostream& os, AlleleColumn const& allele) {
    for (auto const &nucleotide : allele.data) {
        os << nucleotide;
    }

    return os;
}
