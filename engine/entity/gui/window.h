#pragma once

#include <imgui.h>
#include <entity/entity.h>

namespace chira {
    class Window : public Entity {
    public:
        Window(const std::string& title_, bool startVisible, const ImVec2& windowSize = ImVec2(), bool enforceSize = false);
        void render(glm::mat4 parentTransform) override;
        virtual void preRenderContents() {};
        virtual void renderContents() = 0;
        virtual void postRenderContents() {};
    protected:
        std::string title;
        ImVec2 nextWindowSize;
        ImGuiCond_ windowSizeCondition;
        ImGuiWindowFlags flags;
    };
}