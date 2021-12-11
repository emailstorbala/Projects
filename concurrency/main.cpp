#include <fstream>
#include <iostream>
#include <memory>
#include <thread>
#include <tuple>
#include <vector>
#include <chrono>
#include <boost/program_options.hpp>
#include "FileDetails.h"
#include "Concurrent.h"

using std::cout;
using std::cerr;
using std::endl;
using std::endl;
using std::string;
using std::tuple;
using std::vector;
using std::ifstream;

namespace chrono = std::chrono;

using boost::program_options::notify;
using boost::program_options::parse_command_line;
using boost::program_options::store;
using boost::program_options::variables_map;
using boost::program_options::options_description;
using boost::program_options::value;
using boost::program_options::error;

tuple<string> ParseProgramArguments(const int argc, const char * argv[]) {
    string filename;
    variables_map vm;
    options_description prgDesc{"Usage"};

    try {
        prgDesc.add_options()
            ("help, h", "Help screen")
            ("i", value<string>(&filename)->required(), "Input File");

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

    return make_tuple(filename);
}

int main(int argc, const char * argv[]) {
    auto && [fName] = ParseProgramArguments(argc, argv);

    vector<string> files;
    ifstream fileStream;
    fileStream.open((const char *)fName.c_str(), std::ios::in);

    if (fileStream.is_open()) {
        try {
            string line;
            while (getline(fileStream, line)) {
                files.push_back(std::move(line));
            }
        } catch (const std::runtime_error & err) {
            fileStream.close();
            cout << "Runtime error occured: " << err.what() << endl;
            throw;
        }
        fileStream.close();
    } else {
        string err_msg = "File doesn't exists or permission denied for '" + string(fName) + "'";
        throw std::runtime_error(err_msg);
    }

    auto start = chrono::system_clock::now();
    vector <std::thread> thds;
    std::shared_ptr<Concurrent> concPtr = std::make_shared<Concurrent>();

    for (auto && locFile : files) {
        auto locFn = [&locFile] (std::shared_ptr<Concurrent> cPtr) {
            FileDetails fileDtls = FileDetails((char *)locFile.c_str());
            fileDtls.CalculateAndUpdateFileDetails(cPtr);
            cPtr->PrintFileDetails(locFile);
        };
        thds.push_back(std::thread(locFn, concPtr));
        //locFn(concPtr); // Sequential execution
    }

    for (auto && thd: thds) {
        thd.join();
    }

    auto end = chrono::system_clock::now();
    auto dur = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << "Time taken: " << float(dur / 1000) << " mu.secs" << endl;

    return 0;
}
