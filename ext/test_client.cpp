/*! \file spawn_client.cpp
    \brief Spawn named robots into the Enki world.

*/

#include <iostream>
#include <zmq.hpp>

#include <unistd.h> // for usleep

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        std::cout << "Usage:\n" 
                  << "test_client address topic \"command arg1 arg2 ...\"" << std::endl;
        return 1;
    }

    std::string topic(argv[2]);
    std::string cmd(argv[3]);
    std::string data(topic + " " + cmd);
    std::string address(argv[1]);
    
    zmq::context_t context(1);

    zmq::socket_t publisher(context, ZMQ_PUB);
    publisher.bind(address.c_str());
    zmq::message_t data_msg(data.length());
    memcpy((void *) data_msg.data(), data.c_str(), data.length());
    usleep(1000000);

    std::cout << "Sending: " << data << " to " << address << std::endl;
    publisher.send(data_msg);


    return 0;
}
