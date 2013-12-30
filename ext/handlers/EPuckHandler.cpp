/*

 */

#include <zmq.hpp>
#include "ext/zmq_helpers.h"

#include "enki/robots/e-puck/EPuck.h"
#include "ext/handlers/EPuckHandler.h"

using zmq::message_t;
using zmq::socket_t;
using std::string;

namespace Enki
{

    /* virtual */
    string EPuckHandler::createRobot(socket_t* sock, World* world)
    {
        string name("");
        if (epucks_.count("pero") < 1)
        {
            // Robot doesn't exist yet!
            epucks_["pero"] = new EPuck;
            world->addObject(epucks_["pero"]);
        }
        return name;
    }

    /* virtual */
    int EPuckHandler::handleIncoming(socket_t* sock, string name)
    {
        if (epucks_.begin() != epucks_.end())
        {
            epucks_.begin()->second->leftSpeed = 10;
            epucks_.begin()->second->rightSpeed = 10;
        }
    }

    /* virtual */
    int EPuckHandler::sendOutgoing(socket_t* sock)
    {
        int count = 1;
        message_t msg;
        string header_str("EPuck");
        string msg_str("sensor data");
        str_to_msg(header_str, msg);
        sock->send(msg, ZMQ_SNDMORE);
        str_to_msg(msg_str, msg);
        sock->send(msg);
        //snprintf((char*) sens_msg.data(), 12, "sensor data");
        // memcpy((void *) sens_msg.data(), data.c_str(), data.length());
        return count;
    }
}
