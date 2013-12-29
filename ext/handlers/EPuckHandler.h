/* \file  EPuckHandler.h
   \brief Communication handler for the EPuck robot.

 */

#ifndef ENKI_EPUCK_HANDLER_H
#define ENKI_EPUCK_HANDLER_H

#include <map>

//#include "enki/robots/e-puck/EPuck.h"

#include "ext/handlers/RobotHandler.h"

namespace Enki
{
    class EPuck;

    //! Abstract base class, defines the message-handling interface for Enki
    /*! Users should implement their own message handling according for each robot type.

     */
    class EPuckHandler : public RobotHandler
    {
    public:
        EPuckHandler() { }
        virtual ~EPuckHandler() { }
        
        //! Robot factory method
        /*! Creates E-Pucks.

            Keeps a pointer to the created robot, but does not
            delete it in the destructor.

         */
        virtual Robot* createRobot(zmq::message_t* in_msg);

        //! Handle incoming message
        /*! Handles E-Puck motion commands.

         */
        virtual int handleIncoming(zmq::message_t* in_msg);

        //! Assemble outgoing messages
        /*! Creates E-Puck sensor data messages.
         */
        virtual int assembleOutgoing(MessagePtrList& out_msg);

    private:
        std::map<std::string, EPuck*> epucks_;
    };

}

#endif
