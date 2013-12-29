/* World extension implementation.

 */

#include <cstdio>
#include <iostream>

#include <boost/foreach.hpp>

#include <zmq.hpp>

#include "enki/robots/e-puck/EPuck.h"
#include "ext/handlers/RobotHandler.h"
#include "WorldExt.h"

using std::string;
using std::map;
using zmq::message_t;

namespace Enki
{

// -----------------------------------------------------------------------------

    WorldExt::WorldExt(double r, 
                       const string& pub_address, 
                       const string& sub_address,
                       const Color& wallsColor, 
                       unsigned texWidth, 
                       unsigned texHeight, 
                       const uint32_t* texData)
        : World(r, wallsColor, texWidth, texHeight, texData),
          pub_address_(pub_address), sub_address_(sub_address)
    {
        context_ = new zmq::context_t(1);
        publisher_ = new zmq::socket_t(*context_, ZMQ_PUB);
        subscriber_ = new zmq::socket_t(*context_, ZMQ_SUB);

        publisher_->bind(pub_address_.c_str());
        subscriber_->connect(sub_address_.c_str());
        subscriber_->setsockopt(ZMQ_SUBSCRIBE, "spawn", 5);
    }

// -----------------------------------------------------------------------------

    WorldExt::~WorldExt()
    {
        // We own the handlers, so delete them
        typedef map<string, RobotHandler*> handler_map;
        BOOST_FOREACH(const handler_map::value_type& rh, handlers_)
        {
            delete rh.second;
        }

        delete subscriber_;
        delete publisher_;
        delete context_;
     }

// -----------------------------------------------------------------------------

    bool WorldExt::addHandler(string type, RobotHandler* handler)
    {
        if (handlers_.count(type) > 0)
        {
            return false;
        }
        else
        {
            handlers_[type] = handler;
        }
    }

// -----------------------------------------------------------------------------

    /* virtual */
    void WorldExt::controlStep(double dt)
    {
        // TODO: Check if this update sequence is correct

        // Read controller outputs & apply to robots
        int in_count = 0;

        zmq::message_t ctrl_msg;
        int len = subscriber_->recv(&ctrl_msg, ZMQ_DONTWAIT);
        while (len > 0)
        {
            in_count++;
            if (handlers_.begin() != handlers_.end())
            {
                Robot* rob = handlers_.begin()->second->createRobot(&ctrl_msg);
                if (rob)
                {
                    this->addObject(rob);
                }
                handlers_.begin()->second->handleIncoming(&ctrl_msg);
            }
                
            std::cout << "Received: " << string(static_cast<char*>(ctrl_msg.data())) << std::endl;
            len = subscriber_->recv(&ctrl_msg, ZMQ_DONTWAIT);
        }

        // Publish sensor data
        int out_count = 0;

        // Gather messages from all handlers
        MessagePtrList pub_msgs;
        if (handlers_.begin() != handlers_.end())
        {
            out_count += handlers_.begin()->second->assembleOutgoing(pub_msgs);
        }

        // Send all outgoing messages
        BOOST_FOREACH(message_t* msg, pub_msgs)
        {
            publisher_->send(*msg);
        }
    }

// -----------------------------------------------------------------------------

}
