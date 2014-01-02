/*

 */
#include <boost/foreach.hpp>

#include <zmq.hpp>
#include "ext/zmq_helpers.h"

#include "enki/robots/e-puck/EPuck.h"
#include "ext/handlers/EPuckHandler.h"

#include "ext/base_msgs.pb.h"
#include "ext/sensor_msgs.pb.h"

using zmq::message_t;
using zmq::socket_t;
using std::string;

using namespace AssisiMsg;

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
        BOOST_FOREACH(const EPuckMap::value_type& ep, epucks_)
        {
            /* Publishing IR readings */

            // Send message envelope
            message_t msg;
            str_to_msg(ep.first, msg);
            sock->send(msg, ZMQ_SNDMORE);
            str_to_msg("ir_readings", msg);
            sock->send(msg, ZMQ_SNDMORE);

            // Send IR data
            RangeArray ranges;
            ranges.add_range(ep.second->infraredSensor0.getDist());
            ranges.add_range(ep.second->infraredSensor1.getDist());
            ranges.add_range(ep.second->infraredSensor2.getDist());
            ranges.add_range(ep.second->infraredSensor3.getDist());
            ranges.add_range(ep.second->infraredSensor4.getDist());
            ranges.add_range(ep.second->infraredSensor5.getDist());
            ranges.add_range(ep.second->infraredSensor6.getDist());
            ranges.add_range(ep.second->infraredSensor7.getDist());
            std::string data_str;
            ranges.SerializeToString(&data_str);
            str_to_msg(data_str, msg);
            sock->send(msg);
            count++;

            /* Publish other stuff as necessary ... */
        }
        return count;
    }
}
