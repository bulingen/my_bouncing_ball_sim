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

    // Get the thruster
    sf::Push *thruster = (sf::Push *)getSimulationManager()->getActuator("MainThruster");

    if (thruster != nullptr)
    {
        switch (event->key.keysym.sym)
        {
        case SDLK_UP:
            // Forward thrust
            thruster->setForce(20.0); // 20N forward
            break;

        case SDLK_DOWN:
            // Reverse thrust
            thruster->setForce(-10.0); // 10N backward
            break;
        }
    }
}

void MySimulationApp::KeyUp(SDL_Event *event)
{
    // Get the thruster
    sf::Push *thruster = (sf::Push *)getSimulationManager()->getActuator("MainThruster");

    if (thruster != nullptr)
    {
        switch (event->key.keysym.sym)
        {
        case SDLK_UP:
        case SDLK_DOWN:
            // Stop thrust when key released
            thruster->setForce(0.0);
            break;
        }
    }
}