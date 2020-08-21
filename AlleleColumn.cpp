//
// Created by Vlada Sheleg on 8/21/20.
//

#include "AlleleColumn.h"

namespace {

Nucleotide find_normal(allele_column_t const& data) {
    // TODO: possibly do not count N
    nucleotide_counter_t nucleotide_counter;
    for (auto const& nucleotide : data) {
        ++nucleotide_counter[nucleotide];
    }

    auto a = std::max_element(
            nucleotide_counter.begin(),
            nucleotide_counter.end(),
            [](auto a, auto b) { return a.second < b.second; })->first;

    return a;
}

std::vector<bool> replace_unknown(allele_column_t const& data, Nucleotide const consensus) {
    std::vector<bool> result;

    std::transform( data.begin(), data.end(),
                    std::back_inserter(result),
                    [&consensus](auto const& nucleotide)
                    {
                        return nucleotide != consensus &&
                               nucleotide != Nucleotide::Unknown;
                    });

    for (int i = 0; i < data.size(); ++i) {
        std::cout << from_nucleotide_enum(data[i]);
    }
    std::cout << "   ";
    for (int i = 0; i < data.size(); ++i) {
        std::cout << result[i];
    }
    std::cout << "   ";
    std::cout << from_nucleotide_enum(consensus);
    std::cout << std::endl;

    return result;
}

}

AlleleColumn::AlleleColumn(allele_column_t&& data) :
    consensus(find_normal(data)),
    data(replace_unknown(data, consensus))
{
}
