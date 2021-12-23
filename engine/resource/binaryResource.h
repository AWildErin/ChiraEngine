#pragma once

#include "resource.h"

namespace chira {
    class binaryResource : public resource {
    public:
        explicit binaryResource(const std::string& identifier_) : resource(identifier_) {}
        void compile(const unsigned char buffer[], std::size_t bufferLength) override;
        ~binaryResource() override;
        [[nodiscard]] const unsigned char* getBuffer() const noexcept;
        [[nodiscard]] std::size_t getBufferLength() const noexcept;
    private:
        unsigned char* buffer_ = nullptr;
        std::size_t bufferLength_ = 0;
    };
}