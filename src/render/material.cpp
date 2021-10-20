#include "material.h"

#include <fmt/core.h>
#include "../i18n/translationManager.h"
#include "../resource/resourceManager.h"

using namespace chira;

material::material(const std::string& identifier_) : propertiesResource(identifier_) {}

void material::compile(const nlohmann::json& properties) {
    this->shaderPtr = resourceManager::getResource<shader>(properties["dependencies"]["shader"]);
}

void material::use() {
    this->shaderPtr->use();
}

void material::release() const {
    this->shaderPtr->release();
    abstractResource::release();
}

shader* material::getShader() {
    return this->shaderPtr;
}
