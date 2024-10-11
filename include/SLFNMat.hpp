/**
 * SLFNMat.hpp
 *
 * Created on: 4/18/2013
 *     Author: ZHU Qiuxi
 */

#ifndef SLFN_MAT_H
#define SLFN_MAT_H

#include <iostream>
#include "armadillo"
#include "SLFN.h"
#include "ActivationFunction.h"

namespace model{

class SLFNMat:public SLFN{
private:
	arma::Mat<double> wIn;
	arma::Col<double> b;
	arma::Mat<double> wOut;
	ActivationFunction* g;

public:
	SLFNMat();
	~SLFNMat();
	
/*These member functions will throw -1 for NullPointerException (in Java),
                                and -2 for IllegaL_ARGumentException*/
//                  they will throw -3 for unexpected internal miscv::Matches

	arma::Mat<double>& getWIn();
	arma::Col<double>& getB();
	arma::Mat<double>& getWOut();
	ActivationFunction* getG();
	int getN();
	int getNH();
	int getM();
	
	void setWIn(const arma::Mat<double>& arg);
	void setB(const arma::Col<double>& arg);
	void setWOut(const arma::Mat<double>& arg);
	void setG(ActivationFunction* arg);
	
	virtual arma::Col<double> f(const arma::Col<double>& arg);
};

}

#endif //SLFN_MAT_H
