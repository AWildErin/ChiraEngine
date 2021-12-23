#pragma once

#include <string>
#include <unordered_map>
#include "abstractSound.h"

namespace chira {
    class abstractSoundManager {
    public:
        virtual ~abstractSoundManager() = default;
        virtual void init() = 0;
        virtual void update() = 0;
        virtual void stop() = 0;
        virtual void setListenerPosition(const glm::vec3& newPosition) = 0;
        virtual void setListenerRotation(const glm::vec3& newRotation, const glm::vec3& up) = 0;
        virtual void addSound(const std::string& soundName, abstractSound* sound) = 0;
        virtual abstractSound* getSound(const std::string& soundName) = 0;
    protected:
        std::unordered_map<std::string, std::unique_ptr<abstractSound>> sounds;
    };
}