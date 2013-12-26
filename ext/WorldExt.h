/*! \file    WorldExt.h
    \brief   Extensions of Enki with a ZMQ-based external interface.

    TODO: Add detailed description here...

 */

#ifndef ENKI_WORLD_EXT_H
#define ENKI_WORLD_EXT_H

#include <zmq.hpp>

#include "enki/PhysicalEngine.h"

namespace Enki
{

    //! The extension of Enki::World with a ZMQ publisher an subscriber
    /*!

     */
    class WorldExt : public World
    {
        
    public:

        //! Construct a world with walls of radius r, start communication.
        /*!
            \param protocol Communication protocol. Supports all protocol provided by ZMQ.
                            Valid values are: "tcp://", "ipc://"
            \param address  Address to publish on/subscribe to...TODO
            \param port     Port to publish on/subscribe to...TODO
         */
        WorldExt(double r, 
                 const std::string& pub_address = "tcp://127.0.0.1:5555",
                 const std::string& sub_address = "tcp://127.0.0.1:5556",
                 const Color& wallsColor = Color::gray,
                 unsigned texWdith = 0,
                 unsigned texHeight = 0,
                 const uint32_t* texData = 0);

        //! Destructor
        virtual ~WorldExt();

    protected:
        virtual void controlStep(double dt);

    private:
        std::string pub_address_;
        std::string sub_address_;
        
        zmq::context_t* context_;
        zmq::socket_t* publisher_;
        zmq::socket_t* subscriber_;
    };

}

#endif
