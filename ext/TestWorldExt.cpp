/* Test the ZMQ extensions.

 */

#include "WorldExt.h"

#include <unistd.h> // for usleep

using std::string;

int main(int argc, char *argv[])
{
    double r = 120; // World radius (in cm?)
    string pub_address("tcp://127.0.0.1:5555"); 
    string sub_address("tcp://127.0.0.1:5556");
    Enki::WorldExt world(r, pub_address, sub_address);
    Enki::World* wp = &world;
    while (1)
    {
        wp->step(10, 20);
        usleep(1000000);
    }

    return 0;
}
