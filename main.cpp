#include <iostream>
#include <fstream>

#include <vector>

enum Nucleotide
{
    A,
    C,
    G,
    T,
    Undefined,
    Count
};

Nucleotide to_nucleotide_enum(char const letter)
{
    switch (letter)
    {
        case 'A':
            return Nucleotide::A;
        case 'C':
            return Nucleotide::C;
        case 'G':
            return Nucleotide::G;
        case 'T':
            return Nucleotide::T;
        case 'N':
            return Nucleotide::Undefined;
        default:
            return Nucleotide::Count;
    }
}

char from_nucleotide_enum(Nucleotide const& nucleotide)
{
    switch (nucleotide)
    {
        case Nucleotide::A:
            return 'A';
        case Nucleotide::C:
            return 'C';
        case Nucleotide::G:
            return 'G';
        case Nucleotide::T:
            return 'T';
        case Nucleotide::Undefined:
            return 'N';
        default:
            return ' ';
    }
}

inline std::ostream& operator << (std::ostream& os, Nucleotide const& nucleotide)
{
    os << from_nucleotide_enum(nucleotide);
    return os;
}

class Sequence
{
public:
    explicit Sequence(std::string const& base)
    {
        nucleotide_counter.resize(Nucleotide::Count);
        for (auto const& nucleotide : base)
        {
            ++nucleotide_counter[to_nucleotide_enum(nucleotide)];
        }
    }

    [[nodiscard]] std::vector<int> get_statistics() const
    {
        return nucleotide_counter;
    }

private:
    std::vector<int> nucleotide_counter;
};

void preprocess_fastafile(std::string const& filename)
{
    std::ifstream fin(filename);
    if (!fin.good())
    {
        std::cerr << "Error opening '" << filename << "'. Bailing out." << std::endl;
        exit(1);
    }

    std::string name, content;
    while (fin >> name >> content)
    {
//        std::cout << name << " : " << content.length() << " : " << content << std::endl;

        Sequence seq(content);
        
        auto const stat = seq.get_statistics();
        for (int i = 0; i < stat.size(); ++i)
        {
            std::cout << static_cast<Nucleotide>(i) << " " << stat[i] << " ";
        }
        std::cout << std::endl;

        name.clear();
        content.clear();
    }
}

int main (int argc, char **argv)
{
    if (argc <= 1)
    {
        std::cerr << "Usage: " << argv[0] << " [infile]" << std::endl;
        return -1;
    }

    preprocess_fastafile(argv[1]);

    return 0;
}