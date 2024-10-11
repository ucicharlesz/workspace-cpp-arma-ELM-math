/**
 * HyperbolicTangentFunction.h
 *
 * Created on: 3/28/2013
 *     Author: ZHU Qiuxi
 */

#ifndef HYPERBOLIC_TANGENT_FUNCTION_H
#define HYPERBOLIC_TANGENT_FUNCTION_H

#include "ActivationFunction.h"

namespace model{

class HyperbolicTangentFunction:public ActivationFunction{
private:
	static HyperbolicTangentFunction* instance;
	
	HyperbolicTangentFunction(); //private constructor
	~HyperbolicTangentFunction();

public:
	static HyperbolicTangentFunction* getInstance();
	
	double f(double x);
};

}

#endif //HYPERBOLIC_TANGENT_FUNCTION_H
