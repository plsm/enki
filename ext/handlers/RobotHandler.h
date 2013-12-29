/*! \file  RobotHandler.h
    \brief Classes defining the interface for handling messages to/from Enki robots.

 */

#ifndef ENKI_ROBOT_HANDLER_H
#define ENKI_ROBOT_HANDLER_H

#include <list>

namespace zmq
{
    class message_t;
}

namespace Enki
{

    class Robot;
    
    typedef std::list<zmq::message_t*> MessagePtrList;

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
        virtual Robot* createRobot(zmq::message_t* in_msg) = 0;

        //! Handle incoming message
        /*! Override this method to handle incoming messages
            for your particular robot.

         */
        virtual int handleIncoming(zmq::message_t* in_msg) = 0;

        //! Assemble outgoing messages
        /*! Override this method to create outgoing messages 
            for your particular robot.

            Ownership of the allocated messages is transfered
            to the caller, i.e., the caller *must* call delete
            on all messages!
         */
        virtual int assembleOutgoing(MessagePtrList& out_msg) = 0;
    };

}

#endif
