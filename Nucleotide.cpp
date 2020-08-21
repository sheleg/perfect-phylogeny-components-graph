//
// Created by Vlada Sheleg on 8/21/20.
//

#include "Nucleotide.h"

#include <vector>

Nucleotide to_nucleotide_enum(char const letter) {
    switch (letter) {
        case 'A':
            return Nucleotide::A;
        case 'C':
            return Nucleotide::C;
        case 'G':
            return Nucleotide::G;
        case 'T':
            return Nucleotide::T;
        case 'N':
        case '?':
            return Nucleotide::Unknown;
        default:
            throw std::invalid_argument("unknown nucleotide");
    }
}

char from_nucleotide_enum(Nucleotide const &nucleotide) {
    switch (nucleotide) {
        case Nucleotide::A:
            return 'A';
        case Nucleotide::C:
            return 'C';
        case Nucleotide::G:
            return 'G';
        case Nucleotide::T:
            return 'T';
        case Nucleotide::Unknown:
            return 'N';
        default:
            throw std::invalid_argument("unknown nucleotide");
    }
}
