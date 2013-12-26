/* Test the ZMQ extensions.

 */

#include "WorldExt.h"

using std::string;

int main(int argc, char *argv[])
{
    double r = 120; // World radius (in cm?)
    string protocol("tcp://"), address("*"), port(":5555"); 
    Enki::WorldExt world(r, protocol, address, port);

    while (1)
    {
        world.step(0.1, 2);
    }

    return 0;
}
