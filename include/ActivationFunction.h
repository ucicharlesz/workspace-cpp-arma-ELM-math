/**
 * ActivationFunction.h
 *
 * Created on: 3/28/2013
 *     Author: ZHU Qiuxi
 */

#ifndef ACTIVATION_FUNCTION_H
#define ACTIVATION_FUNCTION_H

namespace model{

class ActivationFunction{
public:
	virtual double f(double x)=0;

	virtual ~ActivationFunction();
};

}

#endif //ACTIVATION_FUNCTION_H
