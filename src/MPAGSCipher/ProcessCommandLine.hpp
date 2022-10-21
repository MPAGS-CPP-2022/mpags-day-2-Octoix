#ifndef MPAGS_PROCESSCOMMANDLINE_HPP
#define MPAGS_PROCESSCOMMANDLINE_HPP

#include <iostream>
#include <vector>

bool processCommandLine(
    const std::vector<std::string>& args, 
    bool& helpRequested, 
    bool& versionRequested,
    std::string& mode,
    unsigned int& key,
    std::string& inputFile,
    std::string& outputFile
);

#endif