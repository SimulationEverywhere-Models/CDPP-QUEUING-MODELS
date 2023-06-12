/*******************************************************************
*
*  DESCRIPTION: Server Model
*
*  AUTHOR: Khaldoon Al-Zoubi 
*
*
*  DATE: 20/11/2003
*
*******************************************************************/

#ifndef __SERVER_H
#define __SERVER_H

#include "atomic.h"     // class Atomic

/** forward declarations **/
class Distribution ;

class Server : public Atomic
{
public:
	Server( const string &name = "Server" );	//Default constructor
	~Server ();

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &in;
	const Port &beReady;
	Port &out;
	Port &request;
	//Time delayTime;
	int myId;  // The id of this server.
	double value;
	bool ready;
	Distribution *dist ;

	Distribution &distribution()
			{return *dist;}	
};	// class Server

// ** inline ** // 
inline
string Server::className() const
{
	return "Server" ;
}

#endif   //__SERVER_H
