#include <engine/eyos.hpp>
#include <glm/glm.hpp>
#include <enet/enet.h>
#include <stdio.h>

int eyos::calculate_value() {
    // How many roads must a man walk down?
    glm::vec3 vec3{};

    if (enet_initialize () != 0)
    {
        fprintf (stderr, "An error occurred while initializing ENet.\n");
        return EXIT_FAILURE;
    }
    atexit (enet_deinitialize);

    return 6 * 7;
}

float  eyos::calculate_float() { return 1.f; };
double  eyos::calculate_double() { return 1.00; };
unsigned long long  eyos::calculate_unit64() { return 7777; };
