/**
 * SLFNTrainer.hpp
 *
 * Created on: 3/29/2013
 *     Author: ZHU Qiuxi
 */

#ifndef SLFN_TRAINER_HPP
#define SLFN_TRAINER_HPP

#include "armadillo"
#include "SLFN.h"

namespace model{

class SLFNTrainer{
public:
	virtual void run(SLFN* net,const arma::Mat<double>& tIn,
	                           const arma::Mat<double>& tOut)=0;

	virtual ~SLFNTrainer();
};

}

#endif //SLFN_TRAINER_HPP
