/*! \file   playground_ext.h
    \brief  A simple enki playground with an external interface.

 */

#ifndef PLAYGROUND_EXT_H
#define PLAYGROUND_EXT_H

// Enki includes
#include <viewer/Viewer.h>
#include <enki/PhysicalEngine.h>
#include <enki/robots/e-puck/EPuck.h>
#include <enki/robots/marxbot/Marxbot.h>

// Qt includes
//#include <QApplication>
#include <QtGui>
#include <QList>
#include <QByteArray>

// Zmq includes
#include <nzmqt/nzmqt.hpp>

// Standard includes
#include <iostream>


/*!	\file Studio.cpp
	\brief Test of the Qt-based viewer widget
*/

namespace Enki
{

class EnkiPlayground : public ViewerWidget
{

    Q_OBJECT;

protected:
	bool subjectiveView;
	QVector<EPuck*> epucks;
	QMap<PhysicalObject*, int> bullets;

    // External interface variables
    QString address_;
    QString topic_;

    nzmqt::ZMQSocket* socket_;
    nzmqt::ZMQContext* context_;

public:
	EnkiPlayground(World *world, QWidget *parent = 0, 
                   const QString address = "tcp://127.0.0.1:5555",
                   const QString topic = "spawn") :
		ViewerWidget(world, parent),
		subjectiveView(false),
        address_(address),
        topic_(topic),
        socket_(0),
        context_(0)
	{
		
        // Three blue cylinders
		for (double d = 40; d < 60; d += 8)
		{
			PhysicalObject* o = new PhysicalObject;
			o->pos = Point(d, 20);
			o->setCylindric(4, 2, 10);
			o->setColor(Color(0.2, 0.2, 0.6));
			o->dryFrictionCoefficient = 0.;
			world->addObject(o);
		}
		
        // Add two e-pucks
		addDefaultsRobots(world);

        // Open a ZMQ listener
        context_ = nzmqt::createDefaultContext(this);
        context_->start();
        socket_ = context_->createSocket(nzmqt::ZMQSocket::TYP_SUB, this);
        socket_->setObjectName("Subscriber.Socket.socket(SUB)");
        connect(socket_, SIGNAL(messageReceived(const QList<QByteArray>&)),
                SLOT(messageReceived(const QList<QByteArray>&)));

        socket_->subscribeTo(topic_);
        socket_->connectTo(address_);

		qDebug() << "Listening on " << address_ << " for news about " << topic;	
	}
	
	void addDefaultsRobots(World *world)
	{
		EPuck *epuck = new EPuck;
		epuck->pos = Point(60, 50);
		//epuck->leftSpeed = 5;
		//epuck->rightSpeed = 5;
		world->addObject(epuck);
		
		epuck = new EPuck;
		epuck->pos = Point(40, 50);
		epuck->leftSpeed = 5;
		epuck->rightSpeed = 5;
		epuck->setColor(Color(1, 0, 0));
		//world->addObject(epuck);
	}
	
	~EnkiPlayground()
	{

	}
	
    // Inherited from viewer widget (?)
	virtual void timerEvent(QTimerEvent * event)
	{
		static int fireCounter = 0;
		QMap<PhysicalObject*, int>::iterator i = bullets.begin();
		while (i != bullets.end())
		{
			QMap<PhysicalObject*, int>::iterator oi = i;
			++i;
			if (oi.value())
			{
				oi.value()--;
			}
			else
			{
				PhysicalObject* o = oi.key();
				world->removeObject(o);
				bullets.erase(oi);
				delete o;
			}
		}
		ViewerWidget::timerEvent(event);
	}
	
	virtual void keyPressEvent ( QKeyEvent * event )
	{
		if (event->key() == Qt::Key_C)
		{
			subjectiveView = !subjectiveView;
			if (subjectiveView)
				pitch = M_PI/8;
			event->accept();
		}
		else
			ViewerWidget::keyPressEvent(event);
	}
	
	virtual void sceneCompletedHook()
	{
		glColor3d(0,0,0);
       	renderText(10, height()-50, tr("rotate camera by moving mouse while pressing ctrl+left mouse button"));
		renderText(10, height()-30, tr("move camera on x/y by moving mouse while pressing ctrl+shift+left mouse button"));
		renderText(10, height()-10, tr("move camera on z by moving mouse while pressing ctrl+shift+right mouse button"));
	}

protected slots:
    void messageReceived(const QList<QByteArray>& message)
    {
            qDebug() << "Subscriber> " << message;
    }
};

} // namespace Enki

#endif
