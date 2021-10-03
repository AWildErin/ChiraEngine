#pragma once

#include <memory>
#include <string>
#include "../resource/propertiesResource.h"
#include "../loader/abstractImage.h"

namespace chira {
    class texture : public abstractResource {
    public:
        explicit texture(const std::string& identifier_, bool vFlip_ = true);
        void compile(unsigned char* buffer, std::size_t bufferLen) override;
        virtual void use() = 0;
        void setTextureUnit(int textureUnit);
        [[nodiscard]] int getTextureUnit() const;
        [[nodiscard]] unsigned int getHandle() const;
    protected:
        unsigned int handle = 0;
        int activeTextureUnit = -1;
        std::unique_ptr<abstractImage> file = nullptr;
        int width = -1;
        int height = -1;
        int bitDepth = -1;
        bool vFlip = true;
    };
}
