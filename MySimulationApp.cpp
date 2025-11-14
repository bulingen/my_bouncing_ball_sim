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

    // Get main thruster
    sf::Push *mainThruster = (sf::Push *)getSimulationManager()->getActuator("MainThruster");

    if (!mainThruster)
        return;

    switch (event->key.keysym.sym)
    {
    case SDLK_UP:
        mainThruster->setForce(30.0);
        break;

    case SDLK_DOWN:
        mainThruster->setForce(-10.0);
        break;
    }
}

void MySimulationApp::KeyUp(SDL_Event *event)
{
    sf::Push *mainThruster = (sf::Push *)getSimulationManager()->getActuator("MainThruster");

    if (!mainThruster)
        return;

    switch (event->key.keysym.sym)
    {
    case SDLK_UP:
    case SDLK_DOWN:
        mainThruster->setForce(0.0);
        break;
    }
}