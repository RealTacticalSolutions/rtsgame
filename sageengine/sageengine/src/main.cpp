#include "pch.h"

int main() {
    std::unique_ptr<application> program= std::make_unique<program>();

    program->run();

    
    return 0;
}