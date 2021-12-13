#include <tinyfiledialogs.h>
#include <core/engine.h>
#include <sound/oggFileSound.h>
#include <render/phongMaterial.h>
#include <hook/discordRichPresence.h>
#include <resource/provider/filesystemResourceProvider.h>
#include <resource/resource.h>
#include <utility/markdown.h>
#include <entity/3d/model/mesh3d.h>
#include <i18n/translationManager.h>
#include <entity/3d/physics/bulletRigidBody.h>
#include <entity/imgui/settings/settings.h>
#include "entity/3d/camera/freecam.h"

using namespace chira;

int main() {
    engine::preInit();
    resource::addResourceProvider("file", new filesystemResourceProvider{"file", "resources/editor"});
    translationManager::addTranslationFile("file://i18n/editor");
    translationManager::addUniversalFile("file://i18n/editor");

    engine::getSettingsLoader()->setValue("engineGui", "discordIntegration", true, false, true);
    bool discordEnabled;
    engine::getSettingsLoader()->getValue("engineGui", "discordIntegration", &discordEnabled);

    engine::addKeybind(keybind(GLFW_KEY_ESCAPE, GLFW_PRESS, []() {
        engine::stop();
    }));
    engine::addKeybind(keybind(GLFW_KEY_1, GLFW_PRESS, []() {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }));
    engine::addKeybind(keybind(GLFW_KEY_2, GLFW_PRESS, []() {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }));
    engine::addKeybind(keybind(GLFW_KEY_GRAVE_ACCENT, GLFW_PRESS, []() {
        engine::getConsole()->setVisible(!engine::getConsole()->isVisible());
    }));
#if DEBUG
    engine::addKeybind(keybind(GLFW_KEY_F1, GLFW_PRESS, []() {
        engine::getProfiler()->setVisible(!engine::getProfiler()->isVisible());
    }));
#endif
    engine::addKeybind(keybind(GLFW_KEY_M, GLFW_PRESS, []() {
        engine::getSoundManager()->getSound("helloWorld")->play();
    }));
    engine::addKeybind(keybind(GLFW_KEY_P, GLFW_RELEASE, []() {
        const char* path = tinyfd_openFileDialog(TR("ui.window.select_file").c_str(),
#if _WIN32
                "C:\\",
#else
                "/",
#endif
                0, nullptr, nullptr, 0);
        if (path) {
            logger::log(INFO_IMPORTANT, "File Picker Debug", std::string(path));
            delete path;
        } else {
            logger::log(INFO_IMPORTANT, "File Picker Debug", TR("generic.operation.cancelled"));
        }
    }));

    sharedPointer<meshResource> cubeMesh;

    engine::addInitFunction([&cubeMesh, &discordEnabled]() {
        //region Enable Discord Rich Presence
        if (discordEnabled) {
            discordRichPresence::init(TR("editor.discord.application_id"));
            discordRichPresence::setLargeImage("main_logo");
            discordRichPresence::setState("https://discord.gg/ASgHFkX");
        }
        //endregion

        //region Set the default font
        auto noto = resource::getResource<fontResource>("file://fonts/default.json");
        ImGui::GetIO().FontDefault = noto->getFont();
        //endregion

        //region Add a teapot with a static rigidbody
        auto staticTeapot = new bulletRigidBody{"file://physics/ground_static.json"};
        staticTeapot->translate(glm::vec3{3,0,-13});
        auto cubeMaterial = resource::getResource<phongMaterial>("file://materials/cubeMaterial.json");
        cubeMesh = resource::getResource<meshResource>("file://meshes/teapot.json", cubeMaterial.castDynamic<material>());
        staticTeapot->addChild(new mesh3d{cubeMesh});

        auto fallingTeapot = new bulletRigidBody{"file://physics/cube_dynamic.json"};
        fallingTeapot->translate(glm::vec3{0,15,-10});
        fallingTeapot->addChild(new mesh3d{cubeMesh});

        engine::getRoot()->addChild(staticTeapot);
        engine::getRoot()->addChild(fallingTeapot);
        //endregion

        auto settingsUI = new settings{};
        engine::getRoot()->addChild(settingsUI);
        engine::addKeybind(keybind(GLFW_KEY_O, GLFW_PRESS, [settingsUI](){
            settingsUI->setVisible(!settingsUI->isVisible());
        }));

        //region Add the camera
        engine::captureMouse(true);
        auto camera = new freecam{"freecam", cameraProjectionMode::PERSPECTIVE};
        engine::getRoot()->addChild(camera);
        engine::getRoot()->setMainCamera(camera);
        //endregion

        //region Add a test script
        engine::getAngelscriptProvider()->addScript("file://scripts/testScript.as");
        //endregion

        //region Add a test sound
        auto* sound = new oggFileSound();
        sound->init("helloWorldCutMono.ogg");
        engine::getSoundManager()->addSound("helloWorld", sound);
        //endregion

        //region Apply some lighting properties to the mesh
        cubeMaterial->setShininess();
        cubeMaterial->setLambertFactor();
        auto cubeShader = cubeMaterial->getShader();
        cubeShader->use();
        cubeShader->setUniform("light.ambient", 0.1f, 0.1f, 0.1f);
        cubeShader->setUniform("light.diffuse", 1.0f, 1.0f, 1.0f);
        cubeShader->setUniform("light.specular", 1.0f, 1.0f, 1.0f);
        cubeShader->setUniform("light.position", 0.0f, 5.0f, 0.0f);
        //endregion

        //region Set a nice skybox
        engine::getRoot()->setSkybox("file://materials/skyboxShanghaiMaterial.json");
        //endregion

        camera->translate(glm::vec3{0,0,15});
    });
    engine::init();

    engine::addRenderFunction([cubeMesh]() {
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_AutoHideTabBar | ImGuiDockNodeFlags_PassthruCentralNode);

        // todo: use UBO
        cubeMesh->getMaterial()->getShader()->use();
        cubeMesh->getMaterial()->getShader()->setUniform("p", engine::getRoot()->getMainCamera()->getProjection());
        cubeMesh->getMaterial()->getShader()->setUniform("v", engine::getRoot()->getMainCamera()->getView());

        // todo: use UBO
        engine::getRoot()->getSkybox()->getShader()->use();
        engine::getRoot()->getSkybox()->getShader()->setUniform("p", engine::getRoot()->getMainCamera()->getProjection());
        engine::getRoot()->getSkybox()->getShader()->setUniform("v", glm::mat4(glm::mat3(engine::getRoot()->getMainCamera()->getView())));
    });
    engine::run();
}
