//
// Created by Vlada Sheleg on 8/21/20.
//

#include "AlleleColumn.h"

AlleleColumn::AlleleColumn(allele_column_t&& data) {
    this->data = std::move(data);
    consensus = find_normal();
    replace_unknown();
}

[[nodiscard]] Nucleotide AlleleColumn::find_normal() const {
    // TODO: possibly do not count N
    nucleotide_counter_t nucleotide_counter;
    for (auto nucleotide : data) {
        ++nucleotide_counter[nucleotide];
    }
    return std::max_element(
            nucleotide_counter.begin(),
            nucleotide_counter.end(),
            [](auto a, auto b) { return a.second < b.second; })->first;
}

void AlleleColumn::replace_unknown() {
    std::replace_if(
            data.begin(),
            data.end(),
            [](auto n) { return n == Nucleotide::Unknown; },
            consensus);
}
