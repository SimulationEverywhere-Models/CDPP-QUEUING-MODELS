/*******************************************************************
*
*  DESCRIPTION: class Generator
*
*  AUTHOR: Khaldoon Al-Zoubi 
*
*
*  DATE: 29/11/2003
*
*******************************************************************/

#ifndef __GENERATOR_H
#define __GENERATOR_H

/** include files **/
#include "atomic.h"     // class Atomic
#include "except.h"     // class InvalidMessageException

/** forward declarations **/
class Distribution ;

/** declarations **/
class Generator : public Atomic
{
public:
	Generator( const string &name = "Generator" );	// Default constructor

	~Generator();

	virtual string className() const
		{return "Generator";}

protected:
	Model &initFunction() ;

	Model &externalFunction( const ExternalMessage & )
			{throw InvalidMessageException();}

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage & );

private:
	Port &out ;
	Distribution *dist ;
	double customer_id;
	double customers; // number of customers that will be generated in time unit.
	Distribution &distribution()
			{return *dist;}
			
};	// class Generator


#endif   //__GENERATOR_H 
