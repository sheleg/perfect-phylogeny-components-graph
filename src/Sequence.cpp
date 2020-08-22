//
// Created by Vlada Sheleg on 8/21/20.
//

#include "Sequence.h"

Sequence::Sequence(const std::string &base, const std::string &name) {
    this->name = name;
    for (const auto nucleotide_symbol : base) {
        const auto nucleotide = to_nucleotide_enum(nucleotide_symbol);
        nucleotides.push_back(nucleotide);
    }
}

size_t Sequence::size() const {
    return nucleotides.size();
}

Nucleotide &Sequence::operator[](size_t i) {
    return nucleotides[i];
}
