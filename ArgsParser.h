#ifndef CPP_HSE_ARGSPARSER_H
#define CPP_HSE_ARGSPARSER_H

#include "FilterRegistry.h"

#include <string>
#include <string_view>
#include <vector>

struct FilterSpec {
    std::string name;
    std::vector<std::string> params;
};

struct AppArgs {
    std::string input_path;
    std::string output_path;
    std::vector<FilterSpec> filters;
};

class ArgsParser {
public:
    static AppArgs Parse(int argc, char** argv);
};

#endif  // CPP_HSE_ARGSPARSER_H
