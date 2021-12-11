#include "getcombinations.hpp"

using fmt::format;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::map;
using std::ifstream;
using std::tuple;

using boost::program_options::notify;
using boost::program_options::parse_command_line;
using boost::program_options::store;
using boost::program_options::variables_map;
using boost::program_options::options_description;
using boost::program_options::value;
using boost::program_options::error;

tuple<string, int> ParseProgramArguments(const int argc, const char * argv[]) {
    string inputStr;
    int rvalue;
    variables_map vm;
    options_description prgDesc{"Usage"};

    try {
        prgDesc.add_options()
            ("help, h", "Help screen")
            ("input", value<string>(&inputStr)->required(), "Input String")
            ("r", value<int>(&rvalue)->required(), "rvalue in nCr. Positive value");

        store(parse_command_line(argc, argv, prgDesc), vm);

        if (vm.count("help") || vm.count("h")) {
            cout << prgDesc << endl;
            exit(0);
        }

        notify(vm);
    } catch (const error &ex) {
        cerr << "Exception: '" << ex.what() << endl;
        cout << prgDesc << endl;
        exit(3);
    }

    if (rvalue < 1 || rvalue > (int) inputStr.length()) {
        cout << format("Invalid rvalue '{}' provided!", rvalue) << endl;
        exit(2);
    }

    return make_tuple(inputStr, rvalue);
}

template <typename T>
T Combinations::CreateCombinations() {
    if ((int)combs[0].length() == this->totalLimit)  return combs;
    if ((int)this->inp.length() == this->totalLimit)  return {this->inp};

    vector <string> tmpList;
    for (size_t rep = 0; rep < this->inp.length(); rep++) {
        for (size_t pos = 0; pos < this->combs.size(); pos++) {
            string loc = format("{}{}", this->combs[pos], this->inp[rep]);
            tmpList.push_back(loc);
        }
    }

    if ((int)tmpList[0].length() < this->totalLimit) {
        this->SetInitialCombs(tmpList);
        return this->CreateCombinations<vector<string>>();
    } else {
        vector <string> uniqCombs;
        for (auto & comb : tmpList) {
            if (!this->IsDuplicate(uniqCombs, comb)) {
                uniqCombs.push_back(comb);
            }
        }
        return uniqCombs;
    }
}

bool IsCharacterRepeats(string temp) {
    for (char & ch : temp) {
        int rep = 0;
        for (size_t pos = 0; pos < temp.length(); pos++) {
            if (temp[pos] == ch) {
                rep++;
            }
        }

        if (rep > 1) return true;
    }

    return false;
}

Combinations::Combinations(string _inp, int _tot) {
    this->inp = _inp;
    this->totalLimit = _tot;

    for (char & ch : inp) {
        string loc = format("{}", ch);
        this->combs.push_back(loc);
    }
}

bool Combinations::IsDuplicate(vector <string> itemList, string item) {
    if (IsCharacterRepeats(item)) return true;

    for (auto && locItem : itemList) {
        int commChars = 0;
        for (auto && ch : item) {
            if (locItem.find(ch) != string::npos) {
                commChars++;
            }
        }

        if (commChars == (int) item.length()) return true;
    }

    return false;
}

int main(int argc, const char * args[]) {
    auto && [inp, rvalue] = ParseProgramArguments(argc, args);

    Combinations combinations(inp, rvalue);
    auto totCombs = combinations.CreateCombinations<vector<string>>();

    for (auto comb : totCombs) {
        cout << comb << endl;
    }
    return EXIT_SUCCESS;
}
