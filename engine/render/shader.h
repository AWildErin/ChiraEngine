#pragma once

#include <glm/glm.hpp>
#include <resource/propertiesResource.h>
#include <utility/handleObject.h>

namespace chira {
    class shader : public propertiesResource, public handleObject<int> {
    public:
        explicit shader(const std::string& identifier_);
        void compile(const nlohmann::json& properties) override;
        ~shader() override;
        void use();
        void setUniform(const std::string& name, bool value) const;
        void setUniform(const std::string& name, unsigned int value) const;
        void setUniform(const std::string& name, int value) const;
        void setUniform(const std::string& name, float value) const;
        void setUniform(const std::string& name, bool value1, bool value2) const;
        void setUniform(const std::string& name, unsigned int value1, unsigned int value2) const;
        void setUniform(const std::string& name, int value1, int value2) const;
        void setUniform(const std::string& name, float value1, float value2) const;
        void setUniform(const std::string& name, bool value1, bool value2, bool value3) const;
        void setUniform(const std::string& name, unsigned int value1, unsigned int value2, unsigned int value3) const;
        void setUniform(const std::string& name, int value1, int value2, int value3) const;
        void setUniform(const std::string& name, float value1, float value2, float value3) const;
        void setUniform(const std::string& name, bool value1, bool value2, bool value3, bool value4) const;
        void setUniform(const std::string& name, unsigned int value1, unsigned int value2, unsigned int value3, unsigned int value4) const;
        void setUniform(const std::string& name, int value1, int value2, int value3, int value4) const;
        void setUniform(const std::string& name, float value1, float value2, float value3, float value4) const;
        void setUniform(const std::string& name, const glm::mat4& value) const;
        void setUniform(const std::string& name, glm::mat4* value) const;
        [[nodiscard]] bool usesModelMatrix() const {
            return this->usesModel;
        }
    private:
        /// Set when compiling
        bool usesModel = true;
        void checkForCompilationErrors() const;
    };
}