/** -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

The above line is usefulin Emacs-like editors
 */

/*
Template for simple quadratic crossover operators
=================================================

Quadratic crossover operators modify the both genotypes
*/

#ifndef eoforexQuadCrossover_H
#define eoforexQuadCrossover_H

#include <eoOp.h>

/**
 *  Always write a comment in this format before class definition
 *  if you want the class to be documented by Doxygen
 *
 * THere is NO ASSUMPTION on the class GenoypeT.
 * In particular, it does not need to derive from EO
 */
template<class GenotypeT>
class eoforexQuadCrossover: public eoQuadOp<GenotypeT>
{
public:
  /**
   * Ctor - no requirement
   */
	std::random_device rd;
	    std::mt19937 generator;
		std::normal_distribution<float> distribution;
// START eventually add or modify the anyVariable argument
  eoforexQuadCrossover()
  //  eoforexQuadCrossover( varType  _anyVariable) : anyVariable(_anyVariable)
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
  string className() const { return "eoforexQuadCrossover"; }

  /**
   * eoQuad crossover - _genotype1 and _genotype2 are the (future)
   *       offspring, i.e. _copies_ of the parents, to be modified
   * @param _genotype1 The first parent
   * @param _genotype2 The second parent
   */
  bool operator()(GenotypeT& _genotype1, GenotypeT & _genotype2)
  {
	  //cout << "Enter Crossover\n";
      bool oneAtLeastIsModified(false);
    // START code for crossover of _genotype1 and _genotype2 objects

    //cout << "Leave Crossover\n";
    return oneAtLeastIsModified;
    // END code for crossover of _genotype1 and _genotype2 objects
  }

private:
// START Private data of an eoforexQuadCrossover object
  //  varType anyVariable;		   // for example ...
// END   Private data of an eoforexQuadCrossover object
};

#endif
