#pragma once

#include "Root.h"

#include <math/Types.h>

//todo: add/remove postprocessing effects

namespace chira {

class Frame : public Root {
public:
    Frame(const std::string& name_, int width_, int height_, ColorRGB backgroundColor_ = {}, bool smoothResize = true, bool initNow = true);
    Frame(int width_, int height_, ColorRGB backgroundColor_ = {}, bool smoothResize = true, bool initNow = true);
    void update(glm::mat4 parentTransform) override;
    void update(unsigned int parentFBOHandle, int parentWidth, int parentHeight);
    ~Frame() override;
    [[nodiscard]] const Frame* getFrame() const override;
    [[nodiscard]] Frame* getFrame() override;
    [[nodiscard]] unsigned int getFramebufferHandle() const;
    [[nodiscard]] unsigned int getColorTextureHandle() const;
    [[nodiscard]] glm::vec2i getFrameSize() const;
    virtual void setFrameSize(glm::vec2i newSize);
    [[nodiscard]] ColorRGB getBackgroundColor() const;
    void setBackgroundColor(ColorRGB color);
protected:
    unsigned int fboHandle = 0, colorTexHandle = 0, rboHandle = 0;
    ColorRGB backgroundColor{};
    int width = 0, height = 0;
    bool linearFiltering = true;
    /// Deletes the existing framebuffer if one already exists.
    void createFramebuffer();
};

}
