#include <cctype>
#include <iostream>
#include <string>
#include <vector>

// Forward declare the function
std::string transformChar(const char inChar);

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

int main(int argc, char* argv[])
{
    // Convert the command-line arguments into a more easily usable form
    const std::vector<std::string> cmdLineArgs{argv, argv + argc};

    // Options that might be set by the command-line arguments
    bool helpRequested{false};
    bool versionRequested{false};
    std::string inputFile{""};
    std::string outputFile{""};

    if (!processCommandLine(cmdLineArgs, helpRequested, versionRequested, inputFile, outputFile)) return 1;

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
        std::cerr << "[warning] input from file ('" << inputFile
                  << "') not implemented yet, using stdin\n";
    }

    // loop over each character from user input
    while (std::cin >> inputChar) {
        inputText += transformChar(inputChar);
    }

    // Print out the transliterated text

    // Warn that output file option not yet implemented
    if (!outputFile.empty()) {
        std::cerr << "[warning] output to file ('" << outputFile
                  << "') not implemented yet, using stdout\n";
    }

    std::cout << inputText << std::endl;

    // No requirement to return from main, but we do so for clarity
    // and for consistency with other functions
    return 0;
}

std::string transformChar(const char inChar) {
    // Uppercase alphabetic characters
    std::string returnText {""};
    if (std::isalpha(inChar)) {
        returnText += std::toupper(inChar);
    }

    // Transliterate digits to English words
    switch (inChar) {
        case '0':
            returnText += "ZERO";
            break;
        case '1':
            returnText += "ONE";
            break;
        case '2':
            returnText += "TWO";
            break;
        case '3':
            returnText += "THREE";
            break;
        case '4':
            returnText += "FOUR";
            break;
        case '5':
            returnText += "FIVE";
            break;
        case '6':
            returnText += "SIX";
            break;
        case '7':
            returnText += "SEVEN";
            break;
        case '8':
            returnText += "EIGHT";
            break;
        case '9':
            returnText += "NINE";
            break;
    }
    return returnText;
    // If the character isn't alphabetic or numeric, DONT add it
    // essentially this does add something but it is just empty so it adds nothing
}