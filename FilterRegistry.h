#ifndef CPP_HSE_FILTERREGISTRY_H
#define CPP_HSE_FILTERREGISTRY_H

#include "filters/Filter.h"

#include <functional>
#include <memory>
#include <string_view>
#include <unordered_map>
#include <vector>

class FilterRegistry {
    static inline std::unordered_map<std::string_view,
                                     std::function<std::unique_ptr<Filter>(const std::vector<std::string>&)>>
        creators;

public:
    static void Register(std::string_view name,
                         std::function<std::unique_ptr<Filter>(const std::vector<std::string>&)> creator);
    static std::unique_ptr<Filter> Create(std::string_view name, const std::vector<std::string>& params);
    static bool IsRegistered(std::string_view name);
};

#endif  // CPP_HSE_FILTERREGISTRY_H
