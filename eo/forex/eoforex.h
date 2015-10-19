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


/**
 *  Always write a comment in this format before class definition
 *  if you want the class to be documented by Doxygen

 * Note that you MUST derive your structure from EO<fitT>
 * but you MAY use some other already prepared class in the hierarchy
 * like eoVector for instance, if you handle a vector of something....

 * If you create a structure from scratch,
 * the only thing you need to provide are
 *        a default constructor
 *        IO routines printOn and readFrom
 *
 * Note that operator<< and operator>> are defined at EO level
 * using these routines
 */
class forexRule {
public:
	int from1;
	int from2;
	int to;
	float *weights;
	int tstamp;
	forexRule(int nfrom1,int nfrom2,int nto,float* nweights,int ntstamp) {
		this->weights = new float[6];
		this->from1 = nfrom1;
		this->from2 = nfrom2;
		this->to = nto;
		//copy(nweights[0],nweights[4],this->weights);
		for (int i=0;i<6;i++) {
			this->weights[i] = nweights[i];
		}
		this->tstamp = ntstamp;
	}
	int calcRule(vector<float>& data) {
		if ( this->to >= data.size() || this->from1 >= data.size() || this->from2 >= data.size() ) {
			//cout << "Invalid rule address, break " << this->to << " " << this->from1 << " " << this->from2 << " " << data.size() << endl;
			return 1;
		}
		data[this->to] = tanh( this->weights[0] + this->weights[1] * data[this->from1] + this->weights[2] * data[this->from2] + this->weights[3] * data[this->from1] * data[this->from1] + this->weights[4] * data[this->from2] * data[this->from2] + this->weights[5] * data[this->from1] * data[this->from2] );
//		if ( this->to == filelength - 1 )
//			cout << this->from1 << " " << this->from2 << " " << this->to  << " " << data[this->to] << " " << data[this->from1] << " " << data[this->from2] << endl;
//		for ( int i=0; i < 6; i++)
//			cout << this->weights[i] << endl;
//
		return 0;
	}
};


template< class FitT>
class eoforex: public EO<FitT> {
public:
	/**
	 * Class attributes
	 */
int flength;
int nfile;
int mylength;
float myfit;

vector<forexRule*> rules;

  /** Ctor: you MUST provide a default ctor.
   * though such individuals will generally be processed
   * by some eoInit object
   */
  eoforex()
  {
	  nfile=0;
	  myfit = 10000.0;
	  flength=filelength;
	  mylength=filelength;
	  /* OBSOLET
	  nfile=0;
	  flength=5;
	  mylength=5;
	  float temp;
	  ifstream ifile;
	  int i,j;
	  char thisdir[] = 	".";
	  char pardir[] = "..";
	  char fullfile[100];
	  DIR *dpdf;
	  struct dirent *epdf;

	  dpdf = opendir("./data");
	  if (dpdf != NULL){
	     while ( ( epdf = readdir(dpdf) ) ){

	        // std::out << epdf->d_name << std::endl;

	    	 if ( strcmp(epdf->d_name, thisdir) == 0 || strcmp(epdf->d_name, pardir) == 0 ) {
	    		 continue;
	    	 }
	    	 //printf("Filename: %s",epdf->d_name);
	    	 nfile++;
	     }
	  }
*/


    // START Code of default Ctor of an eoforex object
    // END   Code of default Ctor of an eoforex object
  }

  double runNetwork(vector<float>& data) {
	  data[this->flength-1] = 0;
	  int k=0;
	  for ( vector<forexRule*>::iterator it=this->rules.begin(); it != this->rules.end(); ++it) {
		  (*it)->calcRule(data);
		  k++;
	  }
	  return data[this->flength-1];
  }

  double runWithFitness(vector<float>& data) {
	  float prev = data[this->flength-1];
	  float scale = 0.1;
	  float offs = 0.1;
	  float after = this->runNetwork(data);
	  //cout << after << " " << prev << endl;
	  float diff = abs( prev - after );// * scale + offs;
	  return diff;
  }

  /** Copy Ctor: you MUST provide a copy ctor if the default
   * one is not what you want
   * If this is the case, uncomment and fill the following
   */
/**
  eoforex(const eoforex &eo)
  {
    // START Code of copy Ctor of an eoforex object
	  this->flength = eo.flength;
	  this->nfile = eo.flength;
	  this->mylength = eo.flength;
	  this->rules = eo.rules;
    // END   Code of copy Ctor of an eoforex object
  }
**/


  virtual ~eoforex()
  {
    // START Code of Destructor of an eoEASEAGenome object
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
