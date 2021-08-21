#pragma once

#include <string>
#include <memory>
#include "abstractResource.h"

class abstractResourceProvider {
public:
    explicit abstractResourceProvider(std::string name) : providerName(std::move(name)) {}
    const std::string& getName() {
        return this->providerName;
    }
    virtual bool hasResource(const std::string& name) = 0;
    virtual void compileResource(const std::string& name, abstractResource* resource) = 0;
private:
    std::string providerName;
};
