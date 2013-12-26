/* World extension implementation.

 */

#include "WorldExt.h"

using std::string;

namespace Enki
{

    WorldExt::WorldExt(double r, const string& protocol, const string& address,
                       const string& port, const Color& wallsColor,
                       unsigned texWidth, unsigned texHeight, const uint32_t* texData)
        : World(r, wallsColor, texWidth, texHeight, texData),
          protocol_(protocol), address_(address), port_(port)
    {

    }

    WorldExt::~WorldExt()
    {

    }

    /* virtual */
    void WorldExt::controlStep(double dt)
    {

    }

}
