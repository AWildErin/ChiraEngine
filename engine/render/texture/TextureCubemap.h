#pragma once

#include "ITexture.h"

namespace chira {

class TextureCubemap final : public ITexture {
public:
    explicit TextureCubemap(std::string identifier_);
    void compile(const nlohmann::json& properties) override;
    void use() override;
protected:
    std::string imageFD{"file://textures/missing.png"};
    std::string imageBK{"file://textures/missing.png"};
    std::string imageUP{"file://textures/missing.png"};
    std::string imageDN{"file://textures/missing.png"};
    std::string imageLT{"file://textures/missing.png"};
    std::string imageRT{"file://textures/missing.png"};
    bool verticalFlipFD = false;
    bool verticalFlipBK = false;
    bool verticalFlipUP = false;
    bool verticalFlipDN = false;
    bool verticalFlipLT = false;
    bool verticalFlipRT = false;
    int formatFD = GL_RGBA;
    int formatBK = GL_RGBA;
    int formatUP = GL_RGBA;
    int formatDN = GL_RGBA;
    int formatLT = GL_RGBA;
    int formatRT = GL_RGBA;
    std::string formatOverrideFD{"NONE"};
    std::string formatOverrideBK{"NONE"};
    std::string formatOverrideUP{"NONE"};
    std::string formatOverrideDN{"NONE"};
    std::string formatOverrideLT{"NONE"};
    std::string formatOverrideRT{"NONE"};
    bool mipmaps = true;
    int filterMode = GL_LINEAR;
    std::string filterModeStr{"LINEAR"};
    int wrapModeS = GL_REPEAT;
    std::string wrapModeSStr{"REPEAT"};
    int wrapModeT = GL_REPEAT;
    std::string wrapModeTStr{"REPEAT"};
    int wrapModeR = GL_REPEAT;
    std::string wrapModeRStr{"REPEAT"};
private:
    void setFilterMode(std::string filterModeStr_);
    void setWrapModeS(std::string wrapModeSStr_);
    void setWrapModeT(std::string wrapModeTStr_);
    void setWrapModeR(std::string wrapModeRStr_);
public:
    CHIRA_PROPS(
            CHIRA_PROP(TextureCubemap, imageFD),
            CHIRA_PROP(TextureCubemap, imageBK),
            CHIRA_PROP(TextureCubemap, imageUP),
            CHIRA_PROP(TextureCubemap, imageDN),
            CHIRA_PROP(TextureCubemap, imageLT),
            CHIRA_PROP(TextureCubemap, imageRT),
            CHIRA_PROP(TextureCubemap, verticalFlipFD),
            CHIRA_PROP(TextureCubemap, verticalFlipBK),
            CHIRA_PROP(TextureCubemap, verticalFlipUP),
            CHIRA_PROP(TextureCubemap, verticalFlipDN),
            CHIRA_PROP(TextureCubemap, verticalFlipLT),
            CHIRA_PROP(TextureCubemap, verticalFlipRT),
            CHIRA_PROP(TextureCubemap, formatOverrideFD),
            CHIRA_PROP(TextureCubemap, formatOverrideBK),
            CHIRA_PROP(TextureCubemap, formatOverrideUP),
            CHIRA_PROP(TextureCubemap, formatOverrideDN),
            CHIRA_PROP(TextureCubemap, formatOverrideLT),
            CHIRA_PROP(TextureCubemap, formatOverrideRT),
            CHIRA_PROP(TextureCubemap, mipmaps),
            CHIRA_PROP_NAMED_SET(TextureCubemap, filterModeStr, filterMode, setFilterMode),
            CHIRA_PROP_NAMED_SET(TextureCubemap, wrapModeSStr, wrapModeS, setWrapModeS),
            CHIRA_PROP_NAMED_SET(TextureCubemap, wrapModeTStr, wrapModeT, setWrapModeT),
            CHIRA_PROP_NAMED_SET(TextureCubemap, wrapModeRStr, wrapModeR, setWrapModeR)
    );
};

} // namespace chira