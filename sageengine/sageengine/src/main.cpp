#include "pch.h"


// initialize the extern variable in pch.h
int currentLevel = 0;


int main() {
    std::unique_ptr<application> program = std::make_unique<application>();
    
    program->initWindow();
    program->mainLoop();

    return 0;
}