#ifndef __Visualisation_h__
#define __Visualisation_h__

#include <SDL/SDL.h>
#include <glm/glm.hpp>

#include "Camera.h"
#include "Axis.h"
#include "HUD.h"
#include "Text.h"
#include "interface/Viewport.h"

#undef main //SDL breaks the regular main entry point, this fixes

class Scene;
class Skybox;

/*
This class provides an OpenGL window
*/
class Visualisation : public Viewport
{
public:
    Visualisation(char *windowTitle, int windowWidth, int windowHeight);
    ~Visualisation();

    Scene *setScene(Scene *scene);
    void render();
    void run(); // @todo - improve

    const char *getWindowTitle() const;
    void setWindowTitle(const char *windowTitle);

    void quit();
    void toggleFullScreen();
    void toggleMouseMode();
    void resizeWindow();
    bool isFullscreen() const;

    void defaultProjection();
    void defaultLighting();
    void setRenderAxis(bool state);
    void setMSAA(bool state);
    void setSkybox(bool state);
    const Camera *getCamera() const;
    const Scene *getScene() const;
	const glm::mat4 *getFrustrumPtr() const override;
	HUD* getHUD();
private:
    void clearFrame();
    void handleKeypress(SDL_Keycode keycode, int x, int y);
    void handleMouseMove(int x, int y);
    void updateFPS();
    bool init();
    void close();

    SDL_Window* window;
    SDL_Rect windowedBounds;
    SDL_GLContext context;

	HUD hud;
    Camera camera;
    Scene* scene;
    glm::mat4 frustum;

    bool isInitialised;
    bool continueRender;

    bool renderAxisState;
    bool msaaState;

    //Default objects
    Axis axis;
    Skybox *skybox;

    const char* windowTitle;
    int windowWidth;
    int windowHeight;

    //FPS tracking stuff
    unsigned int previousTime = 0;
    unsigned int currentTime;
    unsigned int frameCount = 0;
    std::shared_ptr<Text> fpsDisplay;
    std::shared_ptr<Text> helpText;
};

#endif //ifndef __Visualisation_h__
