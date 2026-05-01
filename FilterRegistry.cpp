#include "FilterRegistry.h"
#include "help.h"

#include <format>
#include <stdexcept>

void FilterRegistry::Register(std::string_view name,
                              std::function<std::unique_ptr<Filter>(const std::vector<std::string>&)> creator) {
    creators[name] = std::move(creator);
}

std::unique_ptr<Filter> FilterRegistry::Create(std::string_view name, const std::vector<std::string>& params) {
    const auto it = creators.find(name);
    if (it == creators.end()) {
        throw std::runtime_error(std::vformat(ErrorUnknownFilter, std::make_format_args(name)));
    }
    return it->second(params);
}

bool FilterRegistry::IsRegistered(std::string_view name) {
    return creators.contains(name);
}
