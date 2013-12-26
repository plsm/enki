/*! \file simple_subscriber.cpp
    \brief Use to read data from the Enki world.

*/

#include <iostream>
#include <sstream>

#include <zmq.hpp>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cout << "Usage:\n" 
                  << "simple_subscriber address topic " << std::endl;
        return 1;
    }

    std::string topic(argv[2]);
    std::string address(argv[1]);
    
    zmq::context_t context(1);

    zmq::socket_t subscriber(context, ZMQ_SUB);
    subscriber.connect(address.c_str());
    subscriber.setsockopt(ZMQ_SUBSCRIBE, topic.c_str(), topic.length());

    std::cout << "Listening to messages from:  " << address << std::endl;

    while (1)
    {
        zmq::message_t data_msg;
        subscriber.recv(&data_msg);

        std::cout << "Received: " << std::string(static_cast<char*>(data_msg.data())) << std::endl;
    }


    return 0;
}
