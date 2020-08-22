//
// Created by Vlada Sheleg on 8/21/20.
//

#pragma once

#include "Nucleotide.h"

#include <iostream>
#include <vector>

class Sequence {
public:
    explicit Sequence(std::string const &base, std::string const &name);

    [[nodiscard]] size_t size() const;
    Nucleotide &operator[](size_t i);

private:
    std::vector<Nucleotide> nucleotides;
    std::string name;
};
