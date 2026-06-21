#include "engine/core/Engine.h"
#include <iostream>

int main() {
    try {
        OpenHorizon::Engine engine;
        engine.initialize(1920, 1080, "OPEN HORIZON - FH6 Competitor");
        engine.run();
        engine.shutdown();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
}
