#include <iostream>

#include "elgine.hpp"
#include "game/gamemanager.hpp"

int main(int argc, char **argv) {
    Elgine *elgine = new Elgine();

    GameManager::Init();

    elgine->Run();

    delete elgine;

    return 0;
}
