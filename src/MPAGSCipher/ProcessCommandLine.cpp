#include "ProcessCommandLine.hpp"

#include <vector>
#include <iostream>

bool processCommandLine(const std::vector<std::string>& args, bool& helpRequested, bool& versionRequested, std::string& inputFile, std::string& outputFile) {
    const std::size_t nArgs{args.size()};
    for (std::size_t i{1}; i < nArgs; ++i) {
        if (args[i] == "-h" || args[i] == "--help") {
            helpRequested = true;
        } else if (args[i] == "--version") {
            versionRequested = true;
        } else if (args[i] == "-i") {
            // Handle input file option
            // Next element is filename unless "-i" is the last argument
            if (i == nArgs - 1) {
                std::cerr << "[error] -i requires a filename argument" << std::endl;
                return false;
            } else {
                // Got filename, so assign value and advance past it
                inputFile = args[i + 1];
                ++i;
            }
        } else if (args[i] == "-o") {
            // Handle output file option
            // Next element is filename unless "-o" is the last argument
            if (i == nArgs - 1) {
                std::cerr << "[error] -o requires a filename argument" << std::endl;
                return false;
            } else {
                // Got filename, so assign value and advance past it
                outputFile = args[i + 1];
                ++i;
            }
        } else {
            // Have an unknown flag to output error message and return non-zero
            // exit status to indicate failure
            std::cerr << "[error] unknown argument '" << args[i] << "'\n";
            return false;
        }
    }
    return true;
}