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
    explicit AlleleColumn(allele_column_t&& data);

    [[nodiscard]] Nucleotide find_normal() const;

    friend std::ostream& operator<<(std::ostream& os, AlleleColumn const& allele);

private:
    void replace_unknown();

private:
    allele_column_t data;
    Nucleotide consensus;
};

inline std::ostream& operator<<(std::ostream& os, AlleleColumn const& allele) {
    for (auto const &nucleotide : allele.data) {
        os << nucleotide;
    }
    os << "\t" << allele.consensus << std::endl;

    return os;
}
