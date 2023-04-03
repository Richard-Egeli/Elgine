#include "include/glslwrap/definitions.hpp"

int main(int argc, const char* argv[]) {
    vec3 pos = vec3(10, 10, 10);

    vec3 val = vec3(1.0) * pos;

    vec3 er = mix(pos);

    return 0;
}
