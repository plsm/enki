/* World extension implementation.

 */

#include <cstdio>

#include <iostream>

#include "enki/robots/e-puck/EPuck.h"
#include "WorldExt.h"

using std::string;

namespace Enki
{

    WorldExt::WorldExt(double r, MessageHandler* msg_handler,
                       const string& pub_address, const string& sub_address,
                       const Color& wallsColor, unsigned texWidth, unsigned texHeight, 
                       const uint32_t* texData)
        : World(r, wallsColor, texWidth, texHeight, texData),
          msg_handler_(msg_handler), pub_address_(pub_address), sub_address_(sub_address)
    {
        context_ = new zmq::context_t(1);
        publisher_ = new zmq::socket_t(*context_, ZMQ_PUB);
        subscriber_ = new zmq::socket_t(*context_, ZMQ_SUB);

        publisher_->bind(pub_address_.c_str());
        subscriber_->connect(sub_address_.c_str());
        subscriber_->setsockopt(ZMQ_SUBSCRIBE, "control", 7);
    }

    WorldExt::~WorldExt()
    {
        delete subscriber_;
        delete publisher_;
        delete context_;
        delete msg_handler_;
    }

    /* virtual */
    void WorldExt::controlStep(double dt)
    {
        // TODO: Check if this update sequence is correct

        // Read controller outputs & apply to robots
        msg_handler_->handleIncoming(subscriber_, this);

        // Publish sensor data
        msg_handler_->handleOutgoing(publisher_);
    }

}
