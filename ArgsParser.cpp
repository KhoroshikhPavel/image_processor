#include "ArgsParser.h"
#include "FilterRegistry.h"
#include "help.h"

#include <format>
#include <iostream>
#include <stdexcept>

AppArgs ArgsParser::Parse(int argc, char** argv) {
    if (argc == 1) {
        throw std::runtime_error(ErrorShowHelp.data());
    }

    if (argc < 3) {
        throw std::runtime_error(std::vformat(ErrorNotEnoughArgs, std::make_format_args()));
    }

    AppArgs args;
    args.input_path = argv[1];
    args.output_path = argv[2];

    for (int i = 3; i < argc; ++i) {
        std::string_view cmd = argv[i];

        if (!FilterRegistry::IsRegistered(cmd)) {
            throw std::runtime_error(std::vformat(ErrorUnknownFilter, std::make_format_args(cmd)));
        }

        FilterSpec spec;
        spec.name = cmd;

        int j = i + 1;
        while (j < argc && !FilterRegistry::IsRegistered(argv[j])) {
            spec.params.push_back(argv[j]);
            ++j;
        }

        args.filters.push_back(std::move(spec));
        i = j - 1;
    }

    return args;
}
