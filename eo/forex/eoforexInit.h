/** -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

The above line is usefulin Emacs-like editors
 */

/*
Template for EO objects initialization in EO
============================================
 */

#ifndef _eoforexInit_h
#define _eoforexInit_h

// include the base definition of eoInit
#include <eoInit.h>

/**
 *  Always write a comment in this format before class definition
 *  if you want the class to be documented by Doxygen
 *
 * There is NO ASSUMPTION on the class GenoypeT.
 * In particular, it does not need to derive from EO (e.g. to initialize
 *    atoms of an eoVector you will need an eoInit<AtomType>)
 */
template <class GenotypeT>
class eoforexInit: public eoInit<GenotypeT> {
public:
	std::default_random_engine generator;
	std::normal_distribution<float> distribution;
	/// Ctor - no requirement
	// START eventually add or modify the anyVariable argument
	eoforexInit()
//  eoforexInit( varType  _anyVariable) : anyVariable(_anyVariable)
// END eventually add or modify the anyVariable argument
{
		std::normal_distribution<float> temp(0.0,1.0);
		distribution = temp;
		// START Code of Ctor of an eoforexInit object
		// END   Code of Ctor of an eoforexInit object
}


	/** initialize a genotype
	 *
	 * @param _genotype  generally a genotype that has been default-constructed
	 *                   whatever it contains will be lost
	 */
	void operator()(GenotypeT & _genotype)
	{
		// START Code of random initialization of an eoforex object
		/*
		 * Initialize Genotype
		 */

		_genotype.randomInit();
		// END   Code of random initialization of an eoforex object
		_genotype.invalidate();	   // IMPORTANT in case the _genotype is old
	}

private:
	// START Private data of an eoforexInit object
	//  varType anyVariable;		   // for example ...
	// END   Private data of an eoforexInit object
};

#endif
