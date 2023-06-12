/*******************************************************************
*
*  DESCRIPTION: class Generator
*
*  AUTHOR: Khaldoon Al-zoubi 
*
*  DATE: 29/11/2003
*
*******************************************************************/

/** include files **/
#include "generat.h"       // base header
#include "message.h"       // class InternalMessage 
#include "mainsimu.h"      // class Simulator
#include "distri.h"        // class Distribution 
#include "strutil.h"       // str2Value( ... )

/*******************************************************************
* Function Name: Generator
* Description: constructor
********************************************************************/
Generator::Generator( const string &name )
: Atomic( name )
, out( addOutputPort( "out" ) )
{
try
{
dist = Distribution::create( MainSimulator::Instance().getParameter( description(), "distribution" ) );
MASSERT( dist ) ;
for ( register int i = 0; i < dist->varCount(); i++ )
	{
	string parameter( MainSimulator::Instance().getParameter( description(), dist->getVar( i ) ) ) ;
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
********************************************************************/
Model &Generator::initFunction()
{

customer_id = 0;
customers = 0;
holdIn( active, Time::Zero);

return *this;
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &Generator::internalFunction( const InternalMessage & )
{
static double all_customers;

if (customers == 0)
	{
	customers = fabs( distribution().get() );  // get customers for next time unit
	all_customers = customers;
	}

if (customers > 0)
	holdIn( active, Time(0,0,0,1000/all_customers) );
else // nobody has come
	holdIn( active, Time(0,0,1,0) );  // sleep until next time unit.

return *this ;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &Generator::outputFunction( const InternalMessage &msg )
{

if (customers > 0)
	{
	customer_id++;
	sendOutput( msg.time(), out, customer_id);
	customers--;
	} // if

return *this ;
}
/*******************************************************************
* Function Name:
********************************************************************/
Generator::~Generator()
{
delete dist;
}

