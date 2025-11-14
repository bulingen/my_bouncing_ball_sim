#include "MySimulationApp.h"
#include <Stonefish/actuators/Push.h>
#include <Stonefish/core/SimulationManager.h>
#include <iostream>

MySimulationApp::MySimulationApp(std::string name, std::string dataDirPath, sf::RenderSettings s, sf::HelperSettings h, sf::SimulationManager *sim)
    : GraphicalSimulationApp(name, dataDirPath, s, h, sim)
{
}

void MySimulationApp::UpdateDirection()
{
    std::string newState = "stop";

    if (upPressed)
    {
        if (leftPressed && homePressed)
        {
            newState = "left up";
        }
        else if (leftPressed && endPressed)
        {
            newState = "left down";
        }
        else if (rightPressed && homePressed)
        {
            newState = "right up";
        }
        else if (rightPressed && endPressed)
        {
            newState = "right down";
        }
        else if (leftPressed)
        {
            newState = "left";
        }
        else if (rightPressed)
        {
            newState = "right";
        }
        else if (homePressed)
        {
            newState = "up";
        }
        else if (endPressed)
        {
            newState = "down";
        }
        else
        {
            newState = "forward";
        }
    }
    else if (downPressed)
    {
        if (leftPressed)
        {
            newState = "reverse left";
        }
        else if (rightPressed)
        {
            newState = "reverse right";
        }
        else
        {
            newState = "backward";
        }
    }

    // Only print if state changed
    if (newState != currentState)
    {
        std::cout << newState << std::endl;
        currentState = newState;

        // Set thruster force based on state
        sf::Push *mainThruster = (sf::Push *)getSimulationManager()->getActuator("MainThruster");
        if (mainThruster)
        {
            const sf::Scalar steeringAngle = 0.35; // ~20 degrees

            if (newState == "forward")
            {
                // Straight forward - no rotation
                sf::Quaternion rot;
                rot.setEulerZYX(0, 0, -M_PI / 2.0);
                mainThruster->setRelativeActuatorFrame(sf::Transform(rot, sf::Vector3(-0.5, 0.0, 0.0)));
                mainThruster->setForce(8.0);
            }
            else if (newState == "left")
            {
                // Turn left - rotating around Z-axis
                sf::Quaternion rot;
                rot.setEulerZYX(steeringAngle, 0, -M_PI / 2.0);
                mainThruster->setRelativeActuatorFrame(sf::Transform(rot, sf::Vector3(-0.5, 0.0, 0.0)));
                mainThruster->setForce(8.0);
            }
            else if (newState == "right")
            {
                // Turn right - rotating around Z-axis (negative angle)
                sf::Quaternion rot;
                rot.setEulerZYX(-steeringAngle, 0, -M_PI / 2.0);
                mainThruster->setRelativeActuatorFrame(sf::Transform(rot, sf::Vector3(-0.5, 0.0, 0.0)));
                mainThruster->setForce(8.0);
            }
            else if (newState == "backward")
            {
                // Straight backward - no rotation
                sf::Quaternion rot;
                rot.setEulerZYX(0, 0, -M_PI / 2.0);
                mainThruster->setRelativeActuatorFrame(sf::Transform(rot, sf::Vector3(-0.5, 0.0, 0.0)));
                mainThruster->setForce(-4.0);
            }
            else if (newState == "reverse left")
            {
                // Reverse and turn left
                sf::Quaternion rot;
                rot.setEulerZYX(steeringAngle, 0, -M_PI / 2.0);
                mainThruster->setRelativeActuatorFrame(sf::Transform(rot, sf::Vector3(-0.5, 0.0, 0.0)));
                mainThruster->setForce(-4.0);
            }
            else if (newState == "reverse right")
            {
                // Reverse and turn right
                sf::Quaternion rot;
                rot.setEulerZYX(-steeringAngle, 0, -M_PI / 2.0);
                mainThruster->setRelativeActuatorFrame(sf::Transform(rot, sf::Vector3(-0.5, 0.0, 0.0)));
                mainThruster->setForce(-4.0);
            }
            else if (newState == "up")
            {
                // Pitch up - rotate around Y-axis
                sf::Quaternion rot;
                rot.setEulerZYX(0, steeringAngle, -M_PI / 2.0);
                mainThruster->setRelativeActuatorFrame(sf::Transform(rot, sf::Vector3(-0.5, 0.0, 0.0)));
                mainThruster->setForce(8.0);
            }
            else if (newState == "down")
            {
                // Pitch down - rotate around Y-axis (negative)
                sf::Quaternion rot;
                rot.setEulerZYX(0, -steeringAngle, -M_PI / 2.0);
                mainThruster->setRelativeActuatorFrame(sf::Transform(rot, sf::Vector3(-0.5, 0.0, 0.0)));
                mainThruster->setForce(8.0);
            }
            else if (newState == "stop")
            {
                mainThruster->setForce(0.0);
            }
        }
    }
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
        upPressed = true;
        UpdateDirection();
        // mainThruster->setForce(30.0);
        break;

    case SDLK_DOWN:
        downPressed = true;
        UpdateDirection();
        // mainThruster->setForce(-10.0);
        break;

    case SDLK_LEFT:
        leftPressed = true;
        UpdateDirection();
        break;

    case SDLK_RIGHT:
        rightPressed = true;
        UpdateDirection();
        break;

    case SDLK_HOME:
        homePressed = true;
        UpdateDirection();
        break;

    case SDLK_END:
        endPressed = true;
        UpdateDirection();
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
        upPressed = false;
        UpdateDirection();
        // mainThruster->setForce(0.0);
        break;

    case SDLK_DOWN:
        downPressed = false;
        UpdateDirection();
        // mainThruster->setForce(0.0);
        break;

    case SDLK_LEFT:
        leftPressed = false;
        UpdateDirection();
        break;

    case SDLK_RIGHT:
        rightPressed = false;
        UpdateDirection();
        break;

    case SDLK_HOME:
        homePressed = false;
        UpdateDirection();
        break;

    case SDLK_END:
        endPressed = false;
        UpdateDirection();
        break;
    }
}