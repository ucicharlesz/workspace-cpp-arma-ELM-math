/**
 * SigmoidFunction.cpp
 *
 * Created on: 3/28/2013
 *     Author: ZHU Qiuxi
 */

#include <iostream>
#include <math.h>
#include "SigmoidFunction.h"

using namespace model;

SigmoidFunction* SigmoidFunction::instance=NULL;

SigmoidFunction::SigmoidFunction(){;}
SigmoidFunction::~SigmoidFunction(){;}

SigmoidFunction* SigmoidFunction::getInstance(){
	if(instance==NULL) instance=new SigmoidFunction();
	return instance;
}

double SigmoidFunction::f(double x){
	return 1./(1.+exp(-x));
}
