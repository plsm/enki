/*

 */

#include <zmq.hpp>

#include "enki/robots/e-puck/EPuck.h"
#include "ext/handlers/EPuckHandler.h"

using zmq::message_t;

namespace Enki
{

    /* virtual */
    Robot* EPuckHandler::createRobot(message_t* in_msg)
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
    int EPuckHandler::handleIncoming(message_t* in_msg)
    {
        if (epucks_.begin() != epucks_.end())
        {
            epucks_.begin()->second->leftSpeed = 10;
            epucks_.begin()->second->rightSpeed = 10;
        }
    }

    /* virtual */
    int EPuckHandler::assembleOutgoing(MessagePtrList& out_msgs)
    {
        int count = 1;
        message_t* sens_msg = new message_t(12);
        snprintf((char*) sens_msg->data(), 12, "sensor data");
        // memcpy((void *) sens_msg.data(), data.c_str(), data.length());
        out_msgs.push_back(sens_msg);
        return count;
    }
}
