#ifndef __MySimulationApp__
#define __MySimulationApp__

#include <Stonefish/core/GraphicalSimulationApp.h>

class MySimulationApp : public sf::GraphicalSimulationApp
{
public:
    MySimulationApp(std::string name, std::string dataDirPath, sf::RenderSettings s, sf::HelperSettings h, sf::SimulationManager *sim);

    void KeyDown(SDL_Event *event) override;
    void KeyUp(SDL_Event *event) override;

private:
    void UpdateDirection();

    bool upPressed = false;
    bool downPressed = false;
    bool leftPressed = false;
    bool rightPressed = false;

    std::string currentState = "stop";
};

#endif