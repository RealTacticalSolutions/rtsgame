#include "pch.h"

int main() {
    std::unique_ptr<program> programWindow = std::make_unique<program>();

    programWindow->run();

    return 0;
}