//
// Created by Vlada Sheleg on 8/21/20.
//

#pragma once

#include <iostream>

enum class Nucleotide {
    A,
    C,
    G,
    T,
    Unknown,
};

Nucleotide to_nucleotide_enum(char const letter);
char from_nucleotide_enum(Nucleotide const &nucleotide);

inline std::ostream &operator<<(std::ostream &os, Nucleotide const &nucleotide) {
    os << from_nucleotide_enum(nucleotide);
    return os;
}
