#include "TransformChar.hpp"
#include "ProcessCommandLine.hpp"
#include "RunCaesarCipher.hpp"

#include <fstream>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
    // Convert the command-line arguments into a more easily usable form
    const std::vector<std::string> cmdLineArgs{argv, argv + argc};

    // Options that might be set by the command-line arguments
    bool helpRequested{false};
    bool versionRequested{false};
    unsigned int key{0}; // don't shift at all by default
    std::string mode{"e"}; // set the default mode to encrypt
    std::string inputFile{""};
    std::string outputFile{""};

    if (!processCommandLine(cmdLineArgs, helpRequested, versionRequested, mode, key, inputFile, outputFile)) return 1;

    // Process command line arguments - ignore zeroth element, as we know this
    // to be the program name and don't need to worry about it

    // Handle help, if requested
    if (helpRequested) {
        // Line splitting for readability
        std::cout
            << "Usage: mpags-cipher [-h/--help] [--version] [-i <file>] [-o <file>]\n\n"
            << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
            << "Available options:\n\n"
            << "  -h|--help        Print this help message and exit\n\n"
            << "  --version        Print version information\n\n"
            << "  -i FILE          Read text to be processed from FILE\n"
            << "                   Stdin will be used if not supplied\n\n"
            << "  -o FILE          Write processed text to FILE\n"
            << "                   Stdout will be used if not supplied\n\n"
            << "  --mode MODE      One of 'e' or 'd'. Default is encrypt\n\n"
            << "  -k KEY           Key to shift Caesar cipher. Default is 0\n\n"
            << std::endl;
        // Help requires no further action, so return from main
        // with 0 used to indicate success
        return 0;
    }

    // Handle version, if requested
    // Like help, requires no further action,
    // so return from main with zero to indicate success
    if (versionRequested) {
        std::cout << "0.1.0" << std::endl;
        return 0;
    }

    // Initialise variables
    char inputChar{'x'};
    std::string inputText;

    // Read in user input from stdin/file
    // Warn that input file option not yet implemented
    if (!inputFile.empty()) {
        std::ifstream inFile {inputFile};
        if (!inFile.good()) {
            std::cerr << "[error] failed to open the input file\n";
            return 1;
        }
        while(inFile >> inputChar) {
            inputText += transformChar(inputChar);
        }
    } else {
        // loop over each character from user input
        while (std::cin >> inputChar) {
            inputText += transformChar(inputChar);
        }
    }

    const bool encrypt {(mode == "e" ? true : false)};
    inputText = runCaesarCipher(inputText, key, encrypt);

    // Warn that output file option not yet implemented
    if (!outputFile.empty()) {
        std::ofstream outFile {outputFile};
        if (!outFile.good()) {
            std::cerr << "[error] failed to open output file for writing\n";
            return 1;
        }
        outFile << inputText;
    } else {
        // Print out the transliterated text
        std::cout << inputText << std::endl;
    }

    // No requirement to return from main, but we do so for clarity
    // and for consistency with other functions
    return 0;
}