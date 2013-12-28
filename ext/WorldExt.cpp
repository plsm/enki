/* World extension implementation.

 */

#include <cstdio>

#include <iostream>

#include "enki/robots/e-puck/EPuck.h"
#include "WorldExt.h"

using std::string;

namespace Enki
{

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

    WorldExt::~WorldExt()
    {
        delete subscriber_;
        delete publisher_;
        delete context_;
     }

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
            // Call handler here!
            std::cout << "Received: " << std::string(static_cast<char*>(ctrl_msg.data())) << std::endl;
            len = subscriber_->recv(&ctrl_msg, ZMQ_DONTWAIT);
        }

        // Publish sensor data
        int out_count = 0;

        // Call handlers here!
        zmq::message_t pub_msg(11);
        snprintf((char *) pub_msg.data(), 11, "sensor data");
        publisher_->send(pub_msg);
        out_count++;
    }

}
