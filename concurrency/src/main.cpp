#include "Concurrent.h"
#include "DNSDetails.h"
#include <boost/program_options.hpp>
#include <chrono>
#include <fmt/core.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <thread>
#include <tuple>
#include <vector>

using std::ifstream;
using std::string;
using std::tuple;
using std::vector;

namespace chrono = std::chrono;

using boost::program_options::error;
using boost::program_options::notify;
using boost::program_options::options_description;
using boost::program_options::parse_command_line;
using boost::program_options::store;
using boost::program_options::value;
using boost::program_options::variables_map;

tuple<string> ParseProgramArguments(const int argc, const char *argv[]) {
    string filename;
    variables_map vm;
    options_description prgDesc{"Usage"};

    try {
        prgDesc.add_options()("help, h", "Help screen")(
            "i", value<string>(&filename)->required(), "Input File");

        store(parse_command_line(argc, argv, prgDesc), vm);

        if (vm.count("help") || vm.count("h")) {
            std::cout << prgDesc << std::endl;
            exit(0);
        }

        notify(vm);
    } catch (const error &ex) {
        std::cerr << "Exception: '" << ex.what() << std::endl;
        std::cout << prgDesc << std::endl;
        exit(3);
    }

    return make_tuple(filename);
}

int main(int argc, const char *argv[]) {
    auto &&[fName] = ParseProgramArguments(argc, argv);

    vector<string> dnsNames;
    ifstream fileStream;
    fileStream.open((const char *)fName.c_str(), std::ios::in);

    if (fileStream.is_open()) {
        try {
            string line;
            while (getline(fileStream, line)) {
                dnsNames.push_back(std::move(line));
            }
        } catch (const std::runtime_error &err) {
            fileStream.close();
            fmt::print("Runtime error occured: {}\n", err.what());
            throw;
        }
        fileStream.close();
    } else {
        string err_msg;
        fmt::format_to(std::back_inserter(err_msg),
                       "File doesn't exists or permission denied for {}\n",
                       fName);
        throw std::runtime_error(err_msg);
    }

    auto start = chrono::steady_clock::now();
    vector<std::thread> thds;
    std::shared_ptr<Concurrent> concPtr = std::make_shared<Concurrent>();

    for (auto &&dnsName : dnsNames) {
        auto locFn = [&dnsName](std::shared_ptr<Concurrent> cPtr) {
            try {
                DNSDetails dnsDtls = DNSDetails(dnsName);
                dnsDtls.CalculateAndUpdateFileDetails(cPtr);
            } catch (std::runtime_error &excp) {
                fmt::print("Runtime error occured for dnsName '{}': {}\n",
                           dnsName, excp.what());
                return;
            }
        };
        thds.push_back(std::thread(locFn, concPtr));
    }

    for (auto &&thd : thds) {
        thd.join();
    }

    concPtr->PrintSummary();

    auto end = chrono::steady_clock::now();
    auto dur = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    fmt::print("Time taken: {} mu.secs\n", dur / 1000.0);

    return 0;
}
