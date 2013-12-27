/*! \file  MessageHandler.h
    \brief Classes defining the interface for handling messages to/from Enki.

 */

#ifndef ENKI_MESSAGE_HANDLER_H
#define ENKI_MESSAGE_HANDLER_H

#include <zmq.hpp>

#include "enki/PhysicalEngine.h"

namespace Enki
{
    //! Abstract base class, defines the message-handling interface for Enki
    /*!

        TODO: This functionality should be implemented in a more generic way. Right now,
              the class is hardcoded for every type of robot. A better approach would be
              to allow users to attach a "handler object" for robots. This way, new
              robots could be added without having to change this class.

     */
    class MessageHandler
    {
    public:
        MessageHandler() { }
        virtual ~MessageHandler() { }

        virtual int handleIncoming(zmq::socket_t* incoming_, World* world) = 0;
        virtual int handleOutgoing(zmq::socket_t* outgoing_) = 0;

    };

}

#endif
