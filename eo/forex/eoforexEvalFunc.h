/** -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

The above line is usefulin Emacs-like editors
 */

/*
Template for evaluator in EO, a functor that computes the fitness of an EO
==========================================================================
 */

#ifndef _eoforexEvalFunc_h
#define _eoforexEvalFunc_h

// include whatever general include you need
#include <stdexcept>
#include <fstream>
#include<dataprovider.h>
// include the base definition of eoEvalFunc
#include "eoEvalFunc.h"

/**
  Always write a comment in this format before class definition
  if you want the class to be documented by Doxygen
 */
template <class EOT>
class eoforexEvalFunc : public eoEvalFunc<EOT>
{
private:
	dataProvider* provider;
public:
	/// Ctor - no requirement
	// START eventually add or modify the anyVariable argument
	eoforexEvalFunc()
	//  eoforexEvalFunc( varType  _anyVariable) : anyVariable(_anyVariable)
	// END eventually add or modify the anyVariable argument
	{
		// START Code of Ctor of an eoforexEvalFunc object
		//Initialize the training buffer
		this->provider = new dataProvider("../forex_work/data"); // TODO: workdir aus config einlesen
		// END   Code of Ctor of an eoforexEvalFunc object
	}

	/** Actually compute the fitness
	 *
	 * @param EOT & _eo the EO object to evaluate
	 *                  it should stay templatized to be usable
	 *                  with any fitness type
	 */
	void operator()(EOT & _eo)
	{
		// test for invalid to avoid recomputing fitness of unmodified individuals
		ifstream ifile;
		if (_eo.invalid())
		{
			float fit = 0;		   // to hold fitness value
			// START Code of computation of fitness of the eoforex object
			fit = _eo.runNetwork();
			_eo.fitness(fit);
		}
		this->data.clear();
	}

private:
	// START Private data of an eoforexEvalFunc object
	//  varType anyVariable;		   // for example ...
	// END   Private data of an eoforexEvalFunc object
};


#endif
