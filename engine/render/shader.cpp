#include "shader.h"

#include <glm/gtc/type_ptr.hpp>
#include <utility/logger.h>
#include <resource/resource.h>
#include <i18n/translationManager.h>
#include <resource/shaderResource.h>
#include <render/ubo.h>

using namespace chira;

shader::shader(const std::string& identifier_) : propertiesResource(identifier_), handleObject<int>() {}

void shader::compile(const nlohmann::json& properties) {
    this->handle = glCreateProgram();
    auto vert = resource::getResource<shaderResource>(properties["dependencies"]["vertex"], GL_VERTEX_SHADER);
    glAttachShader(this->handle, vert->getHandle());
    auto frag = resource::getResource<shaderResource>(properties["dependencies"]["fragment"], GL_FRAGMENT_SHADER);
    glAttachShader(this->handle, frag->getHandle());
    glLinkProgram(this->handle);
#if DEBUG
    this->checkForCompilationErrors();
#endif
    if (getPropertyOrDefault(properties["properties"], "usesPV", true))
        uboPV::get()->bindToShader(this);
    this->usesModel = getPropertyOrDefault(properties["properties"], "usesM", true);
}

shader::~shader() {
    if (this->handle != -1) glDeleteProgram(this->handle);
}

void shader::use() {
    glUseProgram(this->handle);
}

void shader::checkForCompilationErrors() const {
    int success;
    char infoLog[512];
    glGetProgramiv(this->handle, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(this->handle, 512, nullptr, infoLog);
        logger::log(ERR, "Shader", fmt::format(TR("error.opengl.shader_linking"), infoLog));
    }
}

void shader::setUniform(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(this->handle, name.c_str()), (int) value);
}

void shader::setUniform(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(this->handle, name.c_str()), value);
}

void shader::setUniform(const std::string& name, unsigned int value) const {
    glUniform1ui(glGetUniformLocation(this->handle, name.c_str()), value);
}

void shader::setUniform(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(this->handle, name.c_str()), value);
}

void shader::setUniform(const std::string& name, bool value1, bool value2) const {
    glUniform2i(glGetUniformLocation(this->handle, name.c_str()), (int) value1, (int) value2);
}

void shader::setUniform(const std::string& name, int value1, int value2) const {
    glUniform2i(glGetUniformLocation(this->handle, name.c_str()), value1, value2);
}

void shader::setUniform(const std::string& name, unsigned int value1, unsigned int value2) const {
    glUniform2ui(glGetUniformLocation(this->handle, name.c_str()), value1, value2);
}

void shader::setUniform(const std::string& name, float value1, float value2) const {
    glUniform2f(glGetUniformLocation(this->handle, name.c_str()), value1, value2);
}

void shader::setUniform(const std::string& name, bool value1, bool value2, bool value3) const {
    glUniform3i(glGetUniformLocation(this->handle, name.c_str()), (int) value1, (int) value2, (int) value3);
}

void shader::setUniform(const std::string& name, int value1, int value2, int value3) const {
    glUniform3i(glGetUniformLocation(this->handle, name.c_str()), value1, value2, value3);
}

void shader::setUniform(const std::string& name, unsigned int value1, unsigned int value2, unsigned int value3) const {
    glUniform3ui(glGetUniformLocation(this->handle, name.c_str()), value1, value2, value3);
}

void shader::setUniform(const std::string& name, float value1, float value2, float value3) const {
    glUniform3f(glGetUniformLocation(this->handle, name.c_str()), value1, value2, value3);
}

void shader::setUniform(const std::string& name, bool value1, bool value2, bool value3, bool value4) const {
    glUniform4i(glGetUniformLocation(this->handle, name.c_str()), (int) value1, (int) value2, (int) value3, (int) value4);
}

void shader::setUniform(const std::string& name, int value1, int value2, int value3, int value4) const {
    glUniform4i(glGetUniformLocation(this->handle, name.c_str()), value1, value2, value3, value4);
}

void shader::setUniform(const std::string& name, unsigned int value1, unsigned int value2, unsigned int value3, unsigned int value4) const {
    glUniform4ui(glGetUniformLocation(this->handle, name.c_str()), value1, value2, value3, value4);
}

void shader::setUniform(const std::string& name, float value1, float value2, float value3, float value4) const {
    glUniform4f(glGetUniformLocation(this->handle, name.c_str()), value1, value2, value3, value4);
}

void shader::setUniform(const std::string& name, const glm::mat4& value) const {
    glUniformMatrix4fv(glGetUniformLocation(this->handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void shader::setUniform(const std::string& name, glm::mat4* value) const {
    glUniformMatrix4fv(glGetUniformLocation(this->handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(*value));
}