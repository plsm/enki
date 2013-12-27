/*

 */

#include "AssisiMessageHandler.h"

namespace Assisi
{

    /* virtual */
    int MessageHandler::handleIncoming(zmq::socket_t* incoming_, Enki::World* world)
    {
        int count = 0;

        zmq::message_t ctrl_msg;
        int len = incoming_->recv(&ctrl_msg, ZMQ_DONTWAIT);
        while (len > 0)
        {
            count++;
            std::cout << "Received: " << std::string(static_cast<char*>(ctrl_msg.data())) << std::endl;
            len = incoming_->recv(&ctrl_msg, ZMQ_DONTWAIT);
        }
        
        return count;
    }

    /* virtual */
    int MessageHandler::handleOutgoing(zmq::socket_t* outgoing_)
    {
        int count = 0;

        zmq::message_t pub_msg(26);
        snprintf((char *) pub_msg.data(), 26, "sensor Publishing data...");
        outgoing_->send(pub_msg);
        count++;

        return count;
    }


}
