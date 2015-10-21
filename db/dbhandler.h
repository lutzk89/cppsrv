/*
 * dbhandler.h
 *
 *  Created on: 21.10.2015
 *      Author: lutzk
 */

#ifndef DB_DBHANDLER_H_
#define DB_DBHANDLER_H_


template<class ntype>
class dataSet {
        public:
        virtual int getLength();
        virtual ntype getValue(int position);
}

template<class ntype>
class nnDataSet: public dataSet<ntype> {
        public:
                nnDataSet(string fname);
                int getLength();
};

class dbhandler {
};

class dirDbhandler: public dbhandler {
	public:
	dirDbhandler(string dirName);
	int read_dir();
};



#endif /* DB_DBHANDLER_H_ */
