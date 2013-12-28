/*

 */

#include <zmq.hpp>

#include "enki/robots/e-puck/EPuck.h"
#include "ext/handlers/EPuckHandler.h"

namespace Enki
{

    /* virtual */
    Robot* EPuckHandler::createRobot(zmq::message_t* in_msg)
    {
        if (epucks_.count("pero") > 0)
        {
            // Robot already exists!
            return NULL;
        }
        else
        {
            epucks_["pero"] = new EPuck;
            return epucks_["pero"];
        }
    }

    /* virtual */
    int EPuckHandler::handleIncoming(zmq::message_t* in_msg)
    {
        if (epucks_.begin() != epucks_.end())
        {
            epucks_.begin()->leftSpeed = 10;
            epucks_.begin()->rightSpeed = 10;
        }
    }

    /* virtual */
    int EPuckHandler::handleOutgoing(zmq::message_t** out_msg)
    {
        count = 1;
        out_msg = new message_t*;
        out_msg[0] = new message_t(12);
        snprintf((char*) out_msg[0]->data(), 12, "sensor data");
        return count
    }
}
