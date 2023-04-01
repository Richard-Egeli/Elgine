#include "elgine/components/mesh.hpp"
#include "elgine/elgine.hpp"
#include "elgine/opengl.hpp"
#include "elgine/utils/asset-loader.hpp"
#include "game/gamemanager.hpp"

int main(int argc, char **argv) {
    Elgine *elgine = new Elgine();

    GameManager::Init();

    // AssetLoader::LoadMesh("test.gltf");
    elgine->Run();

    delete elgine;

    return 0;
}
