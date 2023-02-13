#include "pch.h"

int main() {
    std::unique_ptr<application> program = std::make_unique<application>();
    
    program->initWindow();
    program->mainLoop();

    return 0;
}