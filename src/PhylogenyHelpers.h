//
// Created by Pavel Tyletsky on 22/8/20.
//

#pragma once

#include "AlleleColumn.h"

bool is_perfect_phylogeny_pair(AlleleColumn const &first, AlleleColumn const &second) {
    // if (first.size() != second.size()) {
    //     throw std::invalid_argument("columns must be same size");
    // }

    uint8_t res = 0;
    for (int i = 0; i < first.size(); ++i) {
        res |= 1u << (uint8_t) ((first[i] << 1u) + second[i]);
    }

    return res != 0b1111;
}
