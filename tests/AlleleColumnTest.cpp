//
// Created by Vlada Sheleg on 8/22/20.
//

#include <catch2/catch.hpp>

#include <sstream>

#include "../src/AlleleColumn.h"

TEST_CASE("Consensus is the most frequently incoming")
{
    allele_column_t data = { Nucleotide::A, Nucleotide::C, Nucleotide::A, Nucleotide::Unknown };
    AlleleColumn column(data);
    REQUIRE(column.get_consensus() == Nucleotide::A);
}

TEST_CASE("Consensus is the most frequently incoming 2")
{
    allele_column_t data = { Nucleotide::A, Nucleotide::G, Nucleotide::G, Nucleotide::G };
    AlleleColumn column(data);
    REQUIRE(column.get_consensus() == Nucleotide::G);
}

TEST_CASE("Consensus is the most frequently incoming 3")
{
    allele_column_t data = { Nucleotide::A, Nucleotide::C, Nucleotide::T, Nucleotide::G };
    AlleleColumn column(data);
    REQUIRE(column.get_consensus() == Nucleotide::A);
}

// will be fixed after TODO src/AlleleColumn.cpp:10
//TEST_CASE("Consensus is the most frequently incoming 4")
//{
//    allele_column_t data = { Nucleotide::A, Nucleotide::Unknown, Nucleotide::Unknown, Nucleotide::Unknown };
//    AlleleColumn column(data);
//    REQUIRE(column.get_consensus() == Nucleotide::A);
//}

TEST_CASE("Nucleotide to 1 and 0 check common case") {

    allele_column_t data = {Nucleotide::A, Nucleotide::C, Nucleotide::A,
                            Nucleotide::Unknown, Nucleotide::T};

    AlleleColumn column(data);

    std::stringstream stream;
    stream << column;

    REQUIRE(stream.str() == "01001");
}

TEST_CASE("Nucleotide to 1 and 0 check unknown case") {
    allele_column_t data = {Nucleotide::Unknown, Nucleotide::Unknown,
                            Nucleotide::Unknown, Nucleotide::Unknown};

    AlleleColumn column(data);

    std::stringstream stream;
    stream << column;

    REQUIRE(stream.str() == "0000");
}
