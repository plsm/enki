/*! \file simple_publisher.cpp
    \brief Use to send commands to the Enki world.

*/

#include <cstdlib>
#include <iostream>

#include <zmq.hpp>

#include <unistd.h> // for usleep

int main(int argc, char *argv[])
{
    if (argc < 5)
    {
        std::cout << "Usage:\n" 
                  << "simple_publisher count address topic \"command arg1 arg2 ...\"" << std::endl;
        return 1;
    }

    int count = atoi(argv[1]);
    std::string topic(argv[3]);
    std::string cmd(argv[4]);
    std::string data(topic + " " + cmd);
    std::string address(argv[2]);
    
    zmq::context_t context(1);

    zmq::socket_t publisher(context, ZMQ_PUB);
    publisher.bind(address.c_str());

    for (int i = 0; i < count; i++)
    {
        usleep(1000000);
        zmq::message_t data_msg(data.length());
        memcpy((void *) data_msg.data(), data.c_str(), data.length());
        std::cout << "Publishing: " << data << " on " << address << std::endl;
        publisher.send(data_msg);
    }

    return 0;
}
