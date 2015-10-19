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

// include the base definition of eoEvalFunc
#include "eoEvalFunc.h"

/**
  Always write a comment in this format before class definition
  if you want the class to be documented by Doxygen
 */
template <class EOT>
class eoforexEvalFunc : public eoEvalFunc<EOT>
{
public:
	float *fbuf;
	int nfile;
	vector<float> data;
	int flength;
	/// Ctor - no requirement
	// START eventually add or modify the anyVariable argument
	eoforexEvalFunc()
	//  eoforexEvalFunc( varType  _anyVariable) : anyVariable(_anyVariable)
	// END eventually add or modify the anyVariable argument
	{
		// START Code of Ctor of an eoforexEvalFunc object
		//Initialize the training buffer
		nfile=0;
		flength=filelength;
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
				/*
				 * exclude . and ..
				 */
				if ( strcmp(epdf->d_name, thisdir) == 0 || strcmp(epdf->d_name, pardir) == 0 ) {
					continue;
				}
				//printf("Filename: %s",epdf->d_name);
				nfile++;
			}
		}
		this->fbuf = new float[nfile*flength];
		dpdf = opendir("./data");
		i=0;
		if (dpdf != NULL){
			while ( ( epdf = readdir(dpdf) ) ){

				// std::out << epdf->d_name << std::endl;
				/*
				 * exclude . and ..
				 */
				if ( strcmp(epdf->d_name, thisdir) == 0 || strcmp(epdf->d_name, pardir) == 0 ) {
					continue;
				}
				printf("Reading file: %s \n",epdf->d_name);
				j=0;
				for ( int k =0; k < 100; k++) {
					fullfile[k]='\0';
				}
				strcpy(fullfile,"./data/");
				strcat(fullfile,epdf->d_name);
				ifile.open(fullfile);
				if ( !ifile ) {
					cout << "Error opening " << fullfile << endl;
					continue;
				}
				while ( !ifile.eof() ) {
					ifile >> temp;
					if ( !ifile.eof() ) {
						this->fbuf[i*flength+j] = temp;
						j++;
					}
				}
				ifile.close();
				ifile.clear();
				i++;
			}
		}
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
		//cout << "Enter runWithFitness\n";
		if (_eo.invalid())
		{
			float fit = 0;		   // to hold fitness value
			//float *data = new float[_eo.mylength];
			// START Code of computation of fitness of the eoforex object
			for (int i = 0; i < this->nfile ; i++) {
				//for ( int j = 0 ; j < _eo.flength ; j++ ) {
				//	eo.fbuf[i*eo.flength+j];
				//}

				//copy(this->fbuf+i*this->flength,this->fbuf+i*this->flength+this->flength,data);
				// debug
				this->data.clear();//resize(_eo.mylength);
				for ( int j = 0; j < this->flength; j++) {
					this->data.push_back(((float)(this->fbuf[i*this->flength + j])));
					//cout << "File Val  " << ((float)(this->fbuf[i*this->flength + j])) << endl;
				}
				fit += _eo.runWithFitness(this->data);
			}

			//cout << "Leaving runWithFitness\n";
			// END   Code of computation of fitness of the eoforex object
			_eo.myfit = fit;
			//cout << "fitness " << fit << endl;
			_eo.fitness(fit);
		}
		this->data.clear();//resize(_eo.mylength);
	}

private:
	// START Private data of an eoforexEvalFunc object
	//  varType anyVariable;		   // for example ...
	// END   Private data of an eoforexEvalFunc object
};


#endif
