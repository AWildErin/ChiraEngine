#pragma once

#include <resource/propertiesResource.h>
#include "shader.h"

namespace chira {
    class material : public propertiesResource {
    public:
        explicit material(const std::string& identifier_);
        void compile(const nlohmann::json& properties) override;
        virtual void use();
        sharedPointer<shader> getShader();
    protected:
        sharedPointer<shader> shaderPtr;
    };
}