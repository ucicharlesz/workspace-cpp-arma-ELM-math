/**
 * HyperbolicTangentFunction.cpp
 *
 * Created on: 3/28/2013
 *     Author: ZHU Qiuxi
 */

#include <iostream>
#include <math.h>
#include "HyperbolicTangentFunction.h"

using namespace model;

HyperbolicTangentFunction* HyperbolicTangentFunction::instance=NULL;

HyperbolicTangentFunction::HyperbolicTangentFunction(){;}
HyperbolicTangentFunction::~HyperbolicTangentFunction(){;}

HyperbolicTangentFunction* HyperbolicTangentFunction::getInstance(){
	if(instance==NULL) instance=new HyperbolicTangentFunction();
	return instance;
}

double HyperbolicTangentFunction::f(double x){
	return (exp(x)-exp(-x))/(exp(x)+exp(-x));;
}
