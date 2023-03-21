#include <iostream>

#include "elgine.hpp"

int main(int argc, char **argv) {
    Elgine *elgine = new Elgine();

    elgine->Run();

    delete elgine;

    return 0;
}
