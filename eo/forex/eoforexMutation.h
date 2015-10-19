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
		int padd = 900;
		int prem = 200;
		int pcha = 1000;
		int rpos;
		int from1, from2, to;
		float *nweights;
		nweights = new float[6];
		forexRule* newRule;
		int p;
		int del;
		float fcha;
		float num = 0.0000001;
		float offs = 0.5; // 0.001 * 1000 * 0.5
		for ( vector<forexRule*>::iterator it = _genotype.rules.begin(); it != _genotype.rules.end() ; ++it ) {
			for ( int k = 0; k < 6 ; k++ ) {
				p = rand()%1000;
				if ( p < pcha ) {
					fcha =  distribution(generator);//((float)(rand() % 10000000)) * num - offs;
					(*it)->weights[k] = (*it)->weights[k] + fcha;
					isModified = true;
				}
			}
		}
		p = rand()%1000;
		while ( p < padd ) {
			isModified = true;
			from1 = rand() % _genotype.mylength;
			from2 = rand() % _genotype.mylength;
			to = rand() % ( _genotype.mylength + 1 );
			if ( to >= _genotype.mylength ) {
				_genotype.mylength++;
			}

			for ( int i = 0; i < 6; i++ ) {
				fcha = distribution(generator);//((float)(rand() % 1000)) * num - offs;
				nweights[i] = fcha;
			}
			newRule = new forexRule(from1,from2,to,nweights,mutationcounter);
			rpos = rand() % _genotype.rules.size();
			_genotype.rules.insert(_genotype.rules.begin(), newRule);
			mutationcounter++;
			p = rand()%1000;
		}

		p = rand()%1000;
		while ( p < prem ) {
			if ( _genotype.rules.size() > 0 ) {
				isModified = true;
				del = rand() % _genotype.rules.size();
				//delete _genotype.rules[del]; // first free the buffer
				_genotype.rules.erase(_genotype.rules.begin());
				p = rand()%1000;
			} else {
				isModified = true;
				from1 = rand() % _genotype.mylength;
				from2 = rand() % _genotype.mylength;
				to = rand() % ( _genotype.mylength + 1 );
				if ( to >= _genotype.mylength ) {
					_genotype.mylength++;
				}
				for ( int i = 0; i < 6; i++ ) {
					fcha = distribution(generator);//((float)(rand() % 10000000)) * num - offs;
					nweights[i] = fcha;
				}
				newRule = new forexRule(from1,from2,to,nweights,mutationcounter);
				_genotype.rules.insert(_genotype.rules.begin(), newRule);
				mutationcounter++;
				p = rand()%1000;
			}
		}

		/** Requirement
		 * if (_genotype has been modified)
		 *     isModified = true;
		 * else
		 *     isModified = false;
		 */
		delete[] nweights;
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
