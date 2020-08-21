#include <iostream>
#include <fstream>
#include <vector>
#include <map>

enum class Nucleotide {
    A,
    C,
    G,
    T,
    Unknown,
};

using nucleotide_counter_t = std::map<Nucleotide, int>;

// TODO: replace with bool!
using allele_column_t = std::vector<Nucleotide>;

class Sequence;

class AlleleColumn;

using input_data_t = std::vector<Sequence>;
using data_t = std::vector<AlleleColumn>;

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

inline std::ostream &operator<<(std::ostream &os, Nucleotide const &nucleotide) {
    os << from_nucleotide_enum(nucleotide);
    return os;
}

class Sequence {
public:
    explicit Sequence(std::string const &base, std::string const &name) {
        this->name = name;
        for (const auto nucleotide_symbol : base) {
            const auto nucleotide = to_nucleotide_enum(nucleotide_symbol);
            nucleotides.push_back(nucleotide);
        }
    }

    [[nodiscard]] size_t size() const {
        return nucleotides.size();
    }

    Nucleotide &operator[](size_t i) {
        return nucleotides[i];
    }

private:
    std::vector<Nucleotide> nucleotides;
    std::string name;
};

class AlleleColumn {
public:
    explicit AlleleColumn(allele_column_t &&data) {
        this->data = std::move(data);
        consensus = find_normal();
        replace_unknown();
    }

    [[nodiscard]] Nucleotide find_normal() const {
        // TODO: possibly do not count N
        nucleotide_counter_t nucleotide_counter{};
        for (auto nucleotide : data) {
            ++nucleotide_counter[nucleotide];
        }
        return std::max_element(
                nucleotide_counter.begin(),
                nucleotide_counter.end(),
                [](auto a, auto b) { return a.second < b.second; })->first;
    }

    void replace_unknown() {
        std::replace_if(
                data.begin(),
                data.end(),
                [](auto n) { return n == Nucleotide::Unknown; },
                consensus);
    }

private:
    allele_column_t data;
    Nucleotide consensus;

    friend void print_allele_column(const AlleleColumn &column);
};

void print_allele_column(const AlleleColumn &column) {
//    skip alleles without mutations
//    if (std::find_if_not(
//            column.data.begin(),
//            column.data.end(),
//            [&column](auto n) { return n == column.consensus; }) == column.data.end()) {
//        return;
//    }
    for (auto const &nucleotide : column.data) {
        std::cout << nucleotide;
    }
    std::cout << "\t" << column.consensus << std::endl;
}

void print_data(data_t const &data) {
    for (auto const &allele_column : data) {
        print_allele_column(allele_column);
//        std::cout << std::endl;
    }
}

input_data_t read_fasta(std::string const &filename) {
    std::ifstream fin(filename);
    if (!fin.good()) {
        std::cerr << "Error opening '" << filename << "'. Bailing out." << std::endl;
        exit(1);
    }

    input_data_t data;
    std::string name, base;
    while (fin >> name >> base) {
//        std::cout << name << " : " << content.length() << " : " << content << std::endl;
        data.emplace_back(base, name);
    }

    return data;
}

int main(int argc, char **argv) {
    if (argc <= 1) {
        std::cerr << "Usage: " << argv[0] << " [infile]" << std::endl;
        return -1;
    }

    auto input_data = read_fasta(argv[1]);
    data_t data;
    for (int i = 0; i < input_data[0].size(); ++i) {
        allele_column_t ac;
        for (auto &row : input_data) {
            ac.push_back(row[i]);
        }
        data.emplace_back(std::move(ac));
    }
    print_data(data);

    return 0;
}

//    TODO: convert to unittests!
//    Sequence s("GAAAA", "");
//    allele_column_t ac;
//    for (int i = 0; i < 5; ++i) {
//        ac.push_back(s[i]);
//    }
//    AlleleColumn a(std::move(ac));
//    std::cout << a.find_normal();