/**
 * SigmoidFunction.h
 *
 * Created on: 3/28/2013
 *     Author: ZHU Qiuxi
 */

#ifndef SIGMOID_FUNCTION_H
#define SIGMOID_FUNCTION_H

#include "ActivationFunction.h"

namespace model{

class SigmoidFunction:public ActivationFunction{
private:
	static SigmoidFunction* instance;
	
	SigmoidFunction(); //private constructor
	~SigmoidFunction();

public:
	static SigmoidFunction* getInstance();
	
	double f(double x);
};

}

#endif //SIGMOID_FUNCTION_H
