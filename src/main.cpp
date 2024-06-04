
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::vector<std::string>> parse_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("unable to open file: " + filename);
    }

    std::vector<std::string> vcard;
    std::vector<std::vector<std::string>> vcf;
    for (std::string line; getline(file, line);) {
        vcard.push_back(line);
        if (line == "END:VCARD") {
            vcf.push_back(vcard);
            vcard = std::vector<std::string>();
        }
    }

    return vcf;
}

std::vector<std::vector<std::string>> filter_vcf(const std::vector<std::vector<std::string>> &vcf) {
    std::vector<std::vector<std::string>> filtered_vcf;

    for (const auto &vcard: vcf) {
        if(vcard.size() > 6) {
            filtered_vcf.push_back(vcard);
        }
    }

    return filtered_vcf;
}

void save_vcf(const std::string &filename, const std::vector<std::vector<std::string>>& vcf) {
    std::ofstream file(filename);

    for (const auto &vcard : vcf) {
        for(const auto &line: vcard) {
            file << line << "\n";
        }
    }

    file.close();
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        std::cout << "no filename provided\n";
        return 1;
    }
    std::string filename = argv[1];

    auto vcf = parse_file(filename);
    auto filtered_vcf = filter_vcf(vcf);
    save_vcf("filtered.vcf", filtered_vcf);

    return 0;
}
