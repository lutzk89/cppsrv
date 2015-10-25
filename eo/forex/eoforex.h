/** -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

The above line is usefulin Emacs-like editors
 */

/*
Template for creating a new representation in EO
================================================

Mandatory:
- a default constructor (constructor without any argument)
- the I/O functions (readFrom and printOn)

However, if you are using dynamic memory, there are 2 places
to allocate it: the default constructor (if possible?), or, more in
the EO spirit, the eoInit object, that you will need to write anyway
(template file init.tmpl).

But remember that a COPY CONSTRUCTOR will be used in many places in EO,
so make sure that the default copy constructor works, or, even better,
do write your own if in doubt.
And of course write the corresponding destructor!

*/

#ifndef _eoforex_h
#define _eoforex_h


#include<neuralnet.h>



template< class FitT>
class eoforex: public EO<FitT> {
private:
	neuralnet* net;
public:

  /** Ctor: you MUST provide a default ctor.
   * though such individuals will generally be processed
   * by some eoInit object
   */
  eoforex()
  {
	  this->net = new neuralnet(48,48,2);//TODO parametrisieren
  }
  // Backpropagation and return fitness
  double runNetwork() {
	  return this->net->backprop(0.1);
  }

  /** Copy Ctor: you MUST provide a copy ctor if the default
   * one is not what you want
   * If this is the case, uncomment and fill the following
   */

  eoforex(const eoforex &eo)
  {
	  this->net = new neuralnet(eo.net);
  }



  virtual ~eoforex()
  {
    // START Code of Destructor of an eoEASEAGenome object
	  delete this->net;
    // END   Code of Destructor of an eoEASEAGenome object
  }

  virtual string className() const { return "eoforex"; }

  /** printing... */
    void printOn(ostream& os) const
    {
      // First write the fitness
      EO<FitT>::printOn(os);
      os << ' ';
    // START Code of default output

	/** HINTS
	 * in EO we systematically write the sizes of things before the things
	 * so readFrom is easier to code (see below)
	 */

    // END   Code of default output
    }

  /** reading...
   * of course, your readFrom must be able to read what printOn writes!!!
   */
    void readFrom(istream& is)
      {
	// of course you should read the fitness first!
	EO<FitT>::readFrom(is);
    // START Code of input

	/** HINTS
	 * remember the eoforex object will come from the default ctor
	 * this is why having the sizes written out is useful
	 */

    // END   Code of input
      }

private:			   // put all data here
    // START Private data of an eoforex object
    // END   Private data of an eoforex object
};

#endif
