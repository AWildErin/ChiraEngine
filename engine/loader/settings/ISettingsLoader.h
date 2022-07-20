#pragma once

#include <string>
#include <string_view>

namespace chira {

class ISettingsLoader {
public:
    explicit ISettingsLoader(std::string_view path);
    virtual ~ISettingsLoader() = default;

    virtual void addCategory(const std::string& category) = 0;

    virtual void getValue(const std::string& category, const std::string& name, int* value) const = 0;
    virtual void getValue(const std::string& category, const std::string& name, double* value) const = 0;
    virtual void getValue(const std::string& category, const std::string& name, std::string* value) const = 0;
    virtual void getValue(const std::string& category, const std::string& name, bool* value) const = 0;

    virtual void setValue(const std::string& category, const std::string& name, int value, bool overwrite, bool save) = 0;
    virtual void setValue(const std::string& category, const std::string& name, double value, bool overwrite, bool save) = 0;
    virtual void setValue(const std::string& category, const std::string& name, const std::string& value, bool overwrite, bool save) = 0;
    virtual void setValue(const std::string& category, const std::string& name, bool value, bool overwrite, bool save) = 0;

    [[nodiscard]] virtual bool hasCategory(const std::string& category) const = 0;
    [[nodiscard]] virtual bool hasValue(const std::string& category, const std::string& name) const = 0;
    virtual void load() = 0;
    virtual void save() = 0;

    void setFilePath(std::string_view path);
    [[nodiscard]] std::string_view getFilePath() const {
        return this->filepath;
    }
private:
    std::string filepath;
};

} // namespace chira