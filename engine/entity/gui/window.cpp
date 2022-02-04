#include "window.h"

using namespace chira;

Window::Window(const std::string& title_, bool startVisible, const ImVec2& windowSize, bool enforceSize) {
    this->title = title_;
    this->visible = startVisible;
    this->nextWindowSize = windowSize;
    this->windowSizeCondition = enforceSize? ImGuiCond_Always : ImGuiCond_FirstUseEver;
    this->flags = 0;
}

void Window::render(glm::mat4 parentTransform) {
    if (this->visible) {
        ImGui::SetNextWindowSize(this->nextWindowSize, this->windowSizeCondition);
        this->preRenderContents();
        if (ImGui::Begin(this->title.c_str(), &this->visible, this->flags)) {
            this->renderContents();
        }
        ImGui::End();
        this->postRenderContents();
    }
    Entity::render(parentTransform);
}