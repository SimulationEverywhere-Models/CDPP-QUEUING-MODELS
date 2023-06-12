/*******************************************************************
*
*  DESCRIPTION: Performance Model
*
*  AUTHOR: Khaldoon Al-Zoubi 
*
*
*  DATE: 20/11/2003
*
*******************************************************************/

#ifndef __PERFORMANCE_H
#define __PERFORMANCE_H

#include "atomic.h"     // class Atomic
#include "time.h"	// class Time
#include <list>

class Performance : public Atomic
{
public:
	Performance( const string &name = "Performance" );	//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &enter_sys;
	const Port &exit_q;
	const Port &exit_sys;
	const Port &get_data;
	Port &Lq;
	Port &Wq;
	Port &Ls;
	Port &Ws;
	int in_sys, out_q, out_sys;
	float Lq_val, Wq_val, Ls_val, Ws_val;
	void calculate_Lq();
	void calculate_Wq(const Time &time);
	void calculate_Ls();
	void calculate_Ws(const Time &time);
	typedef list<Time> TimeStamps;
	TimeStamps arrivalTimesWq;  // Holds arrival times for customers in the queue
	TimeStamps arrivalTimesWs;  // Holds arrival times for customers in the system
				    // but had already left the queue
	float convertTimeToSec(const Time &time);
};	// class Performance

// ** inline ** // 
inline
string Performance::className() const
{
return "Performance" ;
}
#endif   //__PERFORMANCE_H
