/**
 * SLFNELM.hpp
 *
 * Created on: 3/29/2013
 *     Author: ZHU Qiuxi
 */

#ifndef SLFN_ELM_HPP
#define SLFN_ELM_HPP

#include "armadillo"
#include "SLFNTrainer.hpp"

namespace model{

class SLFNELM:public SLFNTrainer{
private:
	SLFNELM();
	~SLFNELM();

public:
	static SLFNELM* getInstance();

	void run(SLFN* net,const arma::Mat<double>& tIn,const arma::Mat<double>& tOut);
	static void init(SLFN* net,int netN,int netNH);

private:
	static arma::Mat<double> getH(SLFN* net,const arma::Mat<double>& tIn);
};

}

#endif //SLFN_ELM_HPP
