#include "MySimulationManager.h"
#include <Stonefish/entities/statics/Plane.h>
#include <Stonefish/entities/solids/Box.h>
#include <Stonefish/entities/solids/Sphere.h>
#include <Stonefish/actuators/Push.h>
#include <Stonefish/joints/FixedJoint.h>

MySimulationManager::MySimulationManager(sf::Scalar stepsPerSecond) : SimulationManager(stepsPerSecond)
{
}

void MySimulationManager::BuildScenario()
{
    // Enable ocean with calm water (0 waves) at standard water properties
    // Water density ~1000 kg/m³, viscosity ~0.001 Pa·s
    sf::Fluid water;
    water.name = "Water";
    water.density = 1000.0;
    water.viscosity = 0.001;
    water.IOR = 1.33;        // Index of refraction
    EnableOcean(0.0, water); // 0.0 = no waves

    // Physical materials
    // Make a light material (500 kg/m³) so sphere floats in water (1000 kg/m³)
    CreateMaterial("Foam", 500.0, 0.8);
    // Make AUV material close to water density for neutral buoyancy (less bouncy)
    CreateMaterial("AUVBody", 999.0, 0.9); // Nearly neutral buoyancy
    CreateMaterial("Steel", 7810.0, 0.9);
    CreateMaterial("Lead", 1340.0, 0.9); // Heavy ballast material
    SetMaterialsInteraction("Foam", "Foam", 0.7, 0.5);
    SetMaterialsInteraction("AUVBody", "AUVBody", 0.4, 0.3);
    SetMaterialsInteraction("Steel", "Steel", 0.4, 0.2);
    SetMaterialsInteraction("Foam", "Steel", 0.6, 0.4);
    SetMaterialsInteraction("AUVBody", "Steel", 0.5, 0.3);
    SetMaterialsInteraction("Lead", "Lead", 0.4, 0.3);

    // Graphical materials (looks)
    CreateLook("gray", sf::Color::Gray(0.5f), 0.3f, 0.2f);
    CreateLook("yellow", sf::Color::RGB(1.f, 1.f, 0.f), 0.3f, 0.1f);
    CreateLook("red", sf::Color::RGB(1.f, 0.f, 0.f), 0.3f, 0.1f);
    CreateLook("green", sf::Color::RGB(0.f, 1.f, 0.f), 0.3f, 0.1f);
    CreateLook("blue", sf::Color::RGB(0.f, 0.f, 1.f), 0.3f, 0.1f);

    // No ocean floor needed for floating test
    // sf::Plane *plane = new sf::Plane("SeaFloor", 10000.0, "Steel", "gray");
    // AddStaticEntity(plane, sf::Transform(sf::IQ(), sf::Vector3(0.0, 0.0, -50.0)));

    sf::BodyPhysicsSettings sphere_physics;
    sphere_physics.mode = sf::BodyPhysicsMode::SUBMERGED;
    sf::Sphere *sph = new sf::Sphere("FloatingBall", sphere_physics, 0.2, sf::I4(), "Foam", "red");
    AddSolidEntity(sph, sf::Transform(sf::IQ(), sf::Vector3(0.0, 1.0, -2.0)));

    // Create AUV as a box (1m long, 0.1m wide, 0.1m tall)
    // Box naturally has X=length, Y=width, Z=height - aligned with world frame
    sf::BodyPhysicsSettings phy;
    phy.mode = sf::BodyPhysicsMode::SUBMERGED;

    // Shift origin to lower center of mass - shift origin upward in local frame (negative Z)
    sf::Transform boxOrigin(sf::IQ(), sf::Vector3(0.0, 0.0, -0.04)); // Shift COM 2cm lower

    sf::Box *auv = new sf::Box("SimpleAUV", phy, sf::Vector3(1.0, 0.1, 0.1), boxOrigin, "AUVBody", "yellow");
    AddSolidEntity(auv, sf::Transform(sf::IQ(), sf::Vector3(0.0, 0.0, -1.0)));

    // Thruster location in box's local frame
    sf::Quaternion thrusterRotation = sf::Quaternion::getIdentity();
    thrusterRotation.setEulerZYX(0, 0, M_PI / 2.0); // 90° rotation around Y-axis
    sf::Transform thrusterTransform(thrusterRotation, sf::Vector3(-0.5, 0.0, 0.0));
    // sf::Transform thrusterTransform(sf::IQ(), sf::Vector3(0.0, 0.0, -0.5));

    // Add thruster at back - pushes along +X (forward)
    sf::Push *mainThruster = new sf::Push("MainThruster", false);
    mainThruster->setForceLimits(-10.0, 30.0);
    mainThruster->AttachToSolid(auv, thrusterTransform);
    AddActuator(mainThruster);
}