/*! \file  RobotHandler.h
    \brief Classes defining the interface for handling messages to/from Enki robots.

 */

#ifndef ENKI_ROBOT_HANDLER_H
#define ENKI_ROBOT_HANDLER_H

//#include <zmq.hpp>

//#include "enki/PhysicalEngine.h"

// Forward declarations
namespace zmq
{
    class message_t;
}

namespace Enki
{

    class Robot;

    //! Abstract base class, defines the message-handling interface for Enki
    /*! Users should implement their own message handling according for each robot type.

     */
    class RobotHandler
    {
    public:
        RobotHandler() { }
        virtual ~RobotHandler() { }
        
        //! Robot factory method
        /*! Override this method to create the appropriate
            robot type.

         */
        virtual Robot* CreateRobot() = 0;

        //! Handle incoming message
        /*! Override this method to handle incoming messages
            for your particular robot.

         */
        virtual int handleIncoming(zmq::message_t* in_msg) = 0;

        //! Handle outgoing message
        /*! Override this method to handle outgoing messages 
            for your particular robot.
         */
        virtual int handleOutgoing(zmq::message_t** out_msg) = 0;
    };

}

#endif
