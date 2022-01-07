#pragma once

#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <map>
#include <functional>
#include <vector>
#include <memory>
#include <input/keybind.h>
#include <input/mousebind.h>
#include <loader/settings/abstractSettingsLoader.h>
#include <script/abstractScriptProvider.h>
#include <script/angelscriptProvider.h>
#include <sound/abstractSoundManager.h>
#include <physics/abstractPhysicsProvider.h>
#include <entity/3d/root.h>
#include <utility/math/color.h>

namespace chira {
    class Console;
    class Profiler;

    const std::string ENGINE_FILESYSTEM_PATH = "engine"; // NOLINT(cert-err58-cpp)

    class Engine {
    public:
        /// Ran at the very start of your program. Readies the engine for you to add features before init().
        static void preInit(const std::string& configPath = "settings.json");
        static void init();
        static void run();
        static void render();
        static void stop();

        static void addInitFunction(const std::function<void()>& init);
        static void addRenderFunction(const std::function<void()>& render);
        static void addStopFunction(const std::function<void()>& stop);

        static void setBackgroundColor(ColorRGB color);
        static glm::vec2 getWindowSize();
        static int getWindowWidth();
        static int getWindowHeight();
        static void setWindowSize(int width, int height);
        static void shouldStopAfterThisFrame(bool yes);

        static void addKeybind(const Keybind& keybind);
        static std::vector<Keybind>* getKeybinds();
        static void addMousebind(const Mousebind& mousebind);
        static std::vector<Mousebind>* getMousebinds();

        static AngelscriptProvider* getAngelscriptProvider();
        static void setSoundManager(AbstractSoundManager* newSoundManager);
        static AbstractSoundManager* getSoundManager();

        static AbstractSettingsLoader* getSettingsLoader();
        static void setSettingsLoader(AbstractSettingsLoader* newSettingsLoader);
        static AbstractPhysicsProvider* getPhysicsProvider();
        static void setPhysicsProvider(AbstractPhysicsProvider* newPhysicsProvider);

        [[nodiscard]] static Root* getRoot();

        static void callRegisteredFunctions(const std::vector<std::function<void()>>* list);

        [[nodiscard]] static GLFWwindow* getWindow();
        [[nodiscard]] static bool isStarted();
        /// Note: only guaranteed to work after run() in a render method
        [[nodiscard]] static double getDeltaTime();
        static void captureMouse(bool capture);
        [[nodiscard]] static bool isMouseCaptured();
        static Console* getConsole();
        static Profiler* getProfiler();
        [[nodiscard]] static bool isIconified();
    private:
        static GLFWwindow* window;
        static std::vector<std::function<void()>> initFunctions;
        static std::vector<std::function<void()>> renderFunctions;
        static std::vector<std::function<void()>> stopFunctions;
        static std::unique_ptr<AngelscriptProvider> angelscript;
        static std::unique_ptr<AbstractSoundManager> soundManager;
        static std::vector<Keybind> keybinds;
        static std::vector<Mousebind> mousebinds;
        static std::unique_ptr<AbstractSettingsLoader> settingsLoader;
        static std::unique_ptr<AbstractPhysicsProvider> physicsProvider;
        static Root* root;
        static Console* console;
#ifdef DEBUG
        static Profiler* profiler;
#endif
        static bool mouseCaptured;
        static bool started;
        static bool iconified;
        static double lastTime, currentTime, lastMouseX, lastMouseY;

        static void setSettingsLoaderDefaults();
        /// Note: PNGs must have a bit depth of 8 or less* (less not tested)
        static void setIcon(const std::string& iconPath);
        static void displaySplashScreen();
        static void framebufferSizeCallback(GLFWwindow* w, int width, int height);
        static void keyboardCallback(GLFWwindow* w, int key, int scancode, int action, int mods);
        static void keyboardRepeatingCallback();
        static void mouseButtonCallback(GLFWwindow* w, int button, int action, int mods);
        static void mouseButtonRepeatingCallback();
        static void mouseMovementCallback(GLFWwindow* w, double xPos, double yPos);
        static void mouseScrollCallback(GLFWwindow* w, double xPos, double yPos);
        static void windowIconifyCallback(GLFWwindow* w, int isIconified);
    };
}
