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
    using data_t = bool;

    explicit AlleleColumn(allele_column_t const &data);

    explicit AlleleColumn(std::vector<data_t> &&data) :
            data(std::move(data)) {}

    [[nodiscard]] size_t size() const;

    data_t operator[](size_t index) const;

    Nucleotide get_consensus() const;

    friend std::ostream& operator<<(std::ostream& os, AlleleColumn const& allele);

private:
    Nucleotide consensus = Nucleotide::Unknown;
    std::vector<data_t> data;
};

inline std::ostream &operator<<(std::ostream &os, AlleleColumn const &allele) {
    for (auto const &nucleotide : allele.data) {
        os << nucleotide;
    }

    return os;
}
