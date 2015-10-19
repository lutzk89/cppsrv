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
      int pcross = 200;
      int p;
      float fcha1;
      float fcha2;
      float v1,v2;
      for ( vector<forexRule*>::iterator it = _genotype1.rules.begin(); it != _genotype1.rules.end() ; ++it ) {
    	  for ( vector<forexRule*>::iterator at = _genotype2.rules.begin(); at != _genotype2.rules.end() ; ++at ) {
    		  if ( (*it)->tstamp == (*at)->tstamp ) {
    			  p = rand()%1000;
    			  if ( p < pcross ) {
    				  for ( int k = 0; k < 6; k++ ) {
    				      fcha1 =  abs( distribution(generator) );//((float)(rand() % 10000000)) * num - offs;
    				      fcha2 =  abs( distribution(generator) );//((float)(rand() % 10000000)) * num - offs;
    				      v1 = (*it)->weights[k];
    				      v2 = (*at)->weights[k];
    					  (*it)->weights[k] = (v1*fcha1 + v2*fcha2)/( fcha1 + fcha2);//( (*it)->weights[k] + (*at)->weights[k] ) * 0.5;
    					  (*at)->weights[k] = (v1*fcha1 + v2*fcha2)/( fcha1 + fcha2);// ( (*it)->weights[k] + (*at)->weights[k] ) * 0.5;
    				  }
    				  oneAtLeastIsModified = true;
    			  }
    		  }
    	  }
      }
       /** Requirement
	* if (at least one genotype has been modified) // no way to distinguish
	*     oneAtLeastIsModified = true;
	* else
	*     oneAtLeastIsModified = false;
	*/
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
