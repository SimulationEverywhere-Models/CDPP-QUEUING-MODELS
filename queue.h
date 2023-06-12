/*******************************************************************
*
*  DESCRIPTION: Atomic Model Queue
*
*  AUTHOR: Khaldoon Al-Zoubi 
*
*
*  DATE: 18/11/2003
*
*******************************************************************/

#ifndef __QUEUE_H
#define __QUEUE_H

#include <list>
#include "atomic.h"     // class Atomic

class Queue : public Atomic
{
public:
	Queue( const string &name = "Queue" );	//Default constructor
	virtual ~Queue() { delete [] reqList; }
	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &in;
	const Port &request;
	Port &out;
	Port &beReady;	
	typedef list<Value> ElementList ;
	ElementList elements;
	int *reqList;
	int request_count;
	int max_servers;
	int get_server_id();

};	// class Queue

// ** inline ** // 
inline
string Queue::className() const
{
	return "Queue" ;
}

#endif   //__QUEUE_H
