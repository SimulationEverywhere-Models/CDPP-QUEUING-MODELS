/*******************************************************************
*
*  DESCRIPTION: Atomic Model Queue
*
*  AUTHOR: Khaldoon Al-Zoubi 
*
*  DATE: 18/11/2003
*
*******************************************************************/

/** include files **/
#include "queue.h"      // class Queue
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )
#include <stdlib.h>

/** public functions **/

/*******************************************************************
* Function Name: Queue
* Description: 
********************************************************************/
Queue::Queue( const string &name )
: Atomic( name )
, in( addInputPort( "in" ) )
, request( addInputPort( "request" ) )
, out( addOutputPort( "out" ) )
, beReady( addOutputPort( "beReady" ) )
{
string servers( MainSimulator::Instance().getParameter( description(), "servers" ) ) ;

max_servers = atoi(servers.data());

if (max_servers <= 0)
	max_servers = 10;

reqList = new int[max_servers];
MASSERT (reqList != 0);

//Display information to user
cout<<endl<<"The queue can be connected with ";
if (max_servers == 1)
	cout<<"only "<<max_servers<<" server";
else
	cout<<max_servers<<" servers";
cout<<endl<<endl;
}

/*******************************************************************
* Function Name: initFunction
* Description:
* Precondition: 
********************************************************************/
Model &Queue::initFunction()
{

for (int server_id=0; server_id<max_servers; server_id++)
	reqList[server_id] = 0;

request_count = 0;
elements.erase( elements.begin(), elements.end() ) ;

return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Queue::externalFunction( const ExternalMessage &msg )
{
if( msg.port() == in )
	{
	elements.push_back( msg.value() ) ;
      	if ((elements.size() == 1) && (request_count > 0))
		holdIn( active, Time::Zero);
	else if (request_count == 0)
		passivate();
	}

if( (msg.port() == request ) && (msg.value() >= 0) && (msg.value() < max_servers))
	{
	reqList[(int)msg.value()] = 1;
	
	request_count++;
	
	if ((request_count == 1) && (elements.size() > 0))
		holdIn( active, Time::Zero);
	
	else if (elements.size() == 0)
		passivate();	
	}

return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &Queue::internalFunction( const InternalMessage & )
{

elements.pop_front();

if ((request_count >0) && (elements.size() > 0))
	holdIn( active, Time::Zero);
else
	passivate();

return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Queue::outputFunction( const InternalMessage &msg )
{
int server_id = get_server_id();

if (server_id >= 0)
	{
	sendOutput( msg.time(), beReady, (double)server_id); // make server ready
	sendOutput( msg.time(), out, elements.front());  //send data to desired server
	}

return *this ;
}
/*******************************************************************
* Function Name: get_server_id
* Description: 
********************************************************************/

int Queue::get_server_id()
{

for (int server_id=0; server_id<max_servers; server_id++)
	{
	if (reqList[server_id] == 1) //this server has request
		{
		reqList[server_id] = 0;
		request_count--;
		return server_id; // found server
		}
	}
return -1;
}
