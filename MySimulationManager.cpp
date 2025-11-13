#include "MySimulationManager.h"
#include <Stonefish/entities/statics/Plane.h>
#include <Stonefish/entities/solids/Cylinder.h>
#include <Stonefish/entities/solids/Sphere.h>
#include <Stonefish/actuators/Push.h>

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
    // Make a light material (500 kg/m³) so it floats in water (1000 kg/m³)
    CreateMaterial("Foam", 500.0, 0.8);
    CreateMaterial("Steel", 7810.0, 0.9);
    SetMaterialsInteraction("Foam", "Foam", 0.7, 0.5);
    SetMaterialsInteraction("Steel", "Steel", 0.4, 0.2);
    SetMaterialsInteraction("Foam", "Steel", 0.6, 0.4);

    // Graphical materials (looks)
    CreateLook("gray", sf::Color::Gray(0.5f), 0.3f, 0.2f);
    CreateLook("yellow", sf::Color::RGB(1.f, 1.f, 0.f), 0.3f, 0.1f);
    CreateLook("red", sf::Color::RGB(1.f, 0.f, 0.f), 0.3f, 0.1f);

    // No ocean floor needed for floating test
    // sf::Plane *plane = new sf::Plane("SeaFloor", 10000.0, "Steel", "gray");
    // AddStaticEntity(plane, sf::Transform(sf::IQ(), sf::Vector3(0.0, 0.0, -50.0)));

    sf::BodyPhysicsSettings sphere_physics;
    sphere_physics.mode = sf::BodyPhysicsMode::SUBMERGED;
    sf::Sphere *sph = new sf::Sphere("FloatingBall", sphere_physics, 0.2, sf::I4(), "Foam", "red");
    AddSolidEntity(sph, sf::Transform(sf::IQ(), sf::Vector3(0.0, 0.0, -1.0)));

    // Create AUV-like cylinder (horizontal orientation)
    // SUBMERGED mode enables full hydrodynamics (buoyancy, drag, etc.)
    sf::BodyPhysicsSettings phy;
    phy.mode = sf::BodyPhysicsMode::SUBMERGED;

    // Create cylinder: radius=0.1m, length=0.6m (torpedo-like shape)
    // Cylinder's z-axis is its length, so we rotate it to be horizontal (along x-axis)
    sf::Quaternion rotation = sf::Quaternion::getIdentity();
    rotation.setEulerZYX(sf::Scalar(0), sf::Scalar(M_PI / 2.0), sf::Scalar(0)); // Rotate 90° around Y to make it horizontal

    sf::Cylinder *auv = new sf::Cylinder("SimpleAUV", phy, 0.1, 0.6, sf::I4(), "Foam", "yellow");
    AddSolidEntity(auv, sf::Transform(rotation, sf::Vector3(0.0, 0.0, -1.0)));

    // Add a simple push actuator (thruster) at the back
    sf::Push *thruster = new sf::Push("MainThruster", false);
    thruster->setForceLimits(0.0, 10.0); // 0-10 Newton thrust
    // Attach at back of AUV, pointing in +X direction (forward)
    thruster->AttachToSolid(auv, sf::Transform(sf::IQ(), sf::Vector3(-0.3, 0.0, 0.0)));
    AddActuator(thruster);
}