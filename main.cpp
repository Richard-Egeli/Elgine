#include "elgine/elgine.hpp"
#include "engine/types/mat4.hpp"
#include "game/gamemanager.hpp"
#include "shaders.hpp"

int main(int argc, char **argv) {
    Elgine *elgine = new Elgine();

    GameManager::Init();

    // mat.position.x = 10;

    // std::cout << mat.mx[0][0] << std::endl;

    elgine->Run();

    delete elgine;

    return 0;
}
