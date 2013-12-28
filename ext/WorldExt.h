/*! \file    WorldExt.h
    \brief   Extensions of Enki with a ZMQ-based external interface.

    TODO: Add detailed description here...

 */

#ifndef ENKI_WORLD_EXT_H
#define ENKI_WORLD_EXT_H

#include <map>

#include <zmq.hpp>

#include "enki/PhysicalEngine.h"

#include "ext/RobotHandler.h"

namespace Enki
{

    //! The extension of Enki::World with a ZMQ publisher an subscriber
    /*!

     */
    class WorldExt : public World
    {
        
    public:

//! Enki world extened with a ZMQ-based external interface.
    /*! 
        
     */

        //! Construct a world with walls of radius r, start communication.
        /*!
                               WorldExt takes ownership of the object 
                               and deletes it in the destructor!
            \param pub_address The publisher will be bound to this address.
            \param sub_address The subscriber will connect to this address for data.
         */
        WorldExt(double r, 
                 const std::string& pub_address,
                 const std::string& sub_address,
                 const Color& wallsColor = Color::gray,
                 unsigned texWdith = 0,
                 unsigned texHeight = 0,
                 const uint32_t* texData = 0);

        //! Destructor
        virtual ~WorldExt();

    protected:
        virtual void controlStep(double dt);

    private:

        // ZMQ connection data members
        std::string pub_address_;
        std::string sub_address_;
        
        zmq::context_t* context_;
        zmq::socket_t* publisher_;
        zmq::socket_t* subscriber_;
    };

}

#endif