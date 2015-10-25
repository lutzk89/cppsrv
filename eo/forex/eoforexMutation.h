/** -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

The above line is useful in Emacs-like editors
 */

/*
Template for simple mutation operators
======================================
 */

#ifndef eoforexMutation_H
#define eoforexMutation_H


#include <eoOp.h>

/**
 *  Always write a comment in this format before class definition
 *  if you want the class to be documented by Doxygen
 *
 * THere is NO ASSUMPTION on the class GenoypeT.
 * In particular, it does not need to derive from EO
 */
template<class GenotypeT>
class eoforexMutation: public eoMonOp<GenotypeT>
{

	//std::default_random_engine generator;
	std::random_device rd;
    std::mt19937 generator;
	std::normal_distribution<float> distribution;
public:

	/**
	 * Ctor - no requirement
	 */
	// START eventually add or modify the anyVariable argument
	eoforexMutation()
//  eoforexMutation( varType  _anyVariable) : anyVariable(_anyVariable)
// END eventually add or modify the anyVariable argument
{
		// START Code of Ctor of an eoforexEvalFunc object
		std::normal_distribution<float> temp(0.0,1.0);
		distribution = temp;
		std::mt19937 tgen(rd());
		generator = tgen;
		// END   Code of Ctor of an eoforexEvalFunc object
}

	/// The class name. Used to display statistics
	string className() const { return "eoforexMutation"; }

	/**
	 * modifies the parent
	 * @param _genotype The parent genotype (will be modified)
	 */
	bool operator()(GenotypeT & _genotype)
	{
		//cout << "mutate" << endl;
		//cout << "Enter Mutation\n";
		bool isModified(false);
		// START code for mutation of the _genotype object
		isModified = true;
		_genotype.mutate();
		//cout << "Leave Mutation\n";
		return isModified;
		// END code for mutation of the _genotype object
	}

private:
	// START Private data of an eoforexMutation object
	//  varType anyVariable;		   // for example ...
	// END   Private data of an eoforexMutation object
};

#endif
