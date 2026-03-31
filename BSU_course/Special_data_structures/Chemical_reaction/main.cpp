#include <fstream>
#include <string>
#include <map>
#include <cctype>
#include <cstdint>

using namespace std;

struct AtomCount {
public:
    map<string, int32_t> atoms;

    void AddAtom(const string& element, const int32_t count) {
        atoms[element] += count;
    }

    void Merge(const AtomCount& other, const int32_t coefficient) {
        for (const auto& [name, count] : other.atoms) {
            atoms[name] += count * coefficient;
        }
    }
};

static AtomCount ParseFormula(const string& formula) {
    AtomCount result;
    int32_t i = 0;
    const int32_t len = formula.length();

    while (i < len) {
        string element;
        element += formula[i];
        i++;

        if (i < len && (islower(formula[i]) != 0)) {
            element += formula[i];
            i++;
        }

        int32_t count = 1;
        if (i < len && (isdigit(formula[i]) != 0)) {
            count = 0;
            while (i < len && (isdigit(formula[i]) != 0)) {
                count = count * 10 + (formula[i] - '0');
                i++;
            }
        }

        result.AddAtom(element, count);
    }

    return result;
}

static map<string, int32_t> parseExpressionPart(const string& part) {
    map<string, int32_t> result;
    int32_t i = 0;
    const int32_t len = part.length();

    while (i < len) {
        int32_t coefficient = 1;
        if (isdigit(part[i]) != 0) {
            coefficient = 0;
            while (i < len && (isdigit(part[i]) != 0)) {
                coefficient = coefficient * 10 + (part[i] - '0');
                i++;
            }
        }

        string formula;
        while (i < len && part[i] != '+') {
            formula += part[i];
            i++;
        }

        AtomCount const formula_atoms = ParseFormula(formula);
        for (const auto& pair : formula_atoms.atoms) {
            result[pair.first] += pair.second * coefficient;
        }

        if (i < len && part[i] == '+') {
            i++;
        }
    }

    return result;
}

int main() {
    ifstream in("chem.in");
    ofstream out("chem.out");

    string expression;
    getline(in, expression);

    size_t const equal_pos = expression.find('=');
    if (equal_pos == string::npos) {
        out << "NO" << '\n';
        return 0;
    }

    string const left_part = expression.substr(0, equal_pos);
    string const right_part = expression.substr(equal_pos + 1);

    map<string, int32_t> leftAtoms = parseExpressionPart(left_part);
    map<string, int32_t> rightAtoms = parseExpressionPart(right_part);

    if (leftAtoms.size() != rightAtoms.size()) {
        out << "NO" << '\n';
        return 0;
    }

    for (const auto& pair : leftAtoms) {
        if (rightAtoms[pair.first] != pair.second) {
            out << "NO" << '\n';
            return 0;
        }
    }

    out << "YES" << '\n';

    in.close();
    out.close();
    return 0;
}
