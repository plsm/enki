/*! \file  AssisiMessageHandler.h
    \brief Message handling implementation for the ASSISI project.

*/

#ifndef ASSISI_MESSAGE_HANDLER_H
#define ASSISI_MESSAGE_HANDLER_H

#include <map>

#include "enki/PhysicalEngine.h"

#include "MessageHandler.h"

namespace Assisi
{
    //! Abstract base class, defines the message-handling interface for Enki
    /*!

        TODO: This functionality should be implemented in a more generic way. Right now,
              the class is hardcoded for every type of robot. A better approach would be
              to allow users to attach a "handler object" for robots. This way, new
              robots could be added without having to change this class.

     */
    class MessageHandler : public Enki::MessageHandler
    {
    public:
        MessageHandler() { }
        virtual ~MessageHandler() { }

        int handleIncoming(zmq::socket_t* incoming_, Enki::World* world);
        int handleOutgoing(zmq::socket_t* outgoing_);

    private:
        std::map<std::string, Enki::Robot*> robots_;
    };

}


#endif
