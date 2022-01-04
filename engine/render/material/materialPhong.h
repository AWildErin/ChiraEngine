#pragma once

#include "materialUntextured.h"
#include "../texture.h"

namespace chira {
    class MaterialPhong : public MaterialUntextured {
    public:
        explicit MaterialPhong(const std::string& identifier_) : MaterialUntextured(identifier_) {}
        void compile(const nlohmann::json& properties) override;
        void use() const override;
        [[nodiscard]] SharedPointer<Texture> getTextureDiffuse() const;
        [[nodiscard]] SharedPointer<Texture> getTextureSpecular() const;
        void setShininess(float shininess);
        void setLambertFactor(float lambertFactor);
    protected:
        SharedPointer<Texture> diffuse;
        SharedPointer<Texture> specular;
    private:
        REGISTER_MATERIAL_TYPE(MaterialPhong);
    };
}
