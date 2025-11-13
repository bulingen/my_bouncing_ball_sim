#include <Stonefish/core/GraphicalSimulationApp.h>
#include "MySimulationManager.h"
#include "MySimulationApp.h"

int main(int argc, char **argv)
{
    // Configure render settings for larger window
    sf::RenderSettings s;
    s.windowW = 1200; // Increase from default 800
    s.windowH = 800;  // Increase from default 600

    sf::HelperSettings h;

    MySimulationManager manager(500.0);
    MySimulationApp app("Simple AUV Simulator", "path_to_data", s, h, &manager);
    app.Run();

    return 0;
}