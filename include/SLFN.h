/**
 * SLFN.h
 *
 * Created on: 3/28/2013
 *     Author: ZHU Qiuxi
 */

#ifndef SLFN_H
#define SLFN_H

#include "armadillo"
#include "ActivationFunction.h"

namespace model{

class SLFN{
public:
	virtual arma::Col<double> f(const arma::Col<double>& arg)=0;
	
	virtual arma::Mat<double>& getWIn()=0;
	virtual arma::Col<double>& getB()=0;
	virtual arma::Mat<double>& getWOut()=0;
	virtual ActivationFunction* getG()=0;
	virtual int getN()=0;
	virtual int getNH()=0;
	virtual int getM()=0;
	
	virtual void setWIn(const arma::Mat<double>& arg)=0;
	virtual void setB(const arma::Col<double>& arg)=0;
	virtual void setWOut(const arma::Mat<double>& arg)=0;
	virtual void setG(ActivationFunction* arg)=0;

	virtual ~SLFN();
};

}

#endif //SLFN_H
