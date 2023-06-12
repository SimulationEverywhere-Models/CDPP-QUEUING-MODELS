/*******************************************************************
*
*  DESCRIPTION: Performance
*
*  AUTHOR: Khaldoon Al-Zoubi 
*
*
*  DATE: 21/11/2003
*
*******************************************************************/

/** include files **/
#include "performance.h"  // class Performance
#include "message.h"   	  // class ExternalMessage, InternalMessage
#include "mainsimu.h"     // MainSimulator::Instance().getParameter( ... )

/*******************************************************************
* Function Name: Performance
* Description: 	
* 		
********************************************************************/
Performance::Performance( const string &name )
: Atomic( name )
, enter_sys( addInputPort( "enter_sys" ) )
, exit_q( addInputPort( "exit_q" ) )
, exit_sys( addInputPort( "exit_sys" ) )
, get_data( addInputPort( "get_data" ) )
, Lq( addOutputPort( "Lq" ) )
, Wq( addOutputPort( "Wq" ) )
, Ls( addOutputPort( "Ls" ) )
, Ws( addOutputPort( "Ws" ) )
{
//empty	
}

/*******************************************************************
* Function Name: initFunction
* Description:
* 
********************************************************************/
Model& Performance::initFunction()
{
	
in_sys = 0;
out_q = 0;
out_sys = 0;
Lq_val = 0;
Ls_val = 0;
Wq_val = 0;
Ws_val = 0;
arrivalTimesWq.erase( arrivalTimesWq.begin(), arrivalTimesWq.end() );
arrivalTimesWs.erase( arrivalTimesWs.begin(), arrivalTimesWs.end() );

return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model& Performance::externalFunction( const ExternalMessage &msg )
{

if (msg.port() == enter_sys)
	{
	in_sys++;  // customer just enetered the system.
	arrivalTimesWq.push_back(msg.time());  // hold customer arrival time.
	calculate_Lq();
	calculate_Ls();
	}
else if (msg.port() == exit_q)
	{
	out_q++;  // customer just left the queue.
	calculate_Lq();
	calculate_Wq(msg.time());
	}
else if (msg.port() == exit_sys)
	{
	out_sys++;  // customer just left the system.
	calculate_Ls();
	calculate_Ws(msg.time());
	}
else if (msg.port() == get_data)
	{
	holdIn( active, Time::Zero);
	}

return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model& Performance::internalFunction( const InternalMessage & )
{
passivate();
return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Performance::outputFunction( const InternalMessage &msg )
{

sendOutput( msg.time(), Lq, Lq_val);
sendOutput( msg.time(), Wq, Wq_val);
sendOutput( msg.time(), Ls, Ls_val);
sendOutput( msg.time(), Ws, Ws_val);

return *this;
}
/************************************************
* The mean of elements in the queue
*************************************************/
void Performance::calculate_Lq()
{
int q_update = in_sys + out_q;
int cur_q_size = in_sys - out_q;

Lq_val = ((Lq_val * q_update) + cur_q_size) / (q_update + 1);
}
/***********************************************
* The mean of elements in system
* *********************************************/
void Performance::calculate_Ls()
{
int sys_update = in_sys + out_sys;
int cur_sys_size = in_sys - out_sys;

Ls_val = ((Ls_val * sys_update) + cur_sys_size) / (sys_update + 1);
}
/************************************************
* The mean of waiting time in the queue
*************************************************/
void Performance::calculate_Wq(const Time &cur_time)
{
Time cur_wating_time;
float cur_wating_time_sec;

MASSERT (!arrivalTimesWq.empty());

if (cur_time >= arrivalTimesWq.front() )
	{
	cur_wating_time = cur_time - arrivalTimesWq.front();  // time diff
	cur_wating_time_sec = convertTimeToSec(cur_wating_time);

	MASSERT(out_q > 0);
	Wq_val = ( (Wq_val * (out_q - 1)) + cur_wating_time_sec ) / out_q;
	}
arrivalTimesWs.push_back(arrivalTimesWq.front());
arrivalTimesWq.pop_front();
}
/************************************************
* The mean of waiting time in the system
*************************************************/
void Performance::calculate_Ws(const Time &cur_time)
{
Time cur_wating_time;
float cur_wating_time_sec;

MASSERT (!arrivalTimesWs.empty());

if (cur_time >= arrivalTimesWs.front() )
	{
	cur_wating_time = cur_time - arrivalTimesWs.front();  // time diff
	cur_wating_time_sec = convertTimeToSec(cur_wating_time);

	MASSERT(out_sys > 0);
	Ws_val = ( (Ws_val * (out_sys - 1)) + cur_wating_time_sec ) / out_sys;
	}
arrivalTimesWs.pop_front();
}
/************************************************
* Convert time into seconds
*************************************************/
float Performance::convertTimeToSec(const Time &time)
{
int hour = 60 * 60 * time.hours();
int min = 60 * time.minutes();
int sec = time.seconds();
float msec = (float)time.mseconds()/1000;

return hour + min + sec + msec;
}
