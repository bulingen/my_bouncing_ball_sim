#include <Stonefish/core/GraphicalSimulationApp.h>
#include "MySimulationManager.h"
#include "MySimulationApp.h"

int main(int argc, char **argv)
{
    // Using default settings
    sf::RenderSettings s;
    sf::HelperSettings h;

    MySimulationManager manager(500.0);
    MySimulationApp app("Simple AUV Simulator", "path_to_data", s, h, &manager);
    app.Run();

    return 0;
}