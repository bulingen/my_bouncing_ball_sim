#include "MySimulationApp.h"
#include <Stonefish/actuators/Push.h>
#include <Stonefish/core/SimulationManager.h>

MySimulationApp::MySimulationApp(std::string name, std::string dataDirPath, sf::RenderSettings s, sf::HelperSettings h, sf::SimulationManager *sim)
    : GraphicalSimulationApp(name, dataDirPath, s, h, sim)
{
}

void MySimulationApp::KeyDown(SDL_Event *event)
{
    // Call base class to keep default functionality (camera movement, etc.)
    GraphicalSimulationApp::KeyDown(event);

    // Get thrusters
    sf::Push *mainThruster = (sf::Push *)getSimulationManager()->getActuator("MainThruster");
    sf::Push *leftThruster = (sf::Push *)getSimulationManager()->getActuator("LeftThruster");
    sf::Push *rightThruster = (sf::Push *)getSimulationManager()->getActuator("RightThruster");

    switch (event->key.keysym.sym)
    {
    case SDLK_UP:
        if (mainThruster)
            mainThruster->setForce(20.0); // Forward
        break;

    case SDLK_DOWN:
        if (mainThruster)
            mainThruster->setForce(-10.0); // Reverse
        break;

    case SDLK_LEFT:
        // Turn left: fire RIGHT thruster (pushes right side, turns left)
        if (rightThruster)
            rightThruster->setForce(5.0);
        break;

    case SDLK_RIGHT:
        // Turn right: fire LEFT thruster (pushes left side, turns right)
        if (leftThruster)
            leftThruster->setForce(5.0);
        break;
    }
}

void MySimulationApp::KeyUp(SDL_Event *event)
{
    // Get thrusters
    sf::Push *mainThruster = (sf::Push *)getSimulationManager()->getActuator("MainThruster");
    sf::Push *leftThruster = (sf::Push *)getSimulationManager()->getActuator("LeftThruster");
    sf::Push *rightThruster = (sf::Push *)getSimulationManager()->getActuator("RightThruster");

    switch (event->key.keysym.sym)
    {
    case SDLK_UP:
    case SDLK_DOWN:
        if (mainThruster)
            mainThruster->setForce(0.0);
        break;

    case SDLK_LEFT:
        if (rightThruster)
            rightThruster->setForce(0.0);
        break;

    case SDLK_RIGHT:
        if (leftThruster)
            leftThruster->setForce(0.0);
        break;
    }
}