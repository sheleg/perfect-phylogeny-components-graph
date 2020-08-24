//
// Created by Vlada Sheleg on 8/21/20.
//

#include "Sequence.h"

Sequence::Sequence(const std::string &base, const std::string &name) {
    this->name = name;

    nucleotides.reserve(base.size());
    try {
        for (const auto nucleotide_symbol : base) {
            const auto nucleotide = to_nucleotide_enum(nucleotide_symbol);
            nucleotides.push_back(nucleotide);
        }
    } catch (std::invalid_argument &e) {
        std::cout << base << std::endl << e.what() << std::endl;
        exit(1);
    }
}

size_t Sequence::size() const {
    return nucleotides.size();
}

Nucleotide &Sequence::operator[](size_t i) {
    return nucleotides[i];
}
