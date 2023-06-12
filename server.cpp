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

/** include files **/
#include "server.h"        // class Server
#include "message.h"   	   // class ExternalMessage, InternalMessage
#include "mainsimu.h"      // MainSimulator::Instance().getParameter( ... )
#include "distri.h"        // class Distribution 


/*******************************************************************
* Function Name: Server
* Description: 	
* 		
********************************************************************/
Server::Server( const string &name )
: Atomic( name )
, in( addInputPort( "in" ) )
, beReady( addInputPort( "beReady" ) )
, out( addOutputPort( "out" ) )
, request( addOutputPort( "request" ) )
{

string id( MainSimulator::Instance().getParameter( description(), "myId" ) ) ;
myId = atoi(id.data());  //accept any value from user.
	
try
{
dist = Distribution::create( MainSimulator::Instance().getParameter( description(), "distribution" ) );
MASSERT( dist ) ;
for ( register int i = 0; i < dist->varCount(); i++ )
	{
	string parameter( MainSimulator::Instance().getParameter( description(), dist->getVar( i ) ) );
	dist->setVar( i, str2Value( parameter ) ) ;
	}

} catch( InvalidDistribution &e )
	{
	e.addText( "The model " + description() + " has distribution problems!" ) ;
	e.print(cerr);
	MTHROW( e ) ;
} catch( MException &e )
	{
	MTHROW( e ) ;
	}

}

/*******************************************************************
* Function Name: initFunction
* Description:
* 
********************************************************************/
Model& Server::initFunction()
{
ready = false;
holdIn( active, Time::Zero);  // To force sending initial request to the queue
return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model& Server::externalFunction( const ExternalMessage &msg )
{
if ((this->state() == passive) && (msg.port() == beReady) && (myId == (int) msg.value()))
	{
	ready = true;
	}
else if ((this->state() == passive) && (msg.port() == in) && (ready == true))
	{
	value = msg.value();
	double service_time = fabs( distribution().get());
	if (service_time > 0)
		service_time = 1000/service_time;
	else
		service_time = 0;
	holdIn(active, Time(0,0,0,service_time)) ;
	}

return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model& Server::internalFunction( const InternalMessage & )
{
ready = false;
passivate();
return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Server::outputFunction( const InternalMessage &msg )
{

if (ready == true)  // if not initial execution
	sendOutput( msg.time(), out, value) ;

sendOutput( msg.time(), request, myId) ;

return *this ;
}
/*******************************************************************
* Function Name: 
* Description: 
********************************************************************/
Server::~Server ()
{ 
delete dist;
}
