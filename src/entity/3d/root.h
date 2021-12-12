#pragma once

#include "world3d.h"
#include "camera/camera3d.h"
#include <resource/meshResource.h>
#include <render/cubemapMaterial.h>

namespace chira {
    class root : private world3d {
        friend class engine;
    public:
        explicit root(const std::string& name_);
        ~root() override;
        void render();
        glm::vec3 getGlobalPosition() override;
        void setMainCamera(camera3d* camera);
        camera3d* getMainCamera();
        void setSkybox(const std::string& cubemapId);
        sharedPointer<cubemapMaterial> getSkybox();
        glm::vec3 getAudioListeningPosition() {
            return this->mainCamera->getPosition();
        }
        glm::vec3 getAudioListeningRotation() {
            // todo
            return glm::vec3{};
        }
        glm::vec3 getAudioListeningUpVector() {
            return this->mainCamera->getUpVector();
        }
        using world3d::addChild;
        using world3d::getChild;
        using world3d::removeChild;
    private:
        sharedPointer<meshResource> skybox;
        camera3d* mainCamera = nullptr;
        using world3d::render;
        void clearTree();
    };
}
